#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init simple_module_init(void)
{
    pr_info("simple_module: module loaded\n");
    return 0;
}

static void __exit simple_module_exit(void)
{
    pr_info("simple_module: module unloaded\n");
}

module_init(simple_module_init);
module_exit(simple_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NUM student");
MODULE_DESCRIPTION("A simple Linux kernel module example");
