//
// Includes
//
#include "NuMicro.h"
#include "kb_mouse.h"


uint8_t HID_Keyboard_ReportDescriptor[] __attribute__((aligned(4))) = {
    0x05, 0x01,     /* Usage Page(Generic Desktop Controls) */
    0x09, 0x06,     /* Usage(Keyboard) */
    0xA1, 0x01,     /* Collection(Application) */
    0x05, 0x07,         /* Usage Page(Keyboard/Keypad) */
    0x19, 0xE0,         /* Usage Minimum(0xE0) */
    0x29, 0xE7,         /* Usage Maximum(0xE7) */
    0x15, 0x00,         /* Logical Minimum(0x0) */
    0x25, 0x01,         /* Logical Maximum(0x1) */
    0x75, 0x01,         /* Report Size(0x1) */
    0x95, 0x08,         /* Report Count(0x8) */
    0x81, 0x02,         /* Input (Data) => Modifier byte */
    0x95, 0x01,         /* Report Count(0x1) */
    0x75, 0x08,         /* Report Size(0x8) */
    0x81, 0x01,         /* Input (Constant) => Reserved byte */
    0x95, 0x05,         /* Report Count(0x5) */
    0x75, 0x01,         /* Report Size(0x1) */
    0x05, 0x08,         /* Usage Page(LEDs) */
    0x19, 0x01,         /* Usage Minimum(0x1) */
    0x29, 0x05,         /* Usage Maximum(0x5) */
    0x91, 0x02,         /* Output (Data) => LED report */
    0x95, 0x01,         /* Report Count(0x1) */
    0x75, 0x03,         /* Report Size(0x3) */
    0x91, 0x01,         /* Output (Constant) => LED report padding */
    0x95, 0x06,         /* Report Count(0x6) */
    0x75, 0x08,         /* Report Size(0x8) */
    0x15, 0x00,         /* Logical Minimum(0x0) */
    0x25, 0x65,         /* Logical Maximum(0x65) */
    0x05, 0x07,         /* Usage Page(Keyboard/Keypad) */
    0x19, 0x00,         /* Usage Minimum(0x0) */
    0x29, 0x65,         /* Usage Maximum(0x65) */
    0x81, 0x00,         /* Input (Data) */
    0xC0,           /* End Collection */
};


uint8_t HID_Vendorpage1_ReportDescriptor[] __attribute__((aligned(4))) = {
    0x06, 0x06, 0xFF,       /* USAGE_PAGE (Vendor Defined)*/
    0x09, 0x01,             /* USAGE (0x01)*/
    0xA1, 0x01,             /* COLLECTION (Application)*/
    0x15, 0x00,             /* LOGICAL_MINIMUM (0)*/
    0x26, 0xFF, 0x00,       /* LOGICAL_MAXIMUM (255)*/
    0x75, 0x08,             /* REPORT_SIZE (8)*/
    0x96, 0x00, 0x02,       /* REPORT_COUNT*/
    0x09, 0x01,
    0x81, 0x02,             /* INPUT (Data,Var,Abs)*/
    0x96, 0x00, 0x02,       /* REPORT_COUNT*/
    0x09, 0x01,
    0x91, 0x02,             /* OUTPUT (Data,Var,Abs)*/
    0x95, 0x08,             /* REPORT_COUNT (8) */
    0x09, 0x01,
    0xB1, 0x02,             /* FEATURE */
    0xC0,                   /* END_COLLECTION*/
};


