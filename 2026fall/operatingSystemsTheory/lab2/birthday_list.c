#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

static int __init birthday_init(void)
{
	struct birthday *person;
	int i;

	printk(KERN_INFO "Birthday Module: Loading...\n");

	for (i = 0; i < 5; i++) {
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		if (!person) {
			printk(KERN_ERR "Birthday Module: kmalloc failed!\n");
			return -ENOMEM;
		}

		person->day = (i + 1) * 2;
		person->month = 8 + i;
		person->year = 1995 + i;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
	}

	{
		struct birthday *ptr;

		printk(KERN_INFO "Birthday Module: Listing birthdays:\n");
		list_for_each_entry(ptr, &birthday_list, list) {
			printk(KERN_INFO "  - %02d/%02d/%04d\n",
				ptr->day, ptr->month, ptr->year);
		}
	}

	return 0;
}

static void __exit birthday_exit(void)
{
	struct birthday *ptr;
	struct birthday *next;

	printk(KERN_INFO "Birthday Module: Removing...\n");

	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		printk(KERN_INFO "  deleting: %02d/%02d/%04d\n",
			ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}

	printk(KERN_INFO "Birthday Module: Removed. List cleared.\n");
}

module_init(birthday_init);
module_exit(birthday_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Linked List Example (Birthdays)");
MODULE_AUTHOR("Batbayar");
