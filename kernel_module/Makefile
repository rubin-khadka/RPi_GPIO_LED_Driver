obj-m += hello.o

kDIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(kDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(kDIR) M=$(PWD) clean
	