uint8_t HID_Mouse_ReportDescriptor[] __attribute__((aligned(4))) = {
     0x05, 0x01,     /* Usage Page(Generic Desktop Controls) */
    0x09, 0x02,     /* Usage(Mouse) */
    0xA1, 0x01,     /* Collection(Application) */
    0x09, 0x01,         /* Usage(Pointer) */
    0xA1, 0x00,         /* Collection(Physical) */
    0x05, 0x09,             /* Usage Page(Button) */
    0x19, 0x01,             /* Usage Minimum(0x1) */
    0x29, 0x03,             /* Usage Maximum(0x3) */
    0x15, 0x00,             /* Logical Minimum(0x0) */
    0x25, 0x01,             /* Logical Maximum(0x1) */
    0x75, 0x01,             /* Report Size(0x1) */
    0x95, 0x03,             /* Report Count(0x3) */
    0x81, 0x02,             /* Input(3 button bit) */
    0x75, 0x05,             /* Report Size(0x5) */
    0x95, 0x01,             /* Report Count(0x1) */
    0x81, 0x01,             /* Input(5 bit padding) */
    0x05, 0x01,             /* Usage Page(Generic Desktop Controls) */
    0x09, 0x30,             /* Usage(X) */
    0x09, 0x31,             /* Usage(Y) */
    0x09, 0x38,             /* Usage(Wheel) */
    0x15, 0x81,             /* Logical Minimum(0x81)(-127) */
    0x25, 0x7F,             /* Logical Maximum(0x7F)(127) */
    0x75, 0x08,             /* Report Size(0x8) */
    0x95, 0x03,             /* Report Count(0x3) */
    0x81, 0x06,             /* Input(1 byte wheel) */
    0xC0,               /* End Collection */
    0xC0,           /* End Collection */
};


uint8_t HID_Vendorpge2_ReportDescriptor[] __attribute__((aligned(4))) = {
    0x06, 0x01, 0xff,           // Usage Page
    0x09, 0x01,                 // Usage (Vendor Usage 1)
    0xa1, 0x01,                 // Collection (Application)

    0x09, 0x02,                 // Usage (Vendor Usage 2)
    0x75, 0x08,                 // Report Size (8)
    0x95, 0x40,                 // Report Count (64)
    0x15, 0x00,                 // Logical Minimum (0)
    0x26, 0xff, 0x00,           // Maximum (255)
    0x81, 0x02,                 // Input (Data,Var,Abs)

    0x09, 0x03,                 // Usage (Vendor Usage 3)
    0x75, 0x08,                 // Report Size (8)
    0x95, 0x40,                 // Report Count (64)
    0x15, 0x00,                 // Logical Minimum (0)
    0x26, 0xff, 0x00,           // Logical Maximum (255)
    0x91, 0x02,                 // Output (Data,Var,Abs)
    0xc0,                       // End Collection
};

//
// Device Descriptor
//
uint8_t gu8DeviceDescriptor[] __attribute__((aligned(4))) = {
    LEN_DEVICE,                 /* bLength */
    DESC_DEVICE,                /* bDescriptorType */
    0x00, 0x02,                 /* bcdUSB */
    0x00,                       /* bDeviceClass */
    0x00,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    CEP_MAX_PKT_SIZE,           /* bMaxPacketSize0 */
    USBD_VID & 0x00FF,          /* idVendor */
    ((USBD_VID & 0xFF00) >> 8),
    USBD_PID & 0x00FF,          /* idProduct */
    ((USBD_PID & 0xFF00) >> 8),
    0x00, 0x00,                 /* bcdDevice */
    0x01,                       /* iManufacture */
    0x02,                       /* iProduct */
    0x00,                       /* iSerialNumber - no serial */
    0x01                        /* bNumConfigurations */
};

