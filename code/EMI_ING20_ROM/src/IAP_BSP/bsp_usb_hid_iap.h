#ifndef __USB_H
#define __USB_H

#include <stdint.h>
#include "ingsoc.h"
#include "IAP_UserDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USER_DEF_USB_VID
#define MY_USB_VID			(0x36B0)
#else
#define MY_USB_VID			USER_DEF_USB_VID
#endif

#ifndef USER_DEF_USB_PID
#define MY_USB_PID			(0x3002)
#else
#define MY_USB_PID			USER_DEF_USB_PID
#endif

#ifndef USER_DEF_USB_PID
#define MY_USB_VERSION		(0x0100)
#else
#define MY_USB_VERSION		USER_DEF_USB_VERSION
#endif

#ifndef USER_DEF_IAP_REPORT_ID
#define CTL_REPORT_ID       (0x3F)
#else
#define CTL_REPORT_ID       USER_DEF_IAP_REPORT_ID
#endif

// ATTENTION ! FIXED IO FOR USB on 916 series
#define USB_PIN_DP GIO_GPIO_16
#define USB_PIN_DM GIO_GPIO_17

#define USB_STRING_LANGUAGE_IDX		0x00
#define USB_STRING_LANGUAGE			{0x04, 0x03, 0x09, 0x04}

#define USB_STRING_MANUFACTURER_IDX	0x01
#define USB_STRING_MANUFACTURER {18,0x3,'I',0,'n',0,'g',0,'c',0,'h',0,'i',0,'p',0,'s',0}

#define USB_STRING_PRODUCT_IDX		0x02
#define USB_STRING_PRODUCT {12,0x3,'M',0,'o',0,'u',0,'s',0,'e',0}

typedef enum
{
    USB_REQUEST_HID_CLASS_DESCRIPTOR_HID = 0x21,
    USB_REQUEST_HID_CLASS_DESCRIPTOR_REPORT = 0x22,
    USB_REQUEST_HID_CLASS_DESCRIPTOR_PHYSICAL_DESCRIPTOR = 0x23
} USB_REQUEST_HID_CLASS_DESCRIPTOR_TYPES_E ;

typedef enum
{
    USB_REQUEST_HID_CLASS_REQUEST_REPORT_INPUT = 0x01,
    USB_REQUEST_HID_CLASS_REQUEST_REPORT_OUTPUT = 0x02,
    USB_REQUEST_HID_CLASS_REQUEST_REPORT_FEATURE = 0x03
} USB_REQUEST_HID_CLASS_REQUEST_REPORT_TYPE_E ;

typedef enum
{
    USB_REQUEST_HID_CLASS_REQUEST_GET_REPORT = 0x01,
    USB_REQUEST_HID_CLASS_REQUEST_GET_IDLE = 0x02,
    USB_REQUEST_HID_CLASS_REQUEST_GET_PROTOCOL = 0x03,
    USB_REQUEST_HID_CLASS_REQUEST_SET_REPORT = 0x09,
    USB_REQUEST_HID_CLASS_REQUEST_SET_IDLE = 0x0A,
    USB_REQUEST_HID_CLASS_REQUEST_SET_PROTOCOL = 0x0B
} USB_REQUEST_HID_CLASS_REQUEST_TYPES_E ;

// =============================================================================
/// HID Class descriptor structure HID 类描述符
// =============================================================================
typedef struct __attribute__((packed))
{
	uint8_t    size;        //HID 类述符长度 0x09
	uint8_t    type;        //HID 类述符类型 0x21
	uint16_t   bcd;         //HID 版本 两个字节
	uint8_t    countryCode; //设备所适用地区
	uint8_t    nbDescriptor;//下级描述符数量
	uint8_t    classType0;  //下级描述符类型 0x22报表描述符 0x23物理描述符
	uint16_t   classlength0;//下级描述符总长度 高位在前
} BSP_USB_HID_DESCRIPTOR_T;

#define EP_X_MPS_BYTES (64)

#define KB_INTERFACES_NUM   (1)
#define HOST_INTERFACES_NUM (1)
#define CTL_INTERFACES_NUM  (1)
#define bNUM_INTERFACES		(KB_INTERFACES_NUM + HOST_INTERFACES_NUM + CTL_INTERFACES_NUM)

#define KB_INTERFACE_IDX    (0x00)
#define bNUM_EP_KB          (1)
#define EP_KB_IN            (1)/* EP1 is in */
#define EP_KB_IDX_GET(x)    (x - EP_KB_IN) // ep_kb[x]
#define EP_KB_MPS_BYTES     (8)

#define HOST_INTERFACE_IDX 	(0x01)
#define bNUM_EP_HOST         (2)
#define EP_HOST_IN           (2)/* EP2 is in */
#define EP_HOST_OUT          (2)/* EP2 is out */
#define EP_HOST_IDX_GET(x)   (x - EP_HOST_IN) // ep_ctl[x]
#define EP_HOST_MPS_BYTES    (32)

#define CTL_INTERFACE_IDX   (0x02)
#define bNUM_EP_CTL         (2)
#define EP_CTL_IN           (3)/* EP3 is in */
#define EP_CTL_OUT          (3)/* EP3 is out */
#define EP_CTL_IDX_GET(x)   (x - EP_CTL_IN) // ep_ctl[x]
#define EP_CTL_MPS_BYTES    (64)


/*此结构体是USB配置描述符集*/
// =======================================================================================
typedef struct __attribute__((packed))
{
	USB_CONFIG_DESCRIPTOR_REAL_T	config;					/* 配置描述符头九个字节*/

	/*第一个Interface 0*/
	USB_INTERFACE_DESCRIPTOR_REAL_T	interface_kb;			/*描述符头九个字节*/
	BSP_USB_HID_DESCRIPTOR_T		hid_kb;					/*报表描述符集合九个字节*/
	USB_EP_DESCRIPTOR_REAL_T		ep_kb[bNUM_EP_KB];		/*端点描述符七个字节*/

	/*第二个Interface 1*/
	USB_INTERFACE_DESCRIPTOR_REAL_T	interface_host;			/*描述符头九个字节*/
	BSP_USB_HID_DESCRIPTOR_T		hid_host;				/*报表描述符集合九个字节*/
	USB_EP_DESCRIPTOR_REAL_T		ep_host[bNUM_EP_HOST];	/*端点描述符七个字节*/
	
	/*第三个Interface 2*/									
    USB_INTERFACE_DESCRIPTOR_REAL_T interface_ctl;			/*描述符头九个字节*/
    BSP_USB_HID_DESCRIPTOR_T 		hid_ctl;				/*报表描述符集合九个字节*/
    USB_EP_DESCRIPTOR_REAL_T 		ep_ctl[bNUM_EP_CTL];	/*端点描述符七个字节*/

}BSP_USB_DESC_STRUCTURE_T;

#define SELF_POWERED (0)
#define REMOTE_WAKEUP (1)

// =======================================================================================
/*初始化设备描述符*/
#define USB_DEVICE_DESCRIPTOR \
{	\
	.size = sizeof(USB_DEVICE_DESCRIPTOR_REAL_T),			/* bLength */			\
	.type = 1, 												/* bDescriptorType */	\
	.bcdUsb = 0x0200, 										/* 2.00 */	/* bcdUSB */\
	.usbClass = 0x00, 										/* bDeviceClass */		\
	.usbSubClass = 0x00, 									/* bDeviceSubClass */	\
	.usbProto = 0x00,										/* bDeviceProtocol */	\
	.ep0Mps = USB_EP0_MPS, 									/* bMaxPacketSize0 */	\
	.vendor = MY_USB_VID, 									/* idVendor */			\
	.product = MY_USB_PID, 									/* idProduct */			\
	.release = MY_USB_VERSION, 								/* bcdDevice */			\
	.iManufacturer = USB_STRING_MANUFACTURER_IDX,			/* iManufacturer */		\
	.iProduct = USB_STRING_PRODUCT_IDX, 					/* iProduct */			\
	.iSerial = 0x00, 										/* iSerialNumber */		\
	.nbConfig = 0x01 										/* bNumConfigurations: one possible configuration*/\
}

// =======================================================================================
/*初始化配置描述符*/
#define USB_CONFIG_DESCRIPTOR \
{	\
    .size = sizeof(USB_CONFIG_DESCRIPTOR_REAL_T), 			/*配置描述符长度九个字节*/\
    .type = 2,	                                     		/*配置描述符类型是2*/\
    .totalLength = sizeof(BSP_USB_DESC_STRUCTURE_T), 		/*配置描述符总长度是多少 此位占用两个字节*/\
    .nbInterface = bNUM_INTERFACES, 						/*有几个接口*/\
    .configIndex = 0x01, 									/*配置描述符编号 1*/\
    .iDescription = 0x00,									/*配置描述符字符串*/\
    .attrib = 0x80 | (SELF_POWERED<<6) | (REMOTE_WAKEUP<<5),/*选择USB总线供电 支持远程唤醒*/\
    .maxPower = 0x0A 										/*20mA做大工作电流*/\
}

// =======================================================================================
//初始化 interface 0 接口描述符
#define USB_INTERFACE_DESCRIPTOR_KB \
{	\
	.size = sizeof(USB_INTERFACE_DESCRIPTOR_REAL_T),		/*接口描述符长度 0x09*/\
	.type = 4, 												/*接口描述符类型 0x04*/\
	.interfaceIndex = KB_INTERFACE_IDX, 					/*接口编号 从0开始*/\
	.alternateSetting = 0x00, 								/*备用编号 一般不用*/\
	.nbEp = bNUM_EP_KB,   									/*这个接口用了几个端点*/\
	.usbClass = 0x03, 										/*后面三个字节都是USB协议版本*/\
	.usbSubClass = 0x01, 									/*是否支持BIOS 0: no subclass, 1: boot interface*/\
	.usbProto = 0x01, 										/*鼠标协议选0x02 键盘协议选0x01 0: none*/\
	.iDescription = 0x00 									/*接口描述符字符串*/\
}

//初始化 interface 0 类描述符
#define USB_HID_DESCRIPTOR_KB \
{	\
	.size = sizeof(BSP_USB_HID_DESCRIPTOR_T),				/*HID 类述符长度 0x09*/\
	.type = 0x21, 											/*HID 类述符类型 0x21*/\
	.bcd = 0x111, 											/*HID 版本 两个字节*/\
	.countryCode = 0x00, 									/*设备所适用地区*/\
	.nbDescriptor = 0x01,									/*下级描述符数量*/\
	.classType0 = 0x22, 									/*下级描述符类型 0x22报表描述符 0x23物理描述符*/\
	.classlength0 = USB_HID_KB_REPORT_DESCRIPTOR_SIZE		/*下级描述符总长度 高位在前*/\
}

