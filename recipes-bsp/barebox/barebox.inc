DESCRIPTION = "Barebox - a bootloader that inherits the best of U-Boot and the Linux kernel"
HOMEPAGE = "http://www.barebox.org/"
SECTION = "bootloader"
PROVIDES = "virtual/bootloader"
PRIORITY = "optional"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=057bf9e50e1ca857d0eb97bfe4ba8e5d"

PACKAGE_ARCH = "${MACHINE_ARCH}"

DEPENDS += "lzop-native"

inherit kernel-arch
inherit deploy

EXTRA_OEMAKE = "CROSS_COMPILE=${TARGET_PREFIX}"

BAREBOX_MACHINE ?= "${MACHINE}"
BAREBOX_BINARY ?= "barebox.bin"
BAREBOX_IMAGE ?= "barebox-${MACHINE}-${PV}-${PR}.bin"
BAREBOXENV_BIN ?= "bareboxenv-${MACHINE}-${PV}-${PR}.bin"
BAREBOX_SYMLINK ?= "barebox-${MACHINE}.bin"
BAREBOXENV_SYMLINK ?= "bareboxenv-${MACHINE}.bin"
BAREBOX_DEFCONFIG ?= ""
BAREBOX_DEFAULTENV ?= "defaultenv"

INSANE_SKIP_${PN} = "True"

SRC_URI = "http://barebox.org/download/${PN}-${PV}.tar.bz2"

do_configure_prepend() {
	if [ -n ${BAREBOX_DEFCONFIG} ]
	then 
	     cp ${WORKDIR}/defconfig ${S}/.config
	     oe_runmake oldconfig
	else
		oe_runmake ${BAREBOX_DEFCONFIG}
	fi
}

do_compile () {
	unset LDFLAGS
	unset CFLAGS
	unset CPPFLAGS
	oe_runmake all
}

do_deploy () {
	install -d ${DEPLOY_DIR_IMAGE}
	install ${S}/${BAREBOX_BINARY} ${DEPLOY_DIR_IMAGE}/${BAREBOX_IMAGE}
	install ${S}/${BAREBOX_DEFAULTENV}/barebox_default_env ${DEPLOY_DIR_IMAGE}/${BAREBOXENV_BIN}

	cd ${DEPLOY_DIR_IMAGE}
	rm -f ${BAREBOX_SYMLINK}
	rm -f ${BAREBOXENV_SYMLINK}
	ln -sf ${BAREBOX_IMAGE} ${BAREBOX_SYMLINK}
	ln -sf ${BAREBOXENV_BIN} ${BAREBOXENV_SYMLINK}

	install -d ${STAGING_BINDIR_NATIVE}
	cd ${S}
	install -m 755 scripts/mkimage ${STAGING_BINDIR_NATIVE}/
	install -m 755 scripts/bareboxenv ${STAGING_BINDIR_NATIVE}/
}

addtask deploy before do_build after do_compile
