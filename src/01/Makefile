
obj-m +=helloworld.o

KDIR:=/home/xhj/qemu/linux-5.10/

PWD?=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

