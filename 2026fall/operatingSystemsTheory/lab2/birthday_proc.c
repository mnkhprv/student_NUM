#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

#define PROC_NAME "birthdays"

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);
static struct proc_dir_entry *proc_entry;

static int birthdays_show(struct seq_file *file, void *v)
{
	struct birthday *ptr;

	seq_puts(file, "== Birthday List ==\n");
	list_for_each_entry(ptr, &birthday_list, list) {
		seq_printf(file, "%c %02d/%02d/%04d%s\n",
			ptr->year < 2000 ? '*' : '-',
			ptr->day, ptr->month, ptr->year,
			ptr->year < 2000 ? " (pre-2000)" : "");
	}

	return 0;
}

static int birthdays_open(struct inode *inode, struct file *file)
{
	return single_open(file, birthdays_show, NULL);
}

static const struct proc_ops birthdays_fops = {
	.proc_open = birthdays_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

static int __init birthday_init(void)
{
	struct birthday *p;

	printk(KERN_INFO "Birthday Proc Module: Loading...\n");

	/* Толгой дээр нэмэх (list_add) */
	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	p->day = 1;
	p->month = 1;
	p->year = 1995;
	INIT_LIST_HEAD(&p->list);
	list_add(&p->list, &birthday_list);

	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	p->day = 12;
	p->month = 5;
	p->year = 1998;
	INIT_LIST_HEAD(&p->list);
	list_add(&p->list, &birthday_list);

	/* Сүүлд нэмэх (list_add_tail) */
	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	p->day = 3;
	p->month = 7;
	p->year = 2001;
	INIT_LIST_HEAD(&p->list);
	list_add_tail(&p->list, &birthday_list);

	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	p->day = 20;
	p->month = 9;
	p->year = 2005;
	INIT_LIST_HEAD(&p->list);
	list_add_tail(&p->list, &birthday_list);

	/* procfs үүсгэх: /proc/birthdays */
	proc_entry = proc_create(PROC_NAME, 0, NULL, &birthdays_fops);
	if (!proc_entry) {
		printk(KERN_ERR "Failed to create /proc/%s\n", PROC_NAME);
		return -ENOMEM;
	}

	printk(KERN_INFO "Birthday Proc Module: /proc/%s created\n",
		PROC_NAME);
	return 0;
}

static void __exit birthday_exit(void)
{
	struct birthday *ptr;
	struct birthday *next;

	printk(KERN_INFO "Birthday Proc Module: Removing...\n");

	/* procfs устгах */
	if (proc_entry)
		proc_remove(proc_entry);

	/* Жагсаалтыг цэвэрлэх */
	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		printk(KERN_INFO "  deleting: %02d/%02d/%04d\n",
			ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}

	printk(KERN_INFO "Birthday Proc Module: Removed.\n");
}

module_init(birthday_init);
module_exit(birthday_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Batbayar");
MODULE_DESCRIPTION("Birthday list with procfs + list_add vs list_add_tail demo");
