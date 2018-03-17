# Makefile for learnfs filesystem module.

obj-m += learnfs.o
learnfs-objs += super.o inode.o file.o

all: learnfs

learnfs:
	make ARCH=arm64 CROSS_COMPILE=$(CC) -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR) M=$(shell pwd) clean
