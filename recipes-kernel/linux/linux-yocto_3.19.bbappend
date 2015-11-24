FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PR := "${PR}.1"

COMPATIBLE_MACHINE_eukrea-cpuimx51 = "eukrea-cpuimx51"

KCONFIG_MODE = "--alldefconfig"

KBRANCH_eukrea-cpuimx51  = "standard/base"

#SRC_URI += "file://eukrea-cpuimx51-standard.scc \
#            file://eukrea-cpuimx51-user-config.cfg \
#            file://eukrea-cpuimx51-user-patches.scc \
#            file://eukrea-cpuimx51-user-features.scc \
#	    file://defconfig \
#	    file://sdma-imx51.bin \
#           "

SRC_URI += "file://defconfig \
	    file://sdma-imx51.bin "

# uncomment and replace these SRCREVs with the real commit ids once you've had
# the appropriate changes committed to the upstream linux-yocto repo
#SRCREV_machine_pn-linux-yocto_eukrea-cpuimx51 ?= "840bb8c059418c4753415df56c9aff1c0d5354c8"
#SRCREV_meta_pn-linux-yocto_eukrea-cpuimx51 ?= "4fd76cc4f33e0afd8f906b1e8f231b6d13b6c993"
#LINUX_VERSION = "3.19"

do_compile_prepend () {
	cp ${WORKDIR}/sdma-imx51.bin ${S}/sdma-imx51.bin
}