//初始化 interface 0 IN 端点描述符
#define USB_EP_IN_DESCRIPTOR_KB \
{	\
	.size = sizeof(USB_EP_DESCRIPTOR_REAL_T),				/*端点描述符长度 0x07*/\
	.type = 5, 												/*端点描述符类型 0x05*/\
	.ep = USB_EP_DIRECTION_IN(EP_KB_IN), 					/*bit8 1:IN 0:OUT 使用哪个USB端点*/\
	.attributes = USB_EP_TYPE_INTERRUPT, 					/*传输方式 控制传输、中断传输、批量传输*/\
	.mps = EP_KB_MPS_BYTES, 								/*传输一包的长度 byte键盘默认8个字节*/\
	.interval = 0x1 										/*传输间隔*/\
}

/* interface 0 Byte 键盘 报表描述符集*/
#define USB_HID_KB_REPORT_DESCRIPTOR_SIZE (68)
#define USB_HID_KB_REPORT_DESCRIPTOR {						\
	HID_UsagePage(HID_USAGE_PAGE_GENERIC),					\
	HID_Usage(HID_USAGE_GENERIC_KEYBOARD),					\
	HID_Collection(HID_Application),						\
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),				\
		HID_UsageMin(HID_USAGE_KEYBOARD_LCTRL),				\
		HID_UsageMax(HID_USAGE_KEYBOARD_RGUI),				\
		HID_LogicalMin(0), 									\
		HID_LogicalMax(1), 									\
		HID_ReportCount(8),									\
		HID_ReportSize(1),									\
		HID_Input(HID_Data|HID_Variable|HID_Absolute),		\
		HID_ReportCount(1),									\
		HID_ReportSize(8),									\
		HID_Input(HID_Constant|HID_Array|HID_Absolute),		\
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),				\
		HID_UsageMin(0x00),									\
		HID_UsageMax(0xff),									\
		HID_LogicalMin(0), 									\
		HID_LogicalMaxS(0x00FF), 							\
		HID_ReportCount(6),									\
		HID_ReportSize(8),									\
		HID_Input(HID_Data|HID_Array|HID_Absolute),			\
		HID_UsagePage(HID_USAGE_PAGE_LED),					\
		HID_UsageMin(HID_USAGE_LED_NUM_LOCK),				\
		HID_UsageMax(HID_USAGE_LED_KANA),					\
		HID_LogicalMin(0),									\
		HID_LogicalMax(1),									\
		HID_ReportCount(5),									\
		HID_ReportSize(1),									\
		HID_Output(HID_Data|HID_Variable|HID_Absolute),		\
		HID_ReportCount(1), 								\
		HID_ReportSize(3),									\
		HID_Output(HID_Constant|HID_Array|HID_Absolute),	\
	HID_EndCollection,										\
}

// =======================================================================================
//初始化 interface 1 接口描述符
#define USB_INTERFACE_DESCRIPTOR_HOST \
{	\
	.size = sizeof(USB_INTERFACE_DESCRIPTOR_REAL_T),		/*接口描述符长度 0x09*/\
	.type = 4, 												/*接口描述符类型 0x04*/\
	.interfaceIndex = HOST_INTERFACE_IDX, 					/*接口编号 从0开始*/\
	.alternateSetting = 0x00, 								/*备用编号 一般不用*/\
	.nbEp = bNUM_EP_HOST,   									/*这个接口用了几个端点*/\
	.usbClass = 0x03, 										/*后面三个字节都是USB协议版本*/\
	.usbSubClass = 0x00, 									/*是否支持BIOS 0: no subclass, 1: boot interface*/\
	.usbProto = 0x00, 										/*鼠标协议选0x02 键盘协议选0x01 0: none*/\
	.iDescription = 0x00 									/*接口描述符字符串*/\
}

//初始化 interface 1 类描述符
#define USB_HID_DESCRIPTOR_HOST \
{	\
	.size = sizeof(BSP_USB_HID_DESCRIPTOR_T),				/*HID 类述符长度 0x09*/\
	.type = 0x21, 											/*HID 类述符类型 0x21*/\
	.bcd = 0x111, 											/*HID 版本 两个字节*/\
	.countryCode = 0x00, 									/*设备所适用地区*/\
	.nbDescriptor = 0x01,									/*下级描述符数量*/\
	.classType0 = 0x22, 									/*下级描述符类型 0x22报表描述符 0x23物理描述符*/\
	.classlength0 = USB_HID_HOST_REPORT_DESCRIPTOR_SIZE		/*下级描述符总长度 高位在前*/\
}

//初始化 interface 1 IN 端点描述符
#define USB_EP_IN_DESCRIPTOR_HOST \
{	\
	.size = sizeof(USB_EP_DESCRIPTOR_REAL_T),				/*端点描述符长度 0x07*/\
	.type = 5, 												/*端点描述符类型 0x05*/\
	.ep = USB_EP_DIRECTION_IN(EP_HOST_IN), 					/*bit8 1:IN 0:OUT 使用哪个USB端点*/\
	.attributes = USB_EP_TYPE_INTERRUPT, 					/*传输方式 控制传输、中断传输、批量传输*/\
	.mps = EP_HOST_MPS_BYTES, 								/*传输一包的长度 byte键盘默认8个字节*/\
	.interval = 0x4 										/*传输间隔*/\
}

