obj-m += solution.o

KERNEL_VERSION := $(shell uname -r)

KDIR ?= /lib/modules/$(KERNEL_VERSION)/build

all: build

build:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

load: build
	sudo insmod solution.ko node_name="my_super_cool_but_random_node_name"
	sudo dmesg -c

unload:
	sudo rmmod solution.ko
	sudo dmesg -c
