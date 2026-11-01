obj-m += simple.o
obj-m += birthday_list.o
obj-m += birthday_proc.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: all run clean

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

run: all
	@echo "=== removing old lab modules if loaded ==="
	@sudo rmmod birthday_proc 2>/dev/null || true
	@sudo rmmod birthday_list 2>/dev/null || true
	@sudo rmmod simple 2>/dev/null || true
	@echo "=== simple ==="
	sudo insmod simple.ko
	lsmod | grep simple
	sudo rmmod simple
	@echo "=== birthday_list ==="
	sudo insmod birthday_list.ko
	lsmod | grep birthday_list
	sudo rmmod birthday_list
	@echo "=== birthday_proc ==="
	sudo insmod birthday_proc.ko
	lsmod | grep birthday_proc
	cat /proc/birthdays
	sudo rmmod birthday_proc
	@echo "=== dmesg ==="
	sudo dmesg | tail -n 40

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