//
// Config Descritptor
//
uint8_t gu8ConfigDescriptor[] __attribute__((aligned(4))) = {
    LEN_CONFIG,                             /* bLength: Configuration Descriptor size */
    DESC_CONFIG,                            /* bDescriptorType: Configuration */
    LEN_CONFIG_AND_SUBORDINATE & 0x00FF,    /* wTotalLength */
    ((LEN_CONFIG_AND_SUBORDINATE & 0xFF00) >> 8),
    0x04,                                   /*bNumInterfaces: Number of Interface count*/
    0x01,                                   /*bConfigurationValue: Configuration value*/
    0x00,                                   /*iConfiguration: Index of string descriptor describing the configuration*/
    0xA0,                                   /*bmAttributes: bus powered and Support Remote Wake-up */
    0xFA,                                   /*MaxPower 500 mA: this current is used for detecting Vbus*/
    /* 9 */

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x00,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x02,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: CUSTOM_HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_KEYBOARD,                           /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: CUSTOM_HID*/
    0x11,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Keyboard_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Keyboard_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (KB_INT_IN_EP_NUM | EP_INPUT),    /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPA_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_IN_INTERVAL,               /* bInterval */
    
    LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (KB_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPB_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_OT_INTERVAL,               /* bInterval */

    /************** Descriptor of interface ****************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x01,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    HID_MOUSE,                              /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID ********************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x10,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Mouse_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Mouse_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType:*/
    (MOUSE_INT_IN_EP_NUM | EP_INPUT),         /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPC_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPC_MAX_PKT_SIZE & 0xFF00) >> 8),
    MOUSE_INT_IN_INTERVAL,                    /*bInterval: Polling Interval (1 ms)*/

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x02,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No boot*/
    HID_NONE,                               /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x11,                                   /*bcdHID: HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Vendorpage1_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Vendorpage1_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR01_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPD_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPD_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR01_INT_IN_INTERVAL,                 /* bInterval */

    /*-------------------    #ifc4:Custom#    -------------------------*/
    LEN_INTERFACE,                  /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                 /*bDescriptorType: Interface descriptor type*/
    0x03,                           /*bInterfaceNumber: Number of Interface*/
    0x00,                           /*bAlternateSetting: Alternate setting*/
    0x02,                           /*bNumEndpoints*/
    0x03,                           /*bInterfaceClass: CUSTOM_HID*/
    0x00,                           /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_NONE,                       /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,                              /*iInterface: Index of string descriptor*/

    LEN_HID,                        /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                       /*bDescriptorType: CUSTOM_HID*/
    0x11,                           /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                           /*bCountryCode: Hardware target country*/
    0x01,                           /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                   /*bDescriptorType*/
    sizeof(HID_Vendorpge2_ReportDescriptor) & 0x00FF, /* wItemLength: Total length of Report descriptor*/
    ((sizeof(HID_Vendorpge2_ReportDescriptor) & 0xFF00) >> 8),

    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR02_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPE_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPE_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_IN_INTERVAL,                 /* bInterval */
    
	LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (VENDOR02_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPF_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPF_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_OT_INTERVAL,               /* bInterval */
};

