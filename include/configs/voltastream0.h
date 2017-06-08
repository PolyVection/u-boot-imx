/*
 * Copyright (C) 2015-2016 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Freescale i.MX6UL 14x14 EVK board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __VOLTASTREAM0_CONFIG_H
#define __VOLTASTREAM0_CONFIG_H


#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include "mx6_common.h"
#include <asm/imx-common/gpio.h>

#define PHYS_SDRAM_SIZE		SZ_512M
#define CONFIG_BOOTARGS_CMA_SIZE   ""
/* DCDC used on 14x14 EVK, no PMIC */
#undef CONFIG_LDO_BYPASS_CHECK

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART1_BASE

/* MMC Configs */
#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR
#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"mmcautodetect=yes\0" \
	"swbank=2\0" \
	"switch= if test ${swbank} -eq 1; then " \
			"setenv swbank 2; saveenv; " \
		"else " \
			"setenv swbank 1; saveenv; " \
		"fi;\0" \
	"mmcargs=setenv bootargs console=ttymxc0,115200 " \
		"root=/dev/mmcblk1p${swbank} rootwait rw\0" \
	"loadimage=ext4load mmc 1:${swbank} 0x80800000 /boot/zImage\0" \
	"loadfdt=ext4load mmc 1:${swbank} 0x83000000 /boot/imx6ull-voltastream-zero.dtb\0" \
	"mmcboot=echo Booting from swbank=${swbank} ...; " \
		"run mmcargs; " \
		"if run loadfdt; then " \
			"bootz 0x80800000 - 0x83000000; " \
		"else " \
			"echo WARN: Cannot load the DT - ABORTING; " \
		"fi; " \

#define CONFIG_BOOTCOMMAND \
	   "mmc dev 1;" \
	   "mmc dev 1;" \
	   "if mmc rescan; then " \
           	"if run loadimage; then " \
	   		"run mmcboot; " \
		"else " \
			"echo No kernel found - switching bank!; " \
			"run switch; " \
			"if run loadimage; then " \
	   			"run mmcboot; " \
			"fi; " \
           	"fi; " \
	   "fi;"

/* Miscellaneous configurable options */
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x8000000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#define CONFIG_STACKSIZE		SZ_128K

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
/*#define CONFIG_SYS_NO_FLASH*/
/*#define CONFIG_ENV_IS_IN_MMC*/
#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_SYS_MMC_ENV_DEV		1   /* USDHC2 */
#define CONFIG_SYS_MMC_ENV_PART		0	/* user area */
#define CONFIG_MMCROOT			"/dev/mmcblk1p2"  /* USDHC2 */

#define CONFIG_CMD_BMODE


#define CONFIG_ENV_SIZE			SZ_8K
#if defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(12 * SZ_64K)
#elif defined(CONFIG_ENV_IS_IN_SPI_FLASH)
#define CONFIG_ENV_OFFSET		(768 * 1024)
#define CONFIG_ENV_SECT_SIZE		(64 * 1024)
#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#elif defined(CONFIG_ENV_IS_IN_NAND)
#undef CONFIG_ENV_SIZE
#define CONFIG_ENV_OFFSET		(60 << 20)
#define CONFIG_ENV_SECT_SIZE		(128 << 10)
#define CONFIG_ENV_SIZE			CONFIG_ENV_SECT_SIZE
#endif

#define CONFIG_IMX_THERMAL

#define CONFIG_MODULE_FUSE
#define CONFIG_OF_SYSTEM_SETUP

#endif