//初始化 interface 1 OUT 端点描述符
#define USB_EP_OUT_DESCRIPTOR_HOST \
{	\
    .size = sizeof(USB_EP_DESCRIPTOR_REAL_T),				/*端点描述符长度 0x07*/\
    .type = 5, 												/*端点描述符类型 0x05*/\
    .ep = USB_EP_DIRECTION_OUT(EP_HOST_OUT), 				/*bit8 1:IN 0:OUT 使用哪个USB端点*/\
    .attributes = USB_EP_TYPE_INTERRUPT, 					/*传输方式 控制传输、中断传输、批量传输*/\
    .mps = EP_HOST_MPS_BYTES, 								/*传输一包的长度 byte键盘默认8个字节*/\
    .interval = 0x4 										/*传输间隔*/\
}

/* interface 1 HOST 报表描述符集*/
#define USB_HID_HOST_REPORT_DESCRIPTOR_SIZE (34)
#define USB_HID_HOST_REPORT_DESCRIPTOR {						\
	HID_UsagePageVendor(0x60),                              \
	HID_Usage(0x61),                                        \
	HID_Collection(HID_Application),                        \
		HID_Usage(0x62),                                    \
		HID_LogicalMin(0),                                  \
	    HID_LogicalMaxS(0x00FF),                            \
		HID_ReportCount(32),                                \
	    HID_ReportSize(8),                                  \
		HID_Input(HID_Data|HID_Variable|HID_Absolute),      \
		HID_Usage(0x63),                                    \
		HID_LogicalMin(0),                                  \
	    HID_LogicalMaxS(0x00FF),                            \
		HID_ReportCount(32),                                \
	    HID_ReportSize(8),                                  \
		HID_Output(HID_Data|HID_Variable|HID_Absolute),     \
	HID_EndCollection, 										\
}

// =======================================================================================
//初始化 interface 2 接口描述符
#define USB_INTERFACE_DESCRIPTOR_CTL \
{	\
    .size = sizeof(USB_INTERFACE_DESCRIPTOR_REAL_T),		/*接口描述符长度 0x09*/\
    .type = 4, 												/*接口描述符类型 0x04*/\
    .interfaceIndex = CTL_INTERFACE_IDX, 					/*接口编号 从0开始*/\
    .alternateSetting = 0x00, 								/*备用编号 一般不用*/\
    .nbEp = bNUM_EP_CTL,    								/*这个接口用了几个端点*/\
    .usbClass = 0x03, 										/*后面三个字节都是USB协议版本*/\
	.usbSubClass = 0x01, 									/*是否支持BIOS 0: no subclass, 1: boot interface*/\
	.usbProto = 0x01, 										/*鼠标协议选0x02 键盘协议选0x01 0: none*/\
	.iDescription = 0x00 									/*接口描述符字符串*/\
}

//初始化 interface 2 类描述符
#define USB_HID_DESCRIPTOR_CTL \
{	\
    .size = sizeof(BSP_USB_HID_DESCRIPTOR_T),				/*HID 类述符长度 0x09*/\
    .type = 0x21, 											/*HID 类述符类型 0x21*/\
    .bcd = 0x111, 											/*HID 版本 两个字节*/\
    .countryCode = 0x00, 									/*设备所适用地区*/\
    .nbDescriptor = 0x01, 									/*下级描述符数量*/\
    .classType0 = 0x22, 									/*下级描述符类型 0x22报表描述符 0x23物理描述符*/\
    .classlength0 = USB_HID_CTL_REPORT_DESCRIPTOR_SIZE		/*下级描述符总长度 高位在前*/\
}

//初始化 interface 2 IN 端点描述符
#define USB_EP_IN_DESCRIPTOR_CTL \
{	\
	.size = sizeof(USB_EP_DESCRIPTOR_REAL_T),				/*端点描述符长度 0x07*/\
	.type = 5, 												/*端点描述符类型 0x05*/\
	.ep = USB_EP_DIRECTION_IN(EP_CTL_IN), 					/*bit8 1:IN 0:OUT 使用哪个USB端点*/\
	.attributes = USB_EP_TYPE_INTERRUPT, 					/*传输方式 控制传输、中断传输、批量传输*/\
	.mps = EP_CTL_MPS_BYTES, 								/*传输一包的长度 byte键盘默认8个字节*/\
	.interval = 0x1											/*传输间隔*/\
}

//初始化 interface 2 OUT 端点描述符
#define USB_EP_OUT_DESCRIPTOR_CTL \
{	\
    .size = sizeof(USB_EP_DESCRIPTOR_REAL_T),				/*端点描述符长度 0x07*/\
    .type = 5, 												/*端点描述符类型 0x05*/\
    .ep = USB_EP_DIRECTION_OUT(EP_CTL_OUT), 				/*bit8 1:IN 0:OUT 使用哪个USB端点*/\
    .attributes = USB_EP_TYPE_INTERRUPT, 					/*传输方式 控制传输、中断传输、批量传输*/\
    .mps = EP_CTL_MPS_BYTES, 								/*传输一包的长度 byte键盘默认8个字节*/\
    .interval = 0x4 										/*传输间隔*/\
}

