#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>

static struct kobject *my_kobj;
static int cnt = 0;

static ssize_t my_sys_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        cnt += 1;
        return sprintf(buf, "%d\n", cnt);
}

static ssize_t my_sys_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
        int res = kstrtoint(buf, 10, &cnt);
        if (res < 0) {
                return res;
        }
        return count;
}

static struct kobj_attribute my_attribute = __ATTR(my_sys, 0755, my_sys_show, my_sys_store);

static int __init init_mod(void)
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

static void __exit exit_mod(void)
{
        kobject_put(my_kobj);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module2Task1");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
