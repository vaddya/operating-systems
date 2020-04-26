obj-m += solution.o

KERNEL_VERSION := $(shell uname -r)

KDIR ?= /lib/modules/$(KERNEL_VERSION)/build

all: build

build:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

load: build
	sudo insmod solution.ko delays=150,500,850,50,1000,350,200
	sudo dmesg -c

unload:
	sudo rmmod solution.ko
	sudo dmesg -c
