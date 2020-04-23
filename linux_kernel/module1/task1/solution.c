#include <linux/module.h>
#include <linux/kernel.h>

int __init init_mod(void)
{
    printk(KERN_INFO "Hello, world!\n");
    return 0;
}

void __exit exit_mod(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
    return;
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Task1");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");