/******************************************************************
	底层每次中断发送的长度为64字节，其中第一字节必须是report id，
	所以有效字节是后续63字节，所以IN和OUT均设为63.
********************************************************************/
#define MAX_REPORT_SIZE     63 		// WITHOUT REPORT ID.
#define KB_REPORT_ID        0x06    // Extend keyboard report ID.
#define SYS_REPORT_ID     	0x03    // Extend System   report ID.
#define CON_REPORT_ID     	0x04    // Extend Consumer report ID.
#define MOUSE_REPORT_ID  	0x02    // Extend mouse	   report ID.

#define KB_REPORT_SIZE     	(59)
#define SYS_REPORT_SIZE   	(25)
#define CON_REPORT_SIZE   	(25)
#define MOUSE_REPORT_SIZE	(75)
#define IAP_REPORT_SIZE		(29)

#define USB_HID_CTL_REPORT_DESCRIPTOR_SIZE (KB_REPORT_SIZE + SYS_REPORT_SIZE + CON_REPORT_SIZE + MOUSE_REPORT_SIZE + IAP_REPORT_SIZE)
#define USB_HID_CTL_REPORT_DESCRIPTOR {							\
	/* 73 byte mouse 鼠标事件*/                                	\
	HID_UsagePage(HID_USAGE_PAGE_GENERIC),                      \
	HID_Usage(HID_USAGE_GENERIC_MOUSE),                         \
	HID_Collection(HID_Application),                            \
		HID_ReportID(MOUSE_REPORT_ID),                          \
		HID_Usage(HID_USAGE_GENERIC_POINTER),                   \
		HID_Collection(HID_Physical),                           \
			/*第 1 字节修饰鼠标按键*/                           \
			HID_UsagePage(HID_USAGE_PAGE_BUTTON),               \
			HID_UsageMin(1),                                    \
			HID_UsageMax(8),                                    \
			HID_LogicalMin(0),                                  \
			HID_LogicalMax(1),                                  \
			HID_ReportCount(8),                                 \
			HID_ReportSize(1),                                  \
			HID_Input(HID_Data|HID_Variable|HID_Absolute),      \
			                                                    \
			/*第 23(x) 45(y) 字节修饰鼠标移动方向*/              \
			HID_UsagePage(HID_USAGE_PAGE_GENERIC),              \
			HID_Usage(HID_USAGE_GENERIC_X),                     \
			HID_Usage(HID_USAGE_GENERIC_Y),                     \
			HID_LogicalMinS(0x8000),                            \
			HID_LogicalMaxS(0x7FFF),                            \
			HID_ReportCount(2),                                 \
			HID_ReportSize(16),                                 \
			HID_Input(HID_Data|HID_Variable|HID_Relative),      \
                                                                \
			/*第 6 字节修饰鼠标滚轮*/                           \
			HID_Usage(HID_USAGE_GENERIC_WHEEL),                 \
			HID_LogicalMin(0x81),                             	\
			HID_LogicalMax(0x7F),                             	\
			HID_ReportCount(1),                                 \
			HID_ReportSize(8),                                  \
			HID_Input(HID_Data|HID_Variable|HID_Relative),      \
																\
			/*第 7 字节修饰鼠标摇摆*/                           \
			HID_UsagePage(HID_USAGE_PAGE_CONSUMER),            	\
			HID_UsageS(0x0238),	                              	\
			HID_LogicalMin(0x81),                             	\
			HID_LogicalMax(0x7F),                             	\
			HID_ReportCount(1),                                 \
			HID_ReportSize(8),                                  \
			HID_Input(HID_Data|HID_Variable|HID_Relative),		\
		HID_EndCollection,										\
	HID_EndCollection,											\
																\
	/* 25 byte system control 系统类*/ 							\
	HID_UsagePage(HID_USAGE_PAGE_GENERIC),                      \
	HID_Usage(HID_USAGE_GENERIC_SYSTEM_CTL),                    \
	HID_Collection(HID_Application),                            \
		HID_ReportID(SYS_REPORT_ID),                            \
		HID_UsageMin(1),                                        \
		HID_UsageMaxS(0x00B7),                                  \
		HID_LogicalMin(1),                                      \
		HID_LogicalMaxS(0x00B7),                                \
		HID_ReportCount(1),                                     \
		HID_ReportSize(16),                                     \
		HID_Input(HID_Data|HID_Array|HID_Absolute),             \
	HID_EndCollection,											\
																\
	/* 25 byte Consumer 多媒体类*/   							\
    HID_UsagePage(HID_USAGE_PAGE_CONSUMER),						\
    HID_Usage(HID_USAGE_CONSUMER_CONTROL),						\
    HID_Collection(HID_Application),        					\
		HID_ReportID(CON_REPORT_ID),							\
		HID_UsageMin(HID_USAGE_CONSUMER_CONTROL),    	        \
		HID_UsageMaxS(0x02A0),                                  \
		HID_LogicalMin(1),        								\
		HID_LogicalMaxS(0x02A0),        						\
		HID_ReportCount(1),										\
        HID_ReportSize(16),										\
		HID_Input(HID_Data|HID_Array|HID_Absolute),             \
	HID_EndCollection,											\
																\
	/* 59 byte 按键类型*/ 										\
	HID_UsagePage(HID_USAGE_PAGE_GENERIC),                      \
	HID_Usage(HID_USAGE_GENERIC_KEYBOARD),                    	\
	HID_Collection(HID_Application),        					\
		HID_ReportID(KB_REPORT_ID),								\
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),            		\
		HID_UsageMin(HID_USAGE_KEYBOARD_LCTRL),					\
		HID_UsageMax(HID_USAGE_KEYBOARD_RGUI),					\
		HID_LogicalMin(0), 										\
		HID_LogicalMax(1), 										\
		HID_ReportCount(8),										\
		HID_ReportSize(1),										\
		HID_Input(HID_Data|HID_Variable|HID_Absolute),			\
																\
		HID_UsagePage(HID_USAGE_PAGE_KEYBOARD),            		\
		HID_UsageMin(0x00),										\
		HID_UsageMax(0xEF),										\
		HID_LogicalMin(0), 										\
		HID_LogicalMax(1), 										\
		HID_ReportCount(0xF0),									\
		HID_ReportSize(1),										\
		HID_Input(HID_Data|HID_Variable|HID_Absolute),			\
																\
		HID_UsagePage(HID_USAGE_PAGE_LED),						\
		HID_UsageMin(HID_USAGE_LED_NUM_LOCK),					\
		HID_UsageMax(HID_USAGE_LED_KANA),						\
		HID_ReportCount(5),										\
		HID_ReportSize(1),										\
		HID_Output(HID_Data|HID_Variable|HID_Absolute),			\
		HID_ReportCount(1), 									\
		HID_ReportSize(3),										\
		HID_Output(HID_Constant|HID_Array|HID_Absolute),		\
	HID_EndCollection,											\
																\
	/* 29 bytes : USB iAP升级. */  	 							\
	HID_UsagePageVendor(HID_USAGE_PAGE_UNDEFINED),				\
	HID_Usage(HID_USAGE_PAGE_GENERIC),      					\
	HID_Collection(HID_Application),        					\
		HID_ReportID(CTL_REPORT_ID),							\
		HID_Usage(HID_USAGE_CONSUMER_CONTROL),					\
		HID_LogicalMin(0),										\
		HID_LogicalMaxS(0x00FF),								\
		HID_ReportCount(MAX_REPORT_SIZE),						\
		HID_ReportSize(8),										\
		HID_Input(HID_Data|HID_Variable|HID_Absolute),			\
		HID_Usage(HID_USAGE_CONSUMER_CONTROL),      			\
		HID_ReportCount(MAX_REPORT_SIZE),						\
		HID_Output(HID_Data|HID_Variable|HID_Absolute),			\
	HID_EndCollection,											\
}

