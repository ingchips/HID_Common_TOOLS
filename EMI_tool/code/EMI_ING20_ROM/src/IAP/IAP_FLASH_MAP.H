#ifndef _IAP_FLASH_MAP_H_
#define _IAP_FLASH_MAP_H_

#include "eflash.h"

// FLASH MAP: https://www.yuque.com/tanqian-c0ev9/czrc2l/sg3s9lapwmg06ggb?singleDoc

#if (INGCHIPS_FAMILY == INGCHIPS_FAMILY_918)
#define EFLASH_UNIT_SIZE              (uint32_t)(EFLASH_PAGE_SIZE)
#elif (INGCHIPS_FAMILY == INGCHIPS_FAMILY_916)
#define EFLASH_UNIT_SIZE              (uint32_t)(EFLASH_SECTOR_SIZE)
#elif (INGCHIPS_FAMILY == INGCHIPS_FAMILY_20)
#define EFLASH_UNIT_SIZE              (uint32_t)(EFLASH_SECTOR_SIZE)
#endif
#define ALIGN_TO(address, alignment)  (((address) + (alignment) - 1) & ~((alignment) - 1))
#define ALIGN_TO_EFLASH_UNIT(address) ALIGN_TO(address, EFLASH_UNIT_SIZE)

#define APP_ADDR                      (0x0200E000)
#define APP_SIZE                      (0x0002D800)     // 186,368 Byte   182KB
#define KV_PARAM_ADDR                 (0x0207E000)     // kv Param area: from KV_PARAM_ADDR to FLASH_TOP_ADDR
#define RSVD_START_ADDR               (uint32_t)(KV_PARAM_ADDR)
#define USER_PARAM_ADDR               (0x02069000)     // user Param area: from USER_PARAM_ADDR to KV_PARAM_ADDR

#define SECOND_BOOT_START_ADDR        (uint32_t)(0x02002000)
#define PLATFORM_START_ADDR           (uint32_t)(0x02008000)
#define APP_START_ADDR                (uint32_t)(APP_ADDR)
#define APP_TOP_ADDR                  (uint32_t)(ALIGN_TO_EFLASH_UNIT(APP_ADDR + APP_SIZE))
#define APP_PARAM_START_ADDR          (uint32_t)(USER_PARAM_ADDR)
#define FLASH_TOP_ADDR                (uint32_t)(0x02080000) 

#define SECOND_BOOT_CODE_SIZE         (PLATFORM_START_ADDR - SECOND_BOOT_START_ADDR)
#define PLATFORM_CODE_SIZE            (APP_START_ADDR      - PLATFORM_START_ADDR)
#define APP_CODE_SIZE                 (APP_TOP_ADDR        - APP_START_ADDR)
#define APP_PARAM_SIZE                (FLASH_TOP_ADDR      - APP_PARAM_START_ADDR)

#endif
