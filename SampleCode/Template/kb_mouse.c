//
// Includes
//
#include <string.h>
#include "NuMicro.h"
#include "kb_mouse.h"

//
// Prototypes
//
void EPA_Handler(void);
void EPB_Handler(void);
void EPC_Handler(void);
void EPD_Handler(void);
void EPE_Handler(void);
void EPF_Handler(void);

//
// Variables
//
uint8_t volatile g_u8EPBOutBuff[EPB_MAX_PKT_SIZE];
uint8_t volatile g_u8EPFOutBuff[EPF_MAX_PKT_SIZE];

uint8_t volatile g_u8EPAReady = 0;
uint8_t volatile g_u8EPBReady = 0;

uint8_t volatile g_u8EPCReady = 0;

uint8_t volatile g_u8EPDReady = 0;

uint8_t volatile g_u8EPEReady = 0;
uint8_t volatile g_u8EPFReady = 0;

static uint8_t volatile g_u8ReportProtocol = HID_REPORT_PROTOCOL;

// signed char mouse_table[] = {-16, -16, -16, 0, 16, 16, 16, 0};
// uint8_t mouse_idx = 0;
// uint8_t move_len, mouse_mode=1;
//
// USBD20_IRQHandler
//
void USBD20_IRQHandler(void)
{
    __IO uint32_t IrqStL, IrqSt;

    /* get interrupt status */
    IrqStL = HSUSBD->GINTSTS & HSUSBD->GINTEN;    

    if (!IrqStL) {
        return;
    }

    /* USB interrupt */
    if (IrqStL & HSUSBD_GINTSTS_USBIF_Msk) {
        IrqSt = HSUSBD->BUSINTSTS & HSUSBD->BUSINTEN;

        if (IrqSt & HSUSBD_BUSINTSTS_SOFIF_Msk) {
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SOFIF_Msk);
        }
        
        if (IrqSt & HSUSBD_BUSINTSTS_RSTIF_Msk) {
            HSUSBD_SwReset();

            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_SET_ADDR(0);
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk |  \
                HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RSTIF_Msk);
            HSUSBD_CLR_CEP_INT_FLAG(0x1ffc);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_RESUMEIF_Msk) {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RESUMEIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_SUSPENDIF_Msk) {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SUSPENDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_HISPDIF_Msk) {
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_HISPDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_DMADONEIF_Msk) {
            g_hsusbd_DmaDone = 1;
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_DMADONEIF_Msk);

            if (HSUSBD->DMACTL & HSUSBD_DMACTL_DMARD_Msk) {
                if (g_hsusbd_ShortPacket == 1) {
                    HSUSBD->EP[EPA].EPRSPCTL = (HSUSBD->EP[EPA].EPRSPCTL & 0x10) | 
                        HSUSBD_EP_RSPCTL_SHORTTXEN;    // packet end
                    g_hsusbd_ShortPacket = 0;
                }
            }
        }

        if (IrqSt & HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk) {
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_VBUSDETIF_Msk) {
            if (HSUSBD_IS_ATTACHED()) {
                /* USB Plug In */
                HSUSBD_ENABLE_USB();
            } else {
                /* USB Un-plug */
                HSUSBD_DISABLE_USB();
            }
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_VBUSDETIF_Msk);
        }
    }

    if (IrqStL & HSUSBD_GINTSTS_CEPIF_Msk) {
        IrqSt = HSUSBD->CEPINTSTS & HSUSBD->CEPINTEN;

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPTKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPTKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPPKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk);
            HSUSBD_ProcessSetupPacket();
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_OUTTKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_OUTTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_INTKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            if (!(IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk)) {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk);
                HSUSBD_CtrlIn();
            } else {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_PINGIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_PINGIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_TXPKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            if (g_hsusbd_CtrlInSize) {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
            } else {
                if (g_hsusbd_CtrlZero == 1) {
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_ZEROLEN);
                } 
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_RXPKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_RXPKIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_NAKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_NAKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STALLIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STALLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_ERRIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_ERRIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk) {
            HSUSBD_UpdateDeviceState();
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFFULLIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFFULLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk);
            return;
        }
    }
    
    /* EPA - INT-IN */
    if (IrqStL & HSUSBD_GINTSTS_EPAIF_Msk) {
        IrqSt = HSUSBD->EP[EPA].EPINTSTS & HSUSBD->EP[EPA].EPINTEN;
        
        HSUSBD_ENABLE_EP_INT(EPA, 0);
        EPA_Handler();
        HSUSBD_CLR_EP_INT_FLAG(EPA, IrqSt);
    }
    
    /* EPB- INT-OUT */
    if (IrqStL & HSUSBD_GINTSTS_EPBIF_Msk) {
        IrqSt = HSUSBD->EP[EPB].EPINTSTS & HSUSBD->EP[EPB].EPINTEN;
        if (HSUSBD->EP[EPB].EPINTSTS & 0x10) {
            EPB_Handler();
        }
        HSUSBD_CLR_EP_INT_FLAG(EPB, IrqSt);
    }
    
    /* EPC - INT-IN */
    if (IrqStL & HSUSBD_GINTSTS_EPCIF_Msk) {
        IrqSt = HSUSBD->EP[EPC].EPINTSTS & HSUSBD->EP[EPC].EPINTEN;
        
        HSUSBD_ENABLE_EP_INT(EPC, 0);
        EPC_Handler();
        HSUSBD_CLR_EP_INT_FLAG(EPC, IrqSt);
    }
    
    /* EPD - INT-IN */
    if (IrqStL & HSUSBD_GINTSTS_EPDIF_Msk) {
        IrqSt = HSUSBD->EP[EPD].EPINTSTS & HSUSBD->EP[EPD].EPINTEN;
        
        HSUSBD_ENABLE_EP_INT(EPD, 0);
        EPD_Handler();
        HSUSBD_CLR_EP_INT_FLAG(EPD, IrqSt);
    }

    /* EPE - INT-IN */
    if (IrqStL & HSUSBD_GINTSTS_EPEIF_Msk) {
        IrqSt = HSUSBD->EP[EPE].EPINTSTS & HSUSBD->EP[EPE].EPINTEN;
        
        HSUSBD_ENABLE_EP_INT(EPE, 0);
        EPE_Handler();
        HSUSBD_CLR_EP_INT_FLAG(EPE, IrqSt);
    }
    
    /* EPF - INT-OUT */
    if (IrqStL & HSUSBD_GINTSTS_EPFIF_Msk) {
        IrqSt = HSUSBD->EP[EPF].EPINTSTS & HSUSBD->EP[EPF].EPINTEN;
        if (HSUSBD->EP[EPF].EPINTSTS & 0x10) {
            EPF_Handler();
        }
        HSUSBD_CLR_EP_INT_FLAG(EPF, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPHIF_Msk) {
        IrqSt = HSUSBD->EP[EPH].EPINTSTS & HSUSBD->EP[EPH].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPH, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPIIF_Msk) {
        IrqSt = HSUSBD->EP[EPI].EPINTSTS & HSUSBD->EP[EPI].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPI, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPJIF_Msk) {
        IrqSt = HSUSBD->EP[EPJ].EPINTSTS & HSUSBD->EP[EPJ].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPJ, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPKIF_Msk) {
        IrqSt = HSUSBD->EP[EPK].EPINTSTS & HSUSBD->EP[EPK].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPK, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPLIF_Msk) {
        IrqSt = HSUSBD->EP[EPL].EPINTSTS & HSUSBD->EP[EPL].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPL, IrqSt);
    }
}