typedef enum
{
    USB_HID_STA_SUCCESS,            /* > Operate success. */
    USB_HID_STA_NOT_READY,          /* > USB is not ready. */
    USB_HID_STA_BUSY,               /* > Last operating is running. */
    USB_HID_STA_INVALID_PARAM,      /* > Input param error. */
    USB_HID_STA_INACTIVE_EP,        /* > Inactive Endpoint. */
    USB_HID_STA_INTERNAL_ERR,       /* > EP NUM TOO BIG OR INPUT BUFFER NOT ALIGN(4). */
    USB_HID_STA_UNKNOW_ERR,         /* > Unknow error. */
    USB_HID_STA_SIZE_TOO_LARGE,     /* > size too large. */
}USB_HID_IAP_STA_t;

typedef enum
{
    USB_HID_ERROR_NONE,               /* > Operate success. */
    USB_HID_ERROR_NOT_READY,          /* > USB is not ready. */
    USB_HID_ERROR_BUSY,               /* > Last operating is running. */
    USB_HID_ERROR_INVALID_PARAM,      /* > Input param error. */
    USB_HID_ERROR_INACTIVE_EP,        /* > Inactive Endpoint. */
    USB_HID_ERROR_INTERNAL_ERR,       /* > EP NUM TOO BIG OR INPUT BUFFER NOT ALIGN(4). */
    USB_HID_ERROR_UNKNOW_ERR,         /* > Unknow error. */
    USB_HID_ERROR_SIZE_TOO_LARGE,     /* > size too large. */
}USB_HID_OperateSta_t;

typedef enum
{
    BSP_USB_PHY_DISABLE,
    BSP_USB_PHY_ENABLE
}BSP_USB_PHY_ENABLE_e;

typedef enum
{
    BSP_USB_PHY_DP_PULL_UP = 1,
    BSP_USB_PHY_DM_PULL_UP,
    BSP_USB_PHY_DP_DM_PULL_DOWN
}BSP_USB_PHY_PULL_e;

typedef struct
{
    uint32_t config_index:8;    // 记录当前生效的配置     FOR USB-IF
    uint32_t remote_wakeup:1;
    uint32_t unused:23;
}BSP_USB_VAR_s;

