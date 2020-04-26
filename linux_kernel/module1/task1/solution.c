#include <linux/module.h>
#include <linux/kernel.h>

static int __init init_mod(void)
{
        pr_info("Hello, world!\n");
        return 0;
}

static void __exit exit_mod(void)
{
        pr_info("Goodbye, world!\n");
        return;
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module1Task1");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
