#include <linux/init.h>
#include <linux/module.h>
#include <linux/param.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/kernel.h>

#define CLASS_NAME  "mycls"

static struct class *chclass = NULL;
static struct device *chdev = NULL;

static int major;
static char msg[256];
static char *msg_ptr;

static char *node_name;
module_param(node_name, charp, 0);
MODULE_PARM_DESC(node_name, "Node name");

static int device_open(struct inode *inode, struct file *filp)
{
        return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
        return 0;
}

static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
        int bytes = 0;
        while (length && *msg_ptr) {
                put_user(*(msg_ptr++), buffer++);
                length--;
                bytes++;
        }
        return bytes;
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
        return 0;
}

static struct file_operations fops = {
        .read = device_read,
        .write = device_write,
        .open = device_open,
        .release = device_release
};

static int __init init_mod(void)
{
        printk(KERN_NOTICE "Module loaded!\n");

        major = register_chrdev(0, node_name, &fops);

        if (major < 0) {
                printk(KERN_ALERT "Registering char device failed with %d\n", major);
                return major;
        }
        sprintf(msg, "%d\n", major);
        msg_ptr = msg;

        // Register the device class
        chclass = class_create(THIS_MODULE, CLASS_NAME);
        if (IS_ERR(chclass)) {
                unregister_chrdev(major, node_name);
                printk(KERN_ALERT "Failed to register device class\n");
                return PTR_ERR(chclass);
        }

        // Register the device driver
        chdev = device_create(chclass, NULL, MKDEV(major, 0), NULL, node_name);
        if (IS_ERR(chdev)) {
                class_destroy(chclass);
                unregister_chrdev(major, node_name);
                printk(KERN_ALERT "Failed to create the device\n");
                return PTR_ERR(chdev);
        }
        return 0;
}

static void __exit exit_mod(void)
{
        device_destroy(chclass, MKDEV(major, 0));
        class_unregister(chclass);
        class_destroy(chclass);
        unregister_chrdev(major, node_name);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module3Task1");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
