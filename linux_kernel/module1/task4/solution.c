#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/device.h>

extern ssize_t get_void_size(void);
extern void submit_void_ptr(void *p);
extern ssize_t get_int_array_size(void);
extern void submit_int_array_ptr(int *p);
extern void submit_struct_ptr(struct device *p);
extern void checker_kfree(void *p);

static void *void_ptr;
static int *int_ptr;
static struct device *dev_ptr;

static int __init init_mod(void)
{
        ssize_t void_size = get_void_size();
        void_ptr = kmalloc(void_size, GFP_KERNEL);
        submit_void_ptr(void_ptr);

        ssize_t int_size = get_int_array_size();
        int_ptr = (int *) kmalloc(sizeof(int) * int_size, GFP_KERNEL);
        submit_int_array_ptr(int_ptr);

        dev_ptr = (struct device *) kmalloc(sizeof(struct device), GFP_KERNEL);
        submit_struct_ptr(dev_ptr);

        return 0;
}

static void __exit exit_mod(void)
{
        checker_kfree(void_ptr);
        checker_kfree(int_ptr);
        checker_kfree(dev_ptr);

        return;
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module1Task4");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");

