#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

static int my_dev_id;
static int irq_num = 8;
static int irq_cnt = 0;
static struct kobject *my_kobj;

static irqreturn_t my_interrupt(int irq, void *dev_id)
{
        irq_cnt++;
        pr_info("%d\n", irq_cnt);
        return IRQ_NONE;
}

static ssize_t my_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
        return sprintf(buffer, "%d\n", irq_cnt);
}

static ssize_t my_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
        return 0;
}

static struct kobj_attribute my_attribute = __ATTR(my_sys, 0755, my_show, my_store);

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
        res = request_irq(irq_num, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id);
        if (res) {
                return -1;
        }
        return res;
}

static void __exit exit_mod(void)
{
        kobject_put(my_kobj);
        synchronize_irq(irq_num);
        free_irq(irq_num, &my_dev_id);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module4Task3");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
