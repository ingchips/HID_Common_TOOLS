#ifndef _PROFILESTASK_H_
#define _PROFILESTASK_H_

#include <stdint.h>

#define ADV_CMP_LENGTH  14

#define RELEASE_VER             0

#define RSSI_THRESHOLD          -30

#if (RELEASE_VER == 1)
    #define log_printf(...)
#else
    #define log_printf(...) platform_printf(__VA_ARGS__)
#endif

#define USER_KEY_BYTE_DATA		0X0B
#define USER_KEY_BIT_DATA		0X0C
#define USER_MOUSE_DATA			0X0D
#define USER_CONSUMER_DATA		0X0E
#define USER_SYSTEM_DATA		0X0F
#define USER_BATTERY_DATA		0X10
#define USER_SYSTEM_LED_DATA	0X11

#define LED_1		GIO_GPIO_7
#define LED_2		GIO_GPIO_8
#define LED_3		GIO_GPIO_9

#define LED_ON		1
#define LED_OFF		0


enum{
    KB_BLE_STATE_SCAN,                                  // 
    KB_BLE_STATE_CONNECT,                               // 
    KB_BLE_STATE_COMMUNICATING,                         // 

    KB_BLE_STATE_MAX, // Always at last.
};

uint32_t setup_profile(void *data, void *user_data);
uint8_t ble_state_get(void);

#endif


