#include <linux/module.h>
#include <linux/kernel.h>

extern void call_me(const char* message);

int __init init_mod(void)
{
    printk(KERN_INFO "Hello, world!\n");
    call_me("Hello from my module!");
    return 0;
}

void __exit exit_mod(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
    return;
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Task2");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");

