#ifndef __KB_MOUSE_H__
#define __KB_MOUSE_H__

/* Define the vendor id and product id */
#define USBD_VID                0x1B1C
#define USBD_PID                0x5678

/*!<Define HID Class Specific Request */
#define GET_REPORT              0x01
#define GET_IDLE                0x02
#define GET_PROTOCOL            0x03
#define SET_REPORT              0x09
#define SET_IDLE                0x0A
#define SET_PROTOCOL            0x0B

/*!<USB HID Interface Class protocol */
#define HID_NONE                0x00
#define HID_KEYBOARD            0x01
#define HID_MOUSE               0x02

/*!<USB HID Class Report Type */
#define HID_RPT_TYPE_INPUT      0x01
#define HID_RPT_TYPE_OUTPUT     0x02
#define HID_RPT_TYPE_FEATURE    0x03

/*!<USB HID Protocol Type */
#define HID_BOOT_PROTOCOL       0x00
#define HID_REPORT_PROTOCOL     0x01

/*-------------------------------------------------------------*/
/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE        64
#define CEP_OTHER_MAX_PKT_SIZE  64

#define EPA_MAX_PKT_SIZE        64
#define EPA_OTHER_MAX_PKT_SIZE  64

#define EPB_MAX_PKT_SIZE        64
#define EPB_OTHER_MAX_PKT_SIZE  64

#define EPC_MAX_PKT_SIZE        64
#define EPC_OTHER_MAX_PKT_SIZE  64

#define EPD_MAX_PKT_SIZE        64
#define EPD_OTHER_MAX_PKT_SIZE  64

#define EPE_MAX_PKT_SIZE        64
#define EPE_OTHER_MAX_PKT_SIZE  64

#define EPF_MAX_PKT_SIZE        64
#define EPF_OTHER_MAX_PKT_SIZE  64

// #define EPG_MAX_PKT_SIZE        64
// #define EPG_OTHER_MAX_PKT_SIZE  64

#define CEP_BUF_BASE            (0)
#define CEP_BUF_LEN             CEP_MAX_PKT_SIZE

#define EPA_BUF_BASE            0x200   //(CEP_BUF_BASE + CEP_BUF_LEN)
#define EPA_BUF_LEN             EPA_MAX_PKT_SIZE

#define EPB_BUF_BASE            (EPA_BUF_BASE + 0x400)   //(EPA_BUF_BASE + EPA_BUF_LEN)
#define EPB_BUF_LEN             EPB_MAX_PKT_SIZE

#define EPC_BUF_BASE            (EPB_BUF_BASE + 0x400)   //(EPB_BUF_BASE + EPB_BUF_LEN)
#define EPC_BUF_LEN             EPC_MAX_PKT_SIZE

#define EPD_BUF_BASE            (EPC_BUF_BASE + 0x400)   //(EPC_BUF_BASE + EPC_BUF_LEN)
#define EPD_BUF_LEN             EPD_MAX_PKT_SIZE

#define EPE_BUF_BASE            (EPD_BUF_BASE + 0x400)   //(EPD_BUF_BASE + EPD_BUF_LEN)
#define EPE_BUF_LEN             EPE_MAX_PKT_SIZE

#define EPF_BUF_BASE            (EPE_BUF_BASE + 0x400)   //(EPE_BUF_BASE + EPE_BUF_LEN)
#define EPF_BUF_LEN             EPF_MAX_PKT_SIZE

// #define EPG_BUF_BASE            (EPF_BUF_BASE + EPF_BUF_LEN)
// #define EPG_BUF_LEN             EPG_MAX_PKT_SIZE

/*
    TARGET 
    EP1 : KEYBOARD IN/OUT
    EP2 : MOUSE IN
    EP3 : VENDORPAGE IN
    EP4 : VENDORPAGE IN/OUT

*/

#define INTERFACE_NUM               (4)
#define INTERFACE_1                 (0)
#define INTERFACE_2                 (1)
#define INTERFACE_3                 (2)
#define INTERFACE_4                 (3)

#define INTERFACE_1_EP_CNT          (2) // KEYBOARD IN/OUT
#define INTERFACE_2_EP_CNT          (1) // MOUSE IN
#define INTERFACE_3_EP_CNT          (1) // VENDORPAGE IN
#define INTERFACE_4_EP_CNT          (2) // VENDORPAGE IN/OUT

/* KEYBOARD <EPA/EPB> */
#define KB_INT_IN_EP_NUM            0x01
#define KB_INT_IN_INTERVAL          0x01

#define KB_INT_OT_EP_NUM            0x02
#define KB_INT_OT_INTERVAL          0x01

/* MOUSE <EPC> */
#define MOUSE_INT_IN_EP_NUM         0x03
#define MOUSE_INT_IN_INTERVAL       0x01

/* VENDORPAGE <EPD> */
#define VENDOR01_INT_IN_EP_NUM      0x04
#define VENDOR01_INT_IN_INTERVAL    0x01

/* VENDORPAGE  <EPE/EPF>*/
#define VENDOR02_INT_IN_EP_NUM      0x05
#define VENDOR02_INT_IN_INTERVAL    0x01

#define VENDOR02_INT_OT_EP_NUM      0x06
#define VENDOR02_INT_OT_INTERVAL    0x01

#define USBD_SELF_POWERED           0
#define USBD_REMOTE_WAKEUP          0
#define USBD_MAX_POWER              50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

/* Define Descriptor information */
#define LEN_CONFIG_AND_SUBORDINATE      (LEN_CONFIG + (LEN_INTERFACE*4) + (LEN_HID*4) + (LEN_ENDPOINT*6))

/* Others Report ID */
#define CONSUMER_REPORT_ID  0x01
#define SYSTEM_REPORT_ID    0x02
#define CUSTOMER_REPORT_ID  0x03
#define MOUSE_REPORT_ID     0x04

#define REPORT_CUSTOM_SIZE  0x01


void HID_InitForHighSpeed(void);
void HID_InitForFullSpeed(void);

void HID_Init(void);
void HID_ClassRequest(void);
void HID_VendorRequest(void);
void HID_Handler(void);

#endif
