#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "solution_node"
#define MY_MAJOR 240
#define MY_MINOR 0

#define IOC_MAGIC 'k'

#define SUM_LENGTH _IOWR(IOC_MAGIC, 1, char*)
#define SUM_CONTENT _IOWR(IOC_MAGIC, 2, char*)

static dev_t dev;
static struct cdev hcdev;
static int cnt = 1;

static long unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
        static int len = 0;
        static long num = 0;
        static long sum = 0;
        switch (cmd) {
                case SUM_LENGTH:
                        len += strlen((char *) arg);
                        return len;
                case SUM_CONTENT:
                        kstrtol((char *) arg, 10, &num);
                        sum += num;
                        return sum;
                default:
                        return -1;
        }
}

static struct file_operations fops = {
        .unlocked_ioctl = unlocked_ioctl
};

static int __init init_mod(void)
{
        dev = MKDEV(MY_MAJOR, MY_MINOR);
        int ret = register_chrdev_region(dev, cnt, DEVICE_NAME);
        if (ret < 0) {
                pr_err("Can't reg dev");
        }
        cdev_init(&hcdev, &fops);
        hcdev.owner = THIS_MODULE;
        ret = cdev_add(&hcdev, dev, cnt);
        if (ret < 0) {
                pr_err("Can't add dev");
        }
        return 0;
}

static void __exit exit_mod(void)
{
        cdev_del(&hcdev);
        unregister_chrdev_region(MKDEV(MY_MAJOR, MY_MINOR), cnt);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module4Task2");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