//
// HID_Init
//
void HID_Init(void)
{
    /* Configure USB controller */
    /* Enable USB BUS, CEP ,EPA, EPB, EPC, EPD, EPE global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk | HSUSBD_GINTEN_CEPIEN_Msk |     \
        HSUSBD_GINTEN_EPAIEN_Msk | HSUSBD_GINTEN_EPBIEN_Msk | 
        HSUSBD_GINTEN_EPCIEN_Msk | HSUSBD_GINTEN_EPDIEN_Msk | 
        HSUSBD_GINTEN_EPEIEN_Msk | HSUSBD_GINTEN_EPFIEN_Msk );
    
    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk |  \
        HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    
    /* Reset Address to 0 */
    HSUSBD_SET_ADDR(0);

    /*****************************************************/
    /* Control endpoint */
    HSUSBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk | HSUSBD_CEPINTEN_STSDONEIEN_Msk);

    /*****************************************************/
    /* EPA ==> INT-IN EP, ADDR 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, KB_INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);

    /*****************************************************/
    /* EPB ==> INT-OUT EP, ADDR 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, KB_INT_OT_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, (HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_BUFFULLIEN_Msk));

    /*****************************************************/
    /* EPC ==> INT-IN EP, ADDR 3 */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, MOUSE_INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);

    /*****************************************************/
    /* EPD ==> INT-IN EP, ADDR 4 */
    HSUSBD_SetEpBufAddr(EPD, EPD_BUF_BASE, EPD_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPD, EPD_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPD, VENDOR01_INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);
    
    /*****************************************************/
    /* EPE ==> INT-IN EP, ADDR 5 */
    HSUSBD_SetEpBufAddr(EPE, EPE_BUF_BASE, EPE_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPE, EPE_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPE, VENDOR02_INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);
    
    /*****************************************************/
    /* EPF ==> INT-OUT EP, ADDR 6 */
    HSUSBD_SetEpBufAddr(EPF, EPF_BUF_BASE, EPF_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPF, EPF_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPF, VENDOR02_INT_OT_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPF, (HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_BUFFULLIEN_Msk));

    /* start to IN data */
    g_u8EPAReady = 1;
    g_u8EPBReady = 1;

    g_u8EPCReady = 1;
    g_u8EPDReady = 1;

    g_u8EPEReady = 1;
    g_u8EPFReady = 1;
}

