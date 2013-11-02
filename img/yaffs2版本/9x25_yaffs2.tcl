################################################################################
#  proc uboot_env: Convert u-boot variables in a string ready to be flashed
#                  in the region reserved for environment variables
################################################################################
proc set_uboot_env {nameOfLstOfVar} {
    upvar $nameOfLstOfVar lstOfVar
    
    # sector size is the size defined in u-boot CFG_ENV_SIZE
    set sectorSize [expr 0x20000 - 5]

    set strEnv [join $lstOfVar "\0"]
    while {[string length $strEnv] < $sectorSize} {
        append strEnv "\0"
    }
    set strCrc [binary format i [::vfs::crc $strEnv]]
	set flags \1
    return "$strCrc$flags$strEnv"
}

lappend u_boot_variables \
	"baudrate=115200"                                               \
	"bootcmd=run ndubi"                                             \
	"bootdelay=1"                                                   \
	"eth1addr=02:0b:0c:0d:0e:0f"                                    \
	"ethaddr=02:0b:0c:0d:0e:0e"                                     \
	"ipaddr=10.2.236.6"                                             \
	"netmask=255.255.255.0"                                         \
	"serverip=10.2.236.60"                                          \
	"stdin=serial"                                                  \
	"stdout=serial"                                                 \
	"stderr=serial"                                                 \
    "init=/linuxrc"                                                 \
    "hostname=qssx9260"                                             \
    "nfsroot=/home/nfs/rootfs"                                      \
    "mtdroot=/dev/mtdblock3"                                        \
	"ubimtd=3"                                                      \
	"ubiroot=ubi0:rootfs"                                           \
    "usbroot="                                                      \
    "load_addr=0x20010000"                                          \
    "kernel_nand_addr=0x200000"                                     \
    "kernel_size=0x200000"                                          \
	"rootfs_addr=0x500000"                                          \
    "rootfs_size=0x2000000"                                         \
	"set_kernel=setenv loadfile uImage"                             \
	"set_cramfs=setenv loadfile cramfs.img"                         \
	"set_yaffs2=setenv loadfile yaffs2.img"                         \
	"set_ubifs=setenv loadfile ubifs.img"                           \
	"set_app=setenv loadfile app.bin"                               \
	"ld_file_tf=tftp \${load_addr} \${loadfile}"                      \
    "ld_file_us=usb start;fatload usb 0 \${load_addr} \${loadfile};usb stop" \
    "ld_kernel_nd=nand read.i \${load_addr} \${kernel_nand_addr} \${kernel_size}" \
    "addip=setenv bootargs \${bootargs} ip=\${ipaddr}:\${serverip}:\${gatewayip}:\${netmask}:\${hostname}:\${netdev}:off panic=1" \
    "addtty=setenv bootargs \${bootargs} console=ttyS0,\${baudrate} mem=64M"                                                   \
    "mtdargs=setenv bootargs root=\${mtdroot} rw init=\${init}"       \
    "ubiargs=setenv bootargs ubi.mtd=\${ubimtd} rootfstype=ubifs root=\${ubiroot} init=\${init}"             \
    "nfsargs=setenv bootargs root=/dev/nfs rw nfsroot=\${serverip}:\${nfsroot} init=\${init}"               \
    "tfnf=run set_kernel ld_file_tf nfsargs addip addtty;bootm \${load_addr}"                                  \
    "tfnd=run set_kernel ld_file_tf mtdargs addtty;bootm \${load_addr}"                                  \
    "tfubi=run set_kernel ld_file_tf ubiargs addtty;bootm \${load_addr}"                                  \
    "ndnf=run ld_kernel_nd nfsargs addip addtty;bootm \${load_addr}"                                  \
    "ndnd=run ld_kernel_nd mtdargs addtty;bootm \${load_addr}"                                  \
    "ndubi=run ld_kernel_nd ubiargs addtty;bootm \${load_addr}"                                  \
    "usnf=run set_kernel ld_file_us nfsargs addip addtty;bootm \${load_addr}"                                  \
    "usnd=run set_kernel ld_file_us mtdargs addtty;bootm \${load_addr}"                                  \
    "usubi=run set_kernel ld_file_us ubiargs addtty;bootm \${load_addr}"                                  \
	"write_kernel=nand erase \${kernel_nand_addr} \${kernel_size};nand write.i \${load_addr} \${kernel_nand_addr} \${filesize};"\
	"erase_rootfs=nand erase \${rootfs_addr} \${rootfs_size};"        \
	"write_yaffs2=run erase_rootfs;nand write.yaffs \${load_addr} \${rootfs_addr} \${filesize};" \
	"write_ubifs=run erase_rootfs;nand write.i \${load_addr} \${rootfs_addr} \${filesize};"     \
	"write_cramfs=run write_ubifs;"                                 \
	"updt_kernel_tf=run set_kernel ld_file_tf write_kernel;"        \
	"updt_kernel_us=run set_kernel ld_file_us write_kernel;"        \
	"updt_yaffs2_tf=run set_yaffs2 ld_file_tf write_yaffs2;"        \
	"updt_yaffs2_us=run set_yaffs2 ld_file_us write_yaffs2;"        \
	"updt_cramfs_tf=run set_cramfs ld_file_tf write_cramfs;"        \
	"updt_cramfs_us=run set_cramfs ld_file_us write_cramfs;"        \
	"updt_ubifs_tf=run set_ubifs ld_file_tf write_ubifs;"           \
	"updt_ubifs_us=run set_ubifs ld_file_us write_ubifs;"
	
################################################################################
#  Main script: Load the linux demo in NAND Flash
################################################################################
set bootstrapFile	"ministrap.bin"
set ubootFile		"u-boot.bin"
set ubootEnvFile    "tmp.bin"
set kernelFile		"uImage"
set rootfsFile		"ubifs.img"

## NandFlash Mapping
set ubootAddr		0x00040000
set ubootEnvOff0    0x000c0000
set ubootEnvOff1    0x000e0000
set kernelAddr		0x00200000
set rootfsAddr		0x00500000

## Falshing binaries
puts "-I- === Initialize the NAND access ==="
NANDFLASH::Init

puts "-I- === Enable PMECC OS Parameters ==="
NANDFLASH::NandHeaderValue HEADER 0xc0c00405

puts "-I- === Erase all the NAND flash blocs and test the erasing ==="
NANDFLASH::EraseAllNandFlash

puts "-I- === Load the bootstrap: nandflash_at91sam9-ek in the first sector ==="
NANDFLASH::SendBootFilePmeccCmd $bootstrapFile

puts "-I- === Load the u-boot image ==="
send_file {NandFlash} "$ubootFile" $ubootAddr 0

puts "-I- === Load the u-boot environment variables ==="
set fh [open "$ubootEnvFile" w]
fconfigure $fh -translation binary
puts -nonewline $fh [set_uboot_env u_boot_variables]
close $fh
send_file {NandFlash} "$ubootEnvFile" $ubootEnvOff0 0
send_file {NandFlash} "$ubootEnvFile" $ubootEnvOff1 0

puts "-I- === Load the Kernel image ==="
send_file {NandFlash} "$kernelFile" $kernelAddr 0

puts "-I- === Enable trimffs ==="
NANDFLASH::NandSetTrimffs 1

#puts "-I- === Load the linux file system ==="
#send_file {NandFlash} "$rootfsFile" $rootfsAddr 0

puts "-I- === DONE. ==="
