#include "app_main.h"
#include "platform_api.h"
#include "ctrl.h"
#include "profile.h"
#include "IAP.h"

/********************************************************************************
 ****************************** 用户main文件 *************************************
 ********************************************************************************/

// static uint32_t app_busy_flag = 0;

/***************************************************************
							MAIN
****************************************************************/
static uint64_t time_1ms_tick = 0;
static uint64_t time_10ms_tick = 0;
static uint64_t time_20ms_tick = 0;
static uint64_t time_100ms_tick = 0;

static uint8_t wakeup_to_update_time_flag = 0;

static uint8_t jump_boot_flag = 0;

void app_main_set_jump_boot_flag(void)
{
	jump_boot_flag = 1;
}

uint32_t app_main_loop(void)
{
	uint64_t time_tick = 0;
	uint8_t app_low_power_is_enable = 0;

	if(jump_boot_flag)
	{
		jump_boot_flag = 0;
		if(set_enter_second_boot() == 0)
		{
			SYSCTRL_Reset();
		}
		else
		{
			app_printf("Set enter second boot error!\n");
		}
	}
	
    ucm_loop(); //EMI 测试相关

	// 不休眠
	return 1;
}


// 硬件初始化函数
void app_hardware_init(void)
{

}

// 硬件去初始化
void app_hardware_uninit(void)
{

}

// 此函数在系统启动时初始化一次
void app_power_on_init(void)
{
    app_hardware_init();
}

// 此函数在协议栈初始化前调用一次
void app_berfore_Bt_stack_init(void)
{

}

// 此函数在协议栈初始化后调用一次
void app_after_Bt_stack_init(void)
{

}

extern void setup_peripherals(void);
// 此函数在系统正常唤醒时立刻回调一次
void app_sys_wakeup_callback(uint8_t wakeup_reason)
{
	
}

// 此函数在系统唤醒时进入idle立刻回调一次
void app_sys_wakeup_idle_callback(void)
{

}

// 此函数在系统真正睡眠前调用一次
// 特别注意：睡眠前如果调用printf或platform_printf打印了串口信息，则睡眠系统会等待串口FIFO数据发送完成后才会真正进入睡眠
void app_sys_sleep_prepare(void)
{

}
