obj-m := hello.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	# sudo rmmod hello
	sudo insmod hello.ko

clean:
	sudo rmmod hello
	rm -rf *.o *.ko mod* Mod* hello.m* .tmp_versions .hello*
