/*
 * Copyright (C) 2012 Atmel Corporation
 *
 * Configuation settings for the AT91SAM9X5EK board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

//#define DEBUG

#include <asm/hardware.h>

/* ARM asynchronous clock */
#define CONFIG_SYS_AT91_SLOW_CLOCK	32768
#define CONFIG_SYS_AT91_MAIN_CLOCK	12000000	/* 12 MHz crystal */
#define CONFIG_SYS_HZ			1000

#define CONFIG_AT91SAM9X5EK
#define CONFIG_AT91FAMILY

#define CONFIG_CMDLINE_TAG		/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_DISPLAY_CPUINFO

#define CONFIG_CMD_BOOTZ
#define CONFIG_OF_LIBFDT

/* general purpose I/O */
#define CONFIG_ATMEL_LEGACY		/* required until (g)pio is fixed */
#define CONFIG_AT91_GPIO

/* serial console */
#define CONFIG_ATMEL_USART
#define CONFIG_USART_BASE	ATMEL_BASE_DBGU
#define CONFIG_USART_ID		ATMEL_ID_SYS

/* LCD */
#define CONFIG_LCD
#undef CONFIG_LCD
#define LCD_BPP			LCD_COLOR16
#define LCD_OUTPUT_BPP		24
#define CONFIG_LCD_LOGO
#undef LCD_TEST_PATTERN
#define CONFIG_LCD_INFO
#define CONFIG_LCD_INFO_BELOW_LOGO
#define CONFIG_SYS_WHITE_ON_BLACK
#define CONFIG_ATMEL_HLCD
#define CONFIG_ATMEL_LCD_RGB565
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

/* LED */
#define CONFIG_AT91_LED
#define	CONFIG_RED_LED		AT91_PIN_PB18	/* this is the user1 led */

#define CONFIG_BOOTDELAY	1

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_IMI
#undef CONFIG_CMD_IMLS
#undef CONFIG_CMD_LOADS

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_NAND
//#define CONFIG_CMD_SF
#define CONFIG_CMD_MMC
#define CONFIG_CMD_FAT
#define CONFIG_CMD_USB

/*
 * define CONFIG_USB_EHCI to enable USB Hi-Speed (aka 2.0)
 * NB: in this case, USB 1.1 devices won't be recognized.
 */


/* SDRAM */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x20000000
#define CONFIG_SYS_SDRAM_SIZE		0x04000000	/* 64 megs */

#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_SDRAM_BASE + 4 * 1024 - GENERATED_GBL_DATA_SIZE)

/* DataFlash */
#ifdef CONFIG_CMD_SF
#define CONFIG_ATMEL_SPI
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_ATMEL
#define CONFIG_SF_DEFAULT_SPEED		30000000
#endif

/* no NOR flash */
#define CONFIG_SYS_NO_FLASH

/* NAND flash */
#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_ATMEL
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x40000000
#define CONFIG_SYS_NAND_DBW_8		1
/* our ALE is AD21 */
#define CONFIG_SYS_NAND_MASK_ALE	(1 << 21)
/* our CLE is AD22 */
#define CONFIG_SYS_NAND_MASK_CLE	(1 << 22)
#define CONFIG_SYS_NAND_ENABLE_PIN	AT91_PIN_PD4
#define CONFIG_SYS_NAND_READY_PIN	AT91_PIN_PD5

/* PMECC & PMERRLOC */
#define CONFIG_ATMEL_NAND_HWECC		1
#define CONFIG_ATMEL_NAND_HW_PMECC	1
#define CONFIG_PMECC_CAP		2
#define CONFIG_PMECC_SECTOR_SIZE	512
#define CONFIG_PMECC_INDEX_TABLE_OFFSET	0x8000

#define CONFIG_MTD_DEVICE
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_PARTITIONS
#define CONFIG_RBTREE

#if 0
#define CONFIG_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#endif
#define CONFIG_CMD_NAND_YAFFS

#endif

/* MMC */
#ifdef CONFIG_CMD_MMC
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_GENERIC_ATMEL_MCI
#endif

/* FAT */
#ifdef CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#endif

/* Ethernet */
#define CONFIG_MACB
#define CONFIG_RMII
//#define CONFIG_NET_MULTI
#define CONFIG_NET_RETRY_COUNT		20
#define CONFIG_MACB_SEARCH_PHY

