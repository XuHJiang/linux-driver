export ARCH=arm

export CROSS_COMPILE=arm-linux-gnueabihf-

obj-m +=misc.o

KDIR:=/home/xhj/qemu/linux-5.10/

PWD?=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.mk .tmp_versions Module.symvers *.mod.c *.o *.ko .*.cmd Module.markers modules.order *.a *.mod