//
// String Language
//
uint8_t gu8StringLang[4] __attribute__((aligned(4))) = {
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

//
// Vendor String Descriptor
//
uint8_t gu8VendorStringDesc[] __attribute__((aligned(4))) = {
    16,
    DESC_STRING,
    'C', 0, 'O', 0, 'R', 0, 'S', 0, 'A', 0, 'I', 0, 'R', 0
};

//
// Product String Descriptor
//
uint8_t gu8ProductStringDesc[] __attribute__((aligned(4))) = {
    22,
    DESC_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0
};

//
// Qualifier Descriptor
//
uint8_t gu8QualifierDescriptor[] __attribute__((aligned(4))) = {
    LEN_QUALIFIER,  /* bLength */
    DESC_QUALIFIER, /* bDescriptorType */
    0x00, 0x02,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    CEP_OTHER_MAX_PKT_SIZE, /* bMaxPacketSize0 */
    0x01,           /* bNumConfigurations */
    0x00
};

//
// Config Descriptor for Full-speed
//
uint8_t gu8ConfigDescriptorFS[] __attribute__((aligned(4))) = {
    LEN_CONFIG,                             /* bLength: Configuration Descriptor size */
    DESC_CONFIG,                            /* bDescriptorType: Configuration */
    LEN_CONFIG_AND_SUBORDINATE & 0x00FF,    /* wTotalLength */
    ((LEN_CONFIG_AND_SUBORDINATE & 0xFF00) >> 8),
    0x04,                                   /*bNumInterfaces: Number of Interface count*/
    0x01,                                   /*bConfigurationValue: Configuration value*/
    0x00,                                   /*iConfiguration: Index of string descriptor describing the configuration*/
    0xA0,                                   /*bmAttributes: bus powered and Support Remote Wake-up */
    0xFA,                                   /*MaxPower 500 mA: this current is used for detecting Vbus*/
    /* 9 */

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x00,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x02,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: CUSTOM_HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_KEYBOARD,                           /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: CUSTOM_HID*/
    0x11,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Keyboard_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Keyboard_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (KB_INT_IN_EP_NUM | EP_INPUT),    /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPA_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_IN_INTERVAL,               /* bInterval */
    
    LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (KB_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPB_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_OT_INTERVAL,               /* bInterval */

    /************** Descriptor of interface ****************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x01,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    HID_MOUSE,                              /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID ********************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x10,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Mouse_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Mouse_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType:*/
    (MOUSE_INT_IN_EP_NUM | EP_INPUT),         /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPC_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPC_MAX_PKT_SIZE & 0xFF00) >> 8),
    MOUSE_INT_IN_INTERVAL,                    /*bInterval: Polling Interval (1 ms)*/

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x02,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No boot*/
    HID_NONE,                               /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x11,                                   /*bcdHID: HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Vendorpage1_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Vendorpage1_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR01_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPD_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPD_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR01_INT_IN_INTERVAL,                 /* bInterval */
   
    /*-------------------    #ifc4:Custom#    -------------------------*/
    LEN_INTERFACE,                  /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                 /*bDescriptorType: Interface descriptor type*/
    0x03,                           /*bInterfaceNumber: Number of Interface*/
    0x00,                           /*bAlternateSetting: Alternate setting*/
    0x02,                           /*bNumEndpoints*/
    0x03,                           /*bInterfaceClass: CUSTOM_HID*/
    0x00,                           /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_NONE,                       /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,                              /*iInterface: Index of string descriptor*/

    LEN_HID,                        /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                       /*bDescriptorType: CUSTOM_HID*/
    0x11,                           /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                           /*bCountryCode: Hardware target country*/
    0x01,                           /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                   /*bDescriptorType*/
    sizeof(HID_Vendorpge2_ReportDescriptor) & 0x00FF, /* wItemLength: Total length of Report descriptor*/
    ((sizeof(HID_Vendorpge2_ReportDescriptor) & 0xFF00) >> 8),

    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR02_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPE_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPE_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_IN_INTERVAL,                 /* bInterval */
    
	LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (VENDOR02_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPF_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPF_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_OT_INTERVAL,               /* bInterval */
};

//
// Other Config Descriptor for High-speed
//
uint8_t gu8OtherConfigDescriptorHS[] __attribute__((aligned(4))) = {
    LEN_CONFIG,                             /* bLength: Configuration Descriptor size */
    DESC_CONFIG,                            /* bDescriptorType: Configuration */
    LEN_CONFIG_AND_SUBORDINATE & 0x00FF,    /* wTotalLength */
    ((LEN_CONFIG_AND_SUBORDINATE & 0xFF00) >> 8),
    0x04,                                   /*bNumInterfaces: Number of Interface count*/
    0x01,                                   /*bConfigurationValue: Configuration value*/
    0x00,                                   /*iConfiguration: Index of string descriptor describing the configuration*/
    0xA0,                                   /*bmAttributes: bus powered and Support Remote Wake-up */
    0xFA,                                   /*MaxPower 500 mA: this current is used for detecting Vbus*/
    /* 9 */

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x00,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x02,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: CUSTOM_HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_KEYBOARD,                           /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: CUSTOM_HID*/
    0x11,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Keyboard_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Keyboard_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (KB_INT_IN_EP_NUM | EP_INPUT),    /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPA_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_IN_INTERVAL,               /* bInterval */
    
    LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (KB_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPB_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_OT_INTERVAL,               /* bInterval */

    /************** Descriptor of interface ****************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x01,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    HID_MOUSE,                              /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID ********************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x10,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Mouse_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Mouse_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType:*/
    (MOUSE_INT_IN_EP_NUM | EP_INPUT),         /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPC_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPC_MAX_PKT_SIZE & 0xFF00) >> 8),
    MOUSE_INT_IN_INTERVAL,                    /*bInterval: Polling Interval (1 ms)*/

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x02,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No boot*/
    HID_NONE,                               /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x11,                                   /*bcdHID: HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Vendorpage1_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Vendorpage1_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR01_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPD_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPD_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR01_INT_IN_INTERVAL,                 /* bInterval */
   
    /*-------------------    #ifc4:Custom#    -------------------------*/
    LEN_INTERFACE,                  /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                 /*bDescriptorType: Interface descriptor type*/
    0x03,                           /*bInterfaceNumber: Number of Interface*/
    0x00,                           /*bAlternateSetting: Alternate setting*/
    0x02,                           /*bNumEndpoints*/
    0x03,                           /*bInterfaceClass: CUSTOM_HID*/
    0x00,                           /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_NONE,                       /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,                              /*iInterface: Index of string descriptor*/

    LEN_HID,                        /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                       /*bDescriptorType: CUSTOM_HID*/
    0x11,                           /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                           /*bCountryCode: Hardware target country*/
    0x01,                           /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                   /*bDescriptorType*/
    sizeof(HID_Vendorpge2_ReportDescriptor) & 0x00FF, /* wItemLength: Total length of Report descriptor*/
    ((sizeof(HID_Vendorpge2_ReportDescriptor) & 0xFF00) >> 8),

    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR02_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPE_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPE_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_IN_INTERVAL,                 /* bInterval */
    
	LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (VENDOR02_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPF_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPF_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_OT_INTERVAL,               /* bInterval */
};

//
// Other Config Descriptor for Full-speed
//
uint8_t gu8OtherConfigDescriptorFS[] __attribute__((aligned(4))) = {
    LEN_CONFIG,                             /* bLength: Configuration Descriptor size */
    DESC_CONFIG,                            /* bDescriptorType: Configuration */
    LEN_CONFIG_AND_SUBORDINATE & 0x00FF,    /* wTotalLength */
    ((LEN_CONFIG_AND_SUBORDINATE & 0xFF00) >> 8),
    0x04,                                   /*bNumInterfaces: Number of Interface count*/
    0x01,                                   /*bConfigurationValue: Configuration value*/
    0x00,                                   /*iConfiguration: Index of string descriptor describing the configuration*/
    0xA0,                                   /*bmAttributes: bus powered and Support Remote Wake-up */
    0xFA,                                   /*MaxPower 500 mA: this current is used for detecting Vbus*/
    /* 9 */

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x00,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x02,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: CUSTOM_HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_KEYBOARD,                           /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: CUSTOM_HID*/
    0x11,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Keyboard_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Keyboard_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (KB_INT_IN_EP_NUM | EP_INPUT),    /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPA_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_IN_INTERVAL,               /* bInterval */
    
    LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (KB_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPB_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    KB_INT_OT_INTERVAL,               /* bInterval */

    /************** Descriptor of interface ****************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x01,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    HID_MOUSE,                              /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID ********************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x10,                                   /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Mouse_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Mouse_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType:*/
    (MOUSE_INT_IN_EP_NUM | EP_INPUT),         /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPC_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPC_MAX_PKT_SIZE & 0xFF00) >> 8),
    MOUSE_INT_IN_INTERVAL,                    /*bInterval: Polling Interval (1 ms)*/

    /****************** Descriptor of interface *********************/
    LEN_INTERFACE,                          /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                         /*bDescriptorType: Interface descriptor type*/
    0x02,                                   /*bInterfaceNumber: Number of Interface*/
    0x00,                                   /*bAlternateSetting: Alternate setting*/
    0x01,                                   /*bNumEndpoints*/
    0x03,                                   /*bInterfaceClass: HID*/
    0x00,                                   /*bInterfaceSubClass : 1=Support Boot, 0=No boot*/
    HID_NONE,                               /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                                   /*iInterface: Index of string descriptor*/

    /******************** Descriptor of HID *************************/
    LEN_HID,                                /*bLength: HID Descriptor size*/
    DESC_HID,                               /*bDescriptorType: HID*/
    0x11,                                   /*bcdHID: HID Class Spec release number*/
    0x01,
    0x00,                                   /*bCountryCode: Hardware target country*/
    0x01,                                   /*bNumDescriptors: Number of HID class descriptors to follow*/
    DESC_HID_RPT,                           /*bDescriptorType*/
    sizeof(HID_Vendorpage1_ReportDescriptor) & 0x00FF, /* Total length of report descriptor. */
    ((sizeof(HID_Vendorpage1_ReportDescriptor) & 0xFF00) >> 8),

    /******************** Descriptor of endpoint ********************/
    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR01_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPD_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPD_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR01_INT_IN_INTERVAL,                 /* bInterval */
    
    /*-------------------    #ifc4:Custom#    -------------------------*/
    LEN_INTERFACE,                  /*bLength: Interface Descriptor size*/
    DESC_INTERFACE,                 /*bDescriptorType: Interface descriptor type*/
    0x03,                           /*bInterfaceNumber: Number of Interface*/
    0x00,                           /*bAlternateSetting: Alternate setting*/
    0x02,                           /*bNumEndpoints*/
    0x03,                           /*bInterfaceClass: CUSTOM_HID*/
    0x00,                           /*bInterfaceSubClass : 1=Support Boot, 0=No Boot*/
    HID_NONE,                       /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,                              /*iInterface: Index of string descriptor*/

    LEN_HID,                        /*bLength: CUSTOM_HID Descriptor size*/
    DESC_HID,                       /*bDescriptorType: CUSTOM_HID*/
    0x11,                           /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
    0x01,
    0x00,                           /*bCountryCode: Hardware target country*/
    0x01,                           /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
    DESC_HID_RPT,                   /*bDescriptorType*/
    sizeof(HID_Vendorpge2_ReportDescriptor) & 0x00FF, /* wItemLength: Total length of Report descriptor*/
    ((sizeof(HID_Vendorpge2_ReportDescriptor) & 0xFF00) >> 8),

    LEN_ENDPOINT,                           /*bLength: Endpoint Descriptor size*/
    DESC_ENDPOINT,                          /*bDescriptorType */
    (VENDOR02_INT_IN_EP_NUM | EP_INPUT),       /*bEndpointAddress: Endpoint Address (IN)*/
    EP_INT,                                 /*bmAttributes: Interrupt endpoint*/
    EPE_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPE_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_IN_INTERVAL,                 /* bInterval */
    
	LEN_ENDPOINT,                           /* bLength: Endpoint Descriptor size */
    DESC_ENDPOINT,                          /* bDescriptorType */
    (VENDOR02_INT_OT_EP_NUM | EP_OUTPUT),   /*bEndpointAddress: Endpoint Address (OUT)*/
    EP_INT,                                 /* bmAttributes: Interrupt endpoint */
    EPF_MAX_PKT_SIZE & 0x00FF,              /* wMaxPacketSize*/
    ((EPF_MAX_PKT_SIZE & 0xFF00) >> 8),
    VENDOR02_INT_OT_INTERVAL,               /* bInterval */
};