/* USB */
#ifdef CONFIG_CMD_USB
#ifdef CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_ATMEL
#define CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS	2
#else
#define CONFIG_USB_OHCI_NEW
#define CONFIG_SYS_USB_OHCI_CPU_INIT
#define CONFIG_SYS_USB_OHCI_REGS_BASE		ATMEL_BASE_OHCI
#define CONFIG_SYS_USB_OHCI_SLOT_NAME		"at91sam9x5"
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	3
#endif
#define CONFIG_USB_ATMEL
#define CONFIG_USB_STORAGE
#endif

#define CONFIG_SYS_LOAD_ADDR		0x22000000	/* load address */

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		0x21e00000

/* bootstrap + u-boot + env + linux in nandflash */
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET		0xc0000
#define CONFIG_ENV_OFFSET_REDUND	0xe0000
#define CONFIG_ENV_SIZE		0x20000		/* 1 sector = 128 kB */
#define CONFIG_BOOTCOMMAND       "run ndubi"


#define CONFIG_BAUDRATE		115200

#define CONFIG_SYS_PROMPT	"U-Boot> "
#define CONFIG_SYS_CBSIZE	256
#define CONFIG_SYS_MAXARGS	16
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) \
					+ 16)
#define CONFIG_SYS_LONGHELP
#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_HUSH_PARSER

#define CONFIG_NETMASK          255.255.255.0
#define CONFIG_IPADDR           10.2.236.6
#define CONFIG_SERVERIP         10.2.236.60
#define CONFIG_ETHADDR          02:0b:0c:0d:0e:0e
#define CONFIG_ETH1ADDR         02:0b:0c:0d:0e:0f

#define MTDIDS_DEFAULT        "nand0=atmel_nand"
#define MTDPARTS_DEFAULT          \
        "mtdparts=atmel_nand:"    \
        "256k(bootstrap)ro,"      \
        "512k(u-boot)ro,"         \
        "128k(u-boot-env)ro,"     \
        "128k(u-boot-env2)ro,"    \
        "1M(RTOS APP),"           \
        "3M(kernel),"             \
        "32M(root),"              \
        "-(udisk)" 

