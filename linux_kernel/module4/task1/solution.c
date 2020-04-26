#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/list_sort.h>

struct module_list
{
    char name[128];
    struct list_head list;
};

static struct module_list mlst;

static int cmp(void *priv, struct list_head *a, struct list_head *b)
{
        struct module_list *ela, *elb;

        ela = container_of(a, struct module_list, list);
        elb = container_of(b, struct module_list, list);

        return strcmp(ela->name, elb->name);
}

static void get_modules(void)
{
        struct module *mod;
        struct list_head *pos;
        struct module_list *new_data;

        INIT_LIST_HEAD(&mlst.list);
        list_for_each(pos, THIS_MODULE->list.prev) {
                mod = container_of(pos, struct module, list);
                new_data = kmalloc(sizeof(struct module_list), GFP_KERNEL);
                if ((unsigned long) pos >= MODULES_VADDR) {
                        snprintf(new_data->name, 64, "%s", mod->name);
                }
                list_add(&new_data->list, &mlst.list);
        }
}

static void list_modules(void)
{
        struct list_head *pos;
        struct module_list *ptr;
        list_sort(NULL, &mlst.list, cmp);
        list_for_each(pos, &mlst.list) {
                ptr = list_entry(pos, struct module_list, list);
        }
}

static ssize_t my_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        struct list_head *pos;
        struct module_list *ptr;
        int size = 0;
        list_for_each(pos, &mlst.list) {
                ptr = list_entry(pos, struct module_list, list);
                size += sprintf(buf + size, "%s\n", ptr->name);
        }
        return size;
}

static ssize_t my_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
        return count;
}

static struct kobj_attribute foo_attribute = __ATTR(my_sys, 0755, my_show, my_store);

static struct attribute *attrs[] = {
        &foo_attribute.attr,
        NULL,
};

static struct attribute_group attr_group = {
        .attrs = attrs,
};

static struct kobject *example_kobj;

static int __init init_mod(void)
{
        int retval;

        get_modules();
        list_modules();

        example_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
        if (!example_kobj)
                return -ENOMEM;

        /* Create the files associated with this kobject */
        retval = sysfs_create_group(example_kobj, &attr_group);
        if (retval)
                kobject_put(example_kobj);

        return retval;
}

static void __exit exit_mod(void)
{
        kobject_put(example_kobj);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module4Task1");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
