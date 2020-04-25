#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kobject.h>
#include <linux/init.h>
#include <linux/sysfs.h>

static int a = 0;
static int b = 0;
static int c[] = {0, 0, 0, 0, 0};
static int c_size = ARRAY_SIZE(c);

module_param(a, int, 0);
module_param(b, int, 0);
module_param_array(c, int, &c_size, S_IRUGO | S_IWUSR);

int sum;

static ssize_t my_sys_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        sum = a + b + c[0] + c[1] + c[2] + c[3] + c[4];
        return sprintf(buf, "%d\n", sum);
}

static ssize_t my_sys_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
        int res = kstrtoint(buf, 10, &sum);
        if (res < 0) {
                return res;
        }
        return count;
}

static struct kobj_attribute my_attribute = __ATTR(my_sys, 0755, my_sys_show, my_sys_store);
static struct kobject *my_kobj;

int __init init_mod(void)
{
        my_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
        if (!my_kobj) {
                return -ENOMEM;
        }
        int res = sysfs_create_file(my_kobj, &my_attribute.attr);
        if (res) {
                kobject_put(my_kobj);
        }
        return res;
}

void __exit exit_mod(void)
{
        kobject_put(my_kobj);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Task2");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
