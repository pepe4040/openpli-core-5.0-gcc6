# We know about rtc
include conf/machine/include/build-extras.inc

BRAND_OEM = "tripledot"

MACHINE_NAME = "\
${@bb.utils.contains('MACHINEBUILD', 'enibox', 'EniBox' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mago', 'MAGO' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'tyrant', 'tyrant' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'xcombo', 'enfinityX combo plus' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'x1plus', 'enfinityX 1plus' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf108', 'SF108 E2HD' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 't2cable', 'ENFINITY T2/CABLE' , '', d)}\
"

MACHINE_BRAND = "\
${@bb.utils.contains('MACHINEBUILD', 'enibox', 'hdbox' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mago', 'relook' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'tyrant', 'tripledot' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'xcombo', 'EVO' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'x1plus', 'EVO' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf108', 'Octagon' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 't2cable', 'EVO' , '', d)}\
"

IMAGEDIR ?= "\
${@bb.utils.contains('MACHINEBUILD', 'enibox', 'enibox' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mago', 'mago' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'tyrant', 'tyrant' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'xcombo', 'xcombo' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'x1plus', 'x1plus' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf108', 'sf108' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 't2cable', 't2cable' , '', d)}\
"

MTD_KERNEL = "mtd2"
MTD_ROOTFS = "mtd8"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    tripledot-dvb-modules-${MACHINE} \
    "

DVBPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
    kernel-module-cdfs \
    "

MACHINE_EXTRA_RRECOMMENDS = " \
    gstreamer1.0-plugin-dvbmediasink \
    "

include conf/machine/include/autoload-filesystems.inc

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

PREFERRED_PROVIDER_virtual/kernel = "linux-tripledot"

KERNEL_IMAGETYPE = "vmlinux"
KERNEL_OUTPUT = "${KERNEL_IMAGETYPE}"
KERNEL_CONSOLE = "ttyS0,115200n8"

IMAGE_FSTYPES ?= "ubi"

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096"
UBINIZE_ARGS = "-m 2048 -p 128KiB -s 2048"

IMAGE_CMD_ubi_prepend = " \
    rm -rf ${IMAGE_ROOTFS}/boot/*; \
    rm -rf ${IMAGE_ROOTFS}/tmp/*; \
    "

IMAGE_CMD_ubi_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/octagon/splash.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/splash.bin; \
    mv ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.ubi ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${ROOTFS_FILE}; \
    gzip -9c ${DEPLOY_DIR_IMAGE}/vmlinux-${MACHINE}.bin > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    echo ${DISTRO_NAME}-${DISTRO_VERSION}-${DATE} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    echo "rename this file to 'force' to force an update without confirmation" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/noforce; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -Rf ${IMAGEDIR}; \
    "


MACHINE_FEATURES += "3dtv osdposition alsa hdmicec switchoff bootsplash omb videoenhancement ci externalwifi kernelwifi wlan skins1080"

BOOTLOGO_FILENAME = "splash.bin"

require conf/machine/include/tune-mips32.inc

# add support for extra feeds
PACKAGE_ARCHS += " ${MACHINEBUILD}"