#define CONFIG_EXTRA_ENV_SETTINGS                                     \
	"stdin=serial\0"                                                  \
	"stdout=serial\0"                                                 \
	"stderr=serial\0"                                                 \
    "init=/linuxrc\0"                                                 \
    "hostname=qssx9260\0"                                             \
    "nfsroot=/home/nfs/rootfs\0"                                      \
    "mtdroot=/dev/mtdblock3\0"                                        \
	"ubimtd=3\0"                                                      \
	"ubiroot=ubi0:rootfs\0"                                           \
    "usbroot=\0"                                                      \
    "load_addr=0x20010000\0"                                          \
    "kernel_nand_addr=0x200000\0"                                     \
    "kernel_size=0x200000\0"                                          \
	"rootfs_addr=0x500000\0"                                          \
    "rootfs_size=0x2000000\0"                                         \
	"set_kernel=setenv loadfile uImage\0"                             \
	"set_cramfs=setenv loadfile cramfs.img\0"                         \
	"set_yaffs2=setenv loadfile yaffs2.img\0"                         \
	"set_ubifs=setenv loadfile ubifs.img\0"                           \
	"set_app=setenv loadfile app.bin\0"                               \
	"ld_file_tf=tftp ${load_addr} ${loadfile}\0"                      \
    "ld_file_us=usb start;fatload usb 0 ${load_addr} ${loadfile};usb stop\0" \
    "ld_kernel_nd=nand read.i ${load_addr} ${kernel_nand_addr} ${kernel_size}\0" \
    "addip=setenv bootargs ${bootargs} "                        \
        "ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}"      \
        ":${hostname}:${netdev}:off panic=1\0"                        \
    "addtty=setenv bootargs ${bootargs} console=ttyS0,${baudrate} "   \
        "mem=64M\0"                                                   \
    "mtdargs=setenv bootargs root=${mtdroot} rw init=${init}\0"       \
    "ubiargs=setenv bootargs ubi.mtd=${ubimtd} "                      \
		"rootfstype=ubifs root=${ubiroot} init=${init}\0"             \
    "nfsargs=setenv bootargs root=/dev/nfs rw "                       \
        "nfsroot=${serverip}:${nfsroot} init=${init}\0"               \
    "tfnf=run set_kernel ld_file_tf nfsargs addip addtty;"            \
        "bootm ${load_addr}\0"                                  \
    "tfnd=run set_kernel ld_file_tf mtdargs addtty;"                  \
        "bootm ${load_addr}\0"                                  \
    "tfubi=run set_kernel ld_file_tf ubiargs addtty;"                 \
        "bootm ${load_addr}\0"                                  \
    "ndnf=run ld_kernel_nd nfsargs addip addtty;"                     \
        "bootm ${load_addr}\0"                                  \
    "ndnd=run ld_kernel_nd mtdargs addtty;"                           \
        "bootm ${load_addr}\0"                                  \
    "ndubi=run ld_kernel_nd ubiargs addtty;"                          \
        "bootm ${load_addr}\0"                                  \
    "usnf=run set_kernel ld_file_us nfsargs addip addtty;"            \
        "bootm ${load_addr}\0"                                  \
    "usnd=run set_kernel ld_file_us mtdargs addtty;"                  \
        "bootm ${load_addr}\0"                                  \
    "usubi=run set_kernel ld_file_us ubiargs addtty;"                 \
        "bootm ${load_addr}\0"                                  \
	"write_kernel=nand erase ${kernel_nand_addr} ${kernel_size};"     \
		"nand write.i ${load_addr} ${kernel_nand_addr} ${filesize};\0"\
	"erase_rootfs=nand erase ${rootfs_addr} ${rootfs_size};\0"        \
	"write_yaffs2=run erase_rootfs;"                                  \
		"nand write.yaffs ${load_addr} ${rootfs_addr} ${filesize};\0" \
	"write_ubifs=run erase_rootfs;"                                   \
		"nand write.i ${load_addr} ${rootfs_addr} ${filesize};\0"     \
	"write_cramfs=run write_ubifs;\0"                                 \
	"updt_kernel_tf=run set_kernel ld_file_tf write_kernel;\0"        \
	"updt_kernel_us=run set_kernel ld_file_us write_kernel;\0"        \
	"updt_yaffs2_tf=run set_yaffs2 ld_file_tf write_yaffs2;\0"        \
	"updt_yaffs2_us=run set_yaffs2 ld_file_us write_yaffs2;\0"        \
	"updt_cramfs_tf=run set_cramfs ld_file_tf write_cramfs;\0"        \
	"updt_cramfs_us=run set_cramfs ld_file_us write_cramfs;\0"        \
	"updt_ubifs_tf=run set_ubifs ld_file_tf write_ubifs;\0"           \
	"updt_ubifs_us=run set_ubifs ld_file_us write_ubifs;\0"

/* enable watchdog */
#define CONFIG_HW_WATCHDOG
#define CONFIG_AT91SAM9_WATCHDOG

/* RTC and I2C stuff */
#define CONFIG_CMD_DATE
#define CONFIG_RTC_DS3231
#define CONFIG_SYS_I2C_RTC_ADDR        0x68
#undef CONFIG_HARD_I2C
#define CONFIG_SOFT_I2C
#define CONFIG_SYS_I2C_SPEED         100000
#define CONFIG_SYS_I2C_SLAVE           0x7F

#ifdef CONFIG_SOFT_I2C
# define CONFIG_I2C_CMD_TREE
# define CONFIG_I2C_MULTI_BUS
/* Configure data and clock pins for pio */
# define I2C_INIT { \
    at91_set_pio_output(AT91_PIO_PORTA, 30, 0); \
    at91_set_pio_output(AT91_PIO_PORTA, 31, 0); \
}
# define I2C_SOFT_DECLARATIONS
/* Configure data pin as output */
# define I2C_ACTIVE          at91_set_pio_output(AT91_PIO_PORTA, 30, 0)
/* Configure data pin as input */
# define I2C_TRISTATE        at91_set_pio_input(AT91_PIO_PORTA, 30, 0)
/* Read data pin */
# define I2C_READ            at91_get_pio_value(AT91_PIO_PORTA, 30)
/* Set data pin */
# define I2C_SDA(bit)        at91_set_pio_value(AT91_PIO_PORTA, 30, bit)
/* Set clock pin */
# define I2C_SCL(bit)        at91_set_pio_value(AT91_PIO_PORTA, 31, bit)
# define I2C_DELAY           udelay(4) /* 1/4 I2C clock duration */
#endif /* CONFIG_SOFT_I2C */

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(512 * 1024 + 0x1000)

#ifdef CONFIG_USE_IRQ
#error CONFIG_USE_IRQ not supported
#endif

#endif