//
// USB HID Report Descriptor
//
uint8_t *gu8UsbHidReport[4] = {
    HID_Keyboard_ReportDescriptor,
    HID_Mouse_ReportDescriptor,
    HID_Vendorpage1_ReportDescriptor,
    HID_Vendorpge2_ReportDescriptor,
};

//
// HID Report Descriptor Length
//
uint32_t gu32UsbHidReportLen[4] = {
    sizeof(HID_Keyboard_ReportDescriptor),
    sizeof(HID_Mouse_ReportDescriptor),
    sizeof(HID_Vendorpage1_ReportDescriptor),
    sizeof(HID_Vendorpge2_ReportDescriptor),     
};

//
// Config HID Descriptor Index
//
uint32_t gu32ConfigHidDescIdx[4] =
{
    (LEN_CONFIG + LEN_INTERFACE),
    (sizeof(gu8ConfigDescriptor) - LEN_HID*1 - LEN_ENDPOINT*2),
    (sizeof(gu8ConfigDescriptor) - LEN_HID*2 - LEN_ENDPOINT*2),
    (sizeof(gu8ConfigDescriptor) - LEN_HID*3 - LEN_ENDPOINT*2),
};

//
// USB String
//
uint8_t *gpu8UsbString[4] = {
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    NULL,
};

S_HSUSBD_INFO_T gsHSInfo = {
    gu8DeviceDescriptor,
    gu8ConfigDescriptor,
    gpu8UsbString,
    gu8QualifierDescriptor,
    gu8ConfigDescriptorFS,
    gu8OtherConfigDescriptorHS,
    gu8OtherConfigDescriptorFS,
    gu8UsbHidReport,
    gu32UsbHidReportLen,
    gu32ConfigHidDescIdx,
};
