DESCRIPTION = "Hello world example"

# Yocto force to define LICENSE
# Our licence is contained in the source file
LICENSE="GPLv2"
LIC_FILES_CHKSUM = "file://../helloworld.c;beginline=1;endline=17;md5=4b0530b0bdc457f17d58d594cc3991b0"

# Yocto release of the package
PR = "r0"

# Define where to find sources, patches, ...
SRC_URI = "file://helloworld.c"

# Compile sources to obtain binary
do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/helloworld.c -o helloworld
}

# Create package specific skeleton
do_install() {
        install -m 0755 -d ${D}${bindir}
        install -m 0755 ${S}/helloworld ${D}${bindir}
}

# Populate packages
FILES_${PN} = " ${bindir}/helloworld "
