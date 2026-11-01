obj-m += simple_module.o

KERNEL_BUILD := /lib/modules/$(shell uname -r)/build
CURRENT_DIR := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_BUILD) M=$(CURRENT_DIR) modules

clean:
	$(MAKE) -C $(KERNEL_BUILD) M=$(CURRENT_DIR) clean