//
// HID_ClassRequest
//
void HID_ClassRequest(void)
{
    static uint8_t u8Report = 0;
    static uint8_t u8Idle = 0;

    if (gUsbCmd.bmRequestType & 0x80) { // Device to host

        switch (gUsbCmd.bRequest) {
        case GET_REPORT:
            HSUSBD_PrepareCtrlIn(&u8Report, 1ul);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
            break;
        case GET_IDLE:
            HSUSBD_PrepareCtrlIn(&u8Idle, 1ul);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
            break;
        case GET_PROTOCOL:
            if (gUsbCmd.wIndex == 0x00) {   // interface 0
                HSUSBD_PrepareCtrlIn((uint8_t *)&g_u8ReportProtocol, 1ul);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            } else if (gUsbCmd.wIndex == 0x01) {    //interface 1
                HSUSBD_PrepareCtrlIn((uint8_t *)&g_u8ReportProtocol, 1ul);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            } else {
                // Stall
                /* Setup error, stall the device */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
                break;
            }
        default:
            // Stall
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            break;
        }
    } else {    // Host to device
        switch (gUsbCmd.bRequest) {
        case SET_REPORT:
            if (((gUsbCmd.wValue >> 8) & 0xff) == 3) {  /* Request Type = Feature */
                
                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            } else {
                // Stall
                /* Setup error, stall the device */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            }
            break;
        case SET_IDLE:
            u8Idle = (gUsbCmd.wValue >> 8) & 0xff;
        
            /* Status stage */
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            break;
        case SET_PROTOCOL:
            if (gUsbCmd.wIndex == 0x00) {   // interface 0
                if (gUsbCmd.wValue == HID_BOOT_PROTOCOL) {
                    g_u8ReportProtocol = HID_BOOT_PROTOCOL;
                } else {
                    g_u8ReportProtocol = HID_REPORT_PROTOCOL;
                }
                
                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            } else if (gUsbCmd.wIndex == 0x01) {    // interface 1
                if (gUsbCmd.wValue == HID_BOOT_PROTOCOL) {
                    g_u8ReportProtocol = HID_BOOT_PROTOCOL;
                } else {
                    g_u8ReportProtocol = HID_REPORT_PROTOCOL;
                }
                
                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            } else {
                // Stall
                /* Setup error, stall the device */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
                break;
            }
            break;
        default:
            // Stall
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            break;
        }
    }
}


//
// HID_VendorRequest
//
void HID_VendorRequest(void)
{
    /* 
     * Request Data Rransfer Direction 
     */
    if (gUsbCmd.bmRequestType & 0x80) {         // Device to Host
        switch (gUsbCmd.bRequest) {
            default:
                /* Setup error, stall the device */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
                break;
        }
    } else {        // Host to device
        switch (gUsbCmd.bRequest) {
            default:
                // Stall
                /* Setup error, stall the device */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
                break;
        }
    }
}

//
// EPA_Handler
//
void EPA_Handler(void)
{
    g_u8EPAReady = 1;
}


//
// EPB_Handler
//
void EPB_Handler(void)
{
    uint32_t len, i;
    
    len = HSUSBD->EP[EPB].EPDATCNT & 0xffff;

    for (i = 0; i < len; i++) {
        g_u8EPBOutBuff[i] = HSUSBD->EP[EPB].EPDAT_BYTE;
        printf("0x%02x ", g_u8EPBOutBuff[i]);
    }
    printf("\r\n");
}

//
// EPC_Handler
//
void EPC_Handler(void)
{
    g_u8EPCReady = 1;
}

//
// EPD_Handler
//
void EPD_Handler(void)
{
    g_u8EPDReady = 1;
}

//
// EPE_Handler
//
void EPE_Handler(void)
{
    g_u8EPEReady = 1;
}

//
// EPF_Handler
//
void EPF_Handler(void)
{
    uint32_t len, i;
    
    len = HSUSBD->EP[EPF].EPDATCNT & 0xffff;

    for (i = 0; i < len; i++) {
        g_u8EPFOutBuff[i] = HSUSBD->EP[EPF].EPDAT_BYTE;
        printf("0x%02x ", g_u8EPFOutBuff[i]);
    }
    printf("\r\n");
}

//
// HID_Handler
//
void HID_Handler(void)
{
    static uint8_t epa_test_count = 0;
    static uint8_t epd_test_count = 0;
    static uint8_t epe_test_count = 0;

    uint8_t epa_buf[4];
    uint8_t epc_buf[4];
    uint8_t epd_buf[5];
    uint8_t epe_buf[4];

    int volatile i;

    if (g_u8EPAReady) {
        /* Update new report data */
        epa_buf[0] = 0xA0;
        epa_buf[1] = 0xA1;
        epa_buf[2] = 0xA2;
        epa_buf[3] = epa_test_count++;
        g_u8EPAReady = 0;
        
        /* Set transfer length and trigger IN transfer */
        for (i = 0; i < 4; i++) {
            HSUSBD->EP[EPA].EPDAT_BYTE = epa_buf[i];
        }

        HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EP_RSPCTL_SHORTTXEN;
        HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_INTKIEN_Msk);

        printf("g_u8EPAReady\r\n");
    }
    
    if (g_u8EPCReady) {
        
        /* Update new report data */
        epc_buf[0] = 0x00;
        epc_buf[1] = 0x00;
        epc_buf[2] = 0x00;
        epc_buf[3] = 0x00;
        g_u8EPCReady = 0;
        
        /* Set transfer length and trigger IN transfer */
        for (i = 0; i < 4; i++) {
            HSUSBD->EP[EPC].EPDAT_BYTE = epc_buf[i];
        }

        HSUSBD->EP[EPC].EPRSPCTL = HSUSBD_EP_RSPCTL_SHORTTXEN;
        HSUSBD_ENABLE_EP_INT(EPC, HSUSBD_EPINTEN_INTKIEN_Msk);

        printf("g_u8EPCReady\r\n");
    }
    
    if (g_u8EPDReady) {

         /* Update new report data */
        epd_buf[0] = 0xD0;
        epd_buf[1] = 0xD1;
        epd_buf[2] = 0xD2;
        epd_buf[3] = epd_test_count++;
        g_u8EPDReady = 0;
        
        /* Set transfer length and trigger IN transfer */
        for (i = 0; i < 4; i++) {
            HSUSBD->EP[EPD].EPDAT_BYTE = epd_buf[i];
        }

        HSUSBD->EP[EPD].EPRSPCTL = HSUSBD_EP_RSPCTL_SHORTTXEN;
        HSUSBD_ENABLE_EP_INT(EPD, HSUSBD_EPINTEN_INTKIEN_Msk);

        printf("g_u8EPDReady\r\n");
    }
    
    if (g_u8EPEReady) {
        /* Update new report data */
        epe_buf[0] = 0xE0;
        epe_buf[1] = 0xE1;
        epe_buf[2] = 0xE2;
        epe_buf[3] = epe_test_count++;
        g_u8EPEReady = 0;
        
        /* Set transfer length and trigger IN transfer */
        for (i = 0; i < 4; i++) {
            HSUSBD->EP[EPE].EPDAT_BYTE = epe_buf[i];
        }

        HSUSBD->EP[EPE].EPRSPCTL = HSUSBD_EP_RSPCTL_SHORTTXEN;
        HSUSBD_ENABLE_EP_INT(EPE, HSUSBD_EPINTEN_INTKIEN_Msk);

        printf("g_u8EPEReady\r\n");
    }    

}
