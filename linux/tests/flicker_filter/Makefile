KBUILD_CPPFLAGS += -I$(STM_BLITTER_TOPDIR)/linux/tests/gam_utils

PWD := $(shell pwd)

blit_test-objs += flicker_filter.o

obj-m := flicker_filter.o

all: modules modules_install

modules:
	$(MAKE) -C $(KERNELDIR) $(patsubst %,O=%,$O) M="$(PWD)" ARCH="$(ARCH)" CROSS_COMPILE="$(CROSS_COMPILE)" modules

.PHONY: modules_install
modules_install:
	$(MAKE) -C $(KERNELDIR) $(patsubst %,O=%,$O) M="$(PWD)" ARCH="$(ARCH)" CROSS_COMPILE="$(CROSS_COMPILE)" INSTALL_MOD_DIR=blitter modules_install

dep:

clean :
	find . -name "*.o" -exec rm \{\} \;
	find . -name "*.ko" -exec rm \{\} \;

