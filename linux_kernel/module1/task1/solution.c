#include <linux/module.h>
#include <linux/kernel.h>

int __init hello_init(void)
{
    printk(KERN_INFO "Hello, world!\n");
    return 0;
}

void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
    return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("First module");
MODULE_LICENSE("GPL");

