obj-m += driver.o

all:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

insmod:
	sudo insmod driver.ko

rmmod:
	sudo rmmod driver.ko

print:
	dmesg

mknod:
	sudo mknod /dev/chardev c 127 0 -m 777

rmnod:
	sudo rm /dev/chardev

log:
	tail -f /var/log/syslog
