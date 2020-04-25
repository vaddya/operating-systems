#include <linux/module.h>
#include <linux/kernel.h>

extern void call_me(const char *message);

static int __init init_mod(void)
{
        pr_info("Hello, world!\n");
        call_me("Hello from my module!");
        return 0;
}

static void __exit exit_mod(void)
{
        pr_info("Goodbye, world!\n");
        return;
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Task2");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