typedef enum {
    KEY_A               = 0x04,
    KEY_B               = 0x05,
    KEY_C               = 0x06,
    KEY_D               = 0x07,
    KEY_E               = 0x08,
    KEY_F               = 0x09,
    KEY_G               = 0x0A,
    KEY_H               = 0x0B,
    KEY_I               = 0x0C,
    KEY_J               = 0x0D,
    KEY_K               = 0x0E,
    KEY_L               = 0x0F,
    KEY_M               = 0x10,
    KEY_N               = 0x11,
    KEY_O               = 0x12,
    KEY_P               = 0x13,
    KEY_Q               = 0x14,
    KEY_R               = 0x15,
    KEY_S               = 0x16,
    KEY_T               = 0x17,
    KEY_U               = 0x18,
    KEY_V               = 0x19,
    KEY_W               = 0x1A,
    KEY_X               = 0x1B,
    KEY_Y               = 0x1C,
    KEY_Z               = 0x1D,
    KEY_1               = 0x1E,
    KEY_2               = 0x1F,
    KEY_3               = 0x20,
    KEY_4               = 0x21,
    KEY_5               = 0x22,
    KEY_6               = 0x23,
    KEY_7               = 0x24,
    KEY_8               = 0x25,
    KEY_9               = 0x26,
    KEY_0               = 0x27,
    KEY_ENTER           = 0x28,
    KEY_ESC             = 0x29,
    KEY_BACKSPACE       = 0x2A,
    KEY_TAB             = 0x2B,
    KEY_SPACE           = 0x2C,
    KEY_DEC             = 0x2D,
    KEY_ADD             = 0x2E,
    KEY_BRACKET_L       = 0x2F,
    KEY_BRACKET_R       = 0x30,
    KEY_K29             = 0x31,
    KEY_K42             = 0x32,
    KEY_SEMICOLON       = 0x33,
    KEY_QUOTE           = 0x34,
    KEY_GRAVE           = 0x35,
    KEY_COMMA           = 0x36,
    KEY_DOT             = 0x37,
    KEY_SLASH           = 0x38,
    KEY_CAP             = 0x39,
    KEY_F1              = 0x3A,
    KEY_F2              = 0x3B,
    KEY_F3              = 0x3C,
    KEY_F4              = 0x3D,
    KEY_F5              = 0x3E,
    KEY_F6              = 0x3F,
    KEY_F7              = 0x40,
    KEY_F8              = 0x41,
    KEY_F9              = 0x42,
    KEY_F10             = 0x43,
    KEY_F11             = 0x44,
    KEY_F12             = 0x45,
    KEY_PRINT           = 0x46,
    KEY_SCROLL          = 0x47,
    KEY_PAUSE           = 0x48,
    KEY_INSERT          = 0x49,
    KEY_HOME            = 0x4A,
    KEY_PGUP            = 0x4B,
    KEY_DELETE          = 0x4C,
    KEY_END             = 0x4D,
    KEY_PGDN            = 0x4E,
    KEY_RIGHT           = 0x4F,
    KEY_LEFT            = 0x50,
    KEY_DOWN            = 0x51,
    KEY_UP              = 0x52,
    KEY_NUM_LOCK        = 0x53,
    KEY_NUM_SLASH       = 0x54,
    KEY_NUM_STAR        = 0x55,
    KEY_NUM_DEC         = 0x56,
    KEY_NUM_ADD         = 0x57,
    KEY_NUM_ENTER       = 0x58,
    KEY_NUM_1           = 0x59,
    KEY_NUM_2           = 0x5A,
    KEY_NUM_3           = 0x5B,
    KEY_NUM_4           = 0x5C,
    KEY_NUM_5           = 0x5D,
    KEY_NUM_6           = 0x5E,
    KEY_NUM_7           = 0x5F,
    KEY_NUM_8           = 0x60,
    KEY_NUM_9           = 0x61,
    KEY_NUM_0           = 0x62,
    KEY_NUM_DEL         = 0x63,
	KEY_K45             = 0x64,
    KEY_APP             = 0x65,

    KEY_F13             = 0x68,
    KEY_F14             = 0x69,
    KEY_F15             = 0x6A,
    KEY_F16             = 0x6B,
    KEY_F17             = 0x6C,
    KEY_F18             = 0x6D,
    KEY_F19             = 0x6E,
    KEY_F20             = 0x6F,
    KEY_F21             = 0x70,
    KEY_F22             = 0x71,
    KEY_F23             = 0x72,
    KEY_F24             = 0x73,

    KEY_K56             = 0x87,
	KEY_K133            = 0x88,
    KEY_K14             = 0x89,
    KEY_K132            = 0x8A,
	KEY_K131            = 0x8B,
	KEY_K151            = 0x90,
	KEY_K150            = 0x91
	
} KEY_GENERAL_CLASS;

typedef enum {
    KEY_CTRL_L  = 0x01,
    KEY_SHIFT_L = 0x02,
    KEY_ALT_L   = 0x04,
    KEY_WIN_L   = 0x08,
    KEY_CTRL_R  = 0x10,
    KEY_SHIFT_R = 0x20,
    KEY_ALT_R   = 0x40,
    KEY_WIN_R   = 0x80,
} KEY_HOT_CLASS;

typedef enum {
    HID_KEYB_LED_NUM_LOCK = 0x01,
    HID_KEYB_LED_CAPS_LOCK = 0x02,
    HID_KEYB_LED_SCROLL_LOCK = 0x04,
    HID_KEYB_LED_COMPOSE = 0x08,
    HID_KEYB_LED_KANA = 0x10
} BSP_KEYB_KEYB_LED_e;

#define MOUSE_LEFT_KEY		(0x01)
#define MOUSE_RIGHT_KEY		(0x02)
#define MOUSE_MIDDLE_KEY	(0x04)
#define MOUSE_BACKWARD_KEY 	(0x08)
#define MOUSE_FORWARD_KEY 	(0x10)
#define MOUSE_WHEEL_UP		(0X01)
#define MOUSE_WHEEL_DOWN	(0XFF)

#define KEY_TABLE_LEN (6)

typedef struct __attribute__((packed))
{
    uint8_t modifier;
    uint8_t reserved;
    uint8_t key_table[KEY_TABLE_LEN];
} BSP_KEYB_REPORT_s;

