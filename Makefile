ifneq ($(KERNELRELEASE),)
include Kbuild
else
KDIR ?= $(HOME)/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE="ccache arm-linux-gnueabihf-" modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE="ccache arm-linux-gnueabihf-" clean
endif
