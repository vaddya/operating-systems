obj-m += driver.o

all:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

insmod:
	sudo insmod driver.ko

rmmod:
	sudo rmmod driver.ko

mknod:
	sudo mknod /dev/chardev c 126 0 -m 777

rmnod:
	sudo rm /dev/chardev

print:
	dmesg

log:
	tail -f /var/log/syslog