#define KEY_BIT_TABLE_LEN	(31)
#define KEY_SYS_TABLE_LEN	(2)
#define KEY_CON_TABLE_LEN	(2)
#define KEY_MOU_TABLE_LEN	(8)

typedef struct __attribute__((packed))
{
  uint8_t button;
  int16_t pos_x;
  int16_t pos_y;
  uint8_t wheel;
  uint8_t reserved;
} BSP_MOUSE_REPORT_s;

typedef struct
{
    BSP_KEYB_REPORT_s Key_Byte_Table;		   /*byte 键盘数据*/
    uint8_t sendBusy;							/*byte 发送繁忙*/
	uint8_t led_state;							/*系统指示灯状态*/
	uint8_t kb_led_state_recving;				/*系统指示灯获取标志*/
	uint8_t SendByte_KB;						/*byte 键盘有数据要发送*/
	
	uint8_t Key_Bit_Table[KEY_BIT_TABLE_LEN];	/*bit 键盘数据*/
	uint8_t SendBit_KB;							/*bit 键盘有数据要发送*/
	
	uint8_t Key_Sys_Table[KEY_SYS_TABLE_LEN];	/*系统按键数据*/
	uint8_t Send_System;						/*系统键有数据要发送*/
	
	uint8_t Key_Con_Table[KEY_CON_TABLE_LEN];	/*多媒体按键数据*/
	uint8_t Send_Consumer;						/*多媒体键有数据要发送*/
}BSP_KEYB_DATA_s;

typedef struct
{
    uint8_t preReady;
    uint8_t ready;
    uint8_t sendBusy;
}BSP_CTL_DATA_s;

typedef struct
{
    uint8_t preReady;
    uint8_t ready;
    uint8_t sendBusy;
}BSP_HOST_DATA_s;

// =============================================================================================================
typedef enum {
    USB_EVT_ENABLED = 0,
    USB_EVT_DISABLED,
    USB_EVT_ENUM_SUCCESS, //枚举成功
	USB_EVT_TX_DONE,
	USB_EVT_TX_CONTINUE,
	USB_EVT_SUSPEND,
	USB_EVT_RESUME,
	USB_EVT_RESET,
	USB_EVT_SET_ADDRESS,
	USB_EVT_GET_DESCRIPTOR,
} USB_EVENT_E;

typedef void (*usb_event_handler_t) (uint8_t evt);
void bsp_usb_evt_handler_register(usb_event_handler_t __handler);

typedef enum {
  HID_PROTO_TYPE_BIOS   = 0x00,
  HID_PROTO_TYPE_REPORT = 0x01,
} BSP_USB_PROTO_TYPE_e;

// =============================================================================================================

uint8_t bsp_usb_is_ready(void);
void CtlReport_Set_Func(void);
void CtlReport_Claer_Func(void);
void SendBusy_Claer_Func(void);
/**
 * @brief bsp_usb_hid_iap_recv_cb_t
 * @param data: Received data point.
 * @param len:  Received data size. range: [ 1 ~ MAX_REPORT_SIZE ] 
 */
typedef void (* bsp_usb_hid_iap_recv_cb_t)(uint8_t *data, uint16_t len);
typedef void (* bsp_usb_hid_iap_send_complete_cb_t)(void);
typedef void (* bsp_usb_hid_host_recv_cb_t)(uint8_t *data, uint16_t len);

extern void bsp_usb_init(void);
extern void bsp_usb_disable(void);
extern void bsp_usb_device_remote_wakeup(void);

#ifdef FEATURE_DISCONN_DETECT
void bsp_usb_device_disconn_timeout(void);
#endif

USB_HID_OperateSta_t bsp_usb_hid_keyboard_basic_report_send(uint8_t *data, uint16_t len);
USB_HID_OperateSta_t bsp_usb_hid_report_send(uint8_t reportID, uint8_t *data, uint16_t len);


/**
 * @brief Device sends IAP data to host with this function. 
 *        It will generate a callback if cb is registered with.
 * 
 * @param data Send data pointer.
 * @param len  Send data size. range: [ 1 ~ MAX_REPORT_SIZE ] 
 * @return USB_HID_IAP_STA_t ref@USB_HID_IAP_STA_t
 */
USB_HID_IAP_STA_t bsp_usb_hid_iap_send(uint8_t *data, uint16_t len);

/**
 * @brief Device sends HOST data to host with this function. 
 *        It will generate a callback if cb is registered with.
 * 
 * @param data Send data pointer.
 * @param len  Send data size. range: [ 1 ~ MAX_REPORT_SIZE ] 
 * @return USB_HID_HOST_STA_t ref@USB_HID_HOST_STA_t
 */
USB_HID_IAP_STA_t bsp_usb_hid_host_send(uint8_t *data, uint16_t len);

/**
 * @brief If device received data from host, It will generate a callback if
 *        this function is registered.
 * 
 * @param cb application callback function.
 * @param cb param:
 *          data: Received data pointer.
 *          len:  Received data size. range: [ 1 ~ MAX_REPORT_SIZE ] 
 */
void bsp_usb_hid_iap_recv_callback_register(bsp_usb_hid_iap_recv_cb_t cb);

void bsp_usb_hid_host_recv_callback_register(bsp_usb_hid_host_recv_cb_t cb);

void Printf_Usb_Status_Fucn(void);

extern BSP_KEYB_DATA_s KeybReport;

#ifdef __cplusplus
}
#endif

#endif
