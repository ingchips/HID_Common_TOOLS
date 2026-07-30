#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void app_hardware_init(void);
void app_hardware_uninit(void);
void app_power_on_init(void);
void app_berfore_Bt_stack_init(void);
void app_after_Bt_stack_init(void);
void app_sys_wakeup_callback(uint8_t wakeup_reason);
void app_sys_wakeup_idle_callback(void);
void app_sys_sleep_prepare(void);
void app_main_set_jump_boot_flag(void);
uint32_t app_main_loop(void);

#endif

