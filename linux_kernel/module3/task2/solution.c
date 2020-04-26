#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define MOD_NAME "my_node"

static const int major = 240;
static const int minor = 0;

static ssize_t open_cnt = -1;

static struct cdev hcdev;
static const int BUF_SIZE = 255;

static int device_open(struct inode *inode, struct file *filp)
{
        ++open_cnt;
        filp->private_data = kcalloc(BUF_SIZE + 1, 1, GFP_KERNEL);
        if (!filp->private_data) {
                return -ENOMEM;
        }
        sprintf(filp->private_data, "%lu", open_cnt);
        return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
        kfree(filp->private_data);
        return 0;
}

static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
        size_t size = (*offset + length) < BUF_SIZE ? length : strlen(filp->private_data + *offset);
        if (size == 0) {
                return 0;
        }
        unsigned long uncopied = copy_to_user(buffer, filp->private_data + *offset, size);
        if (uncopied > 0) {
                return -EINVAL;
        }
        *offset += size;
        return size;
}

static ssize_t device_write(struct file *filp, const char __user *buffer, size_t length, loff_t *offset)
{
        size_t size = (*offset + length) < BUF_SIZE ? length : BUF_SIZE - *offset;
        if (size == 0) {
                return 0;
        }
        unsigned long uncopied = copy_from_user(filp->private_data + *offset, buffer, size);
        if (uncopied > 0) {
                return -EINVAL;
        }
        *offset += size;
        return size;
}

static loff_t device_llseek(struct file *filp, loff_t offset, int origin)
{
        loff_t pos;
        switch (origin) {
                case SEEK_SET:
                        pos = offset;
                        break;
                case SEEK_CUR:
                        pos = filp->f_pos + offset;
                        break;
                case SEEK_END:
                        pos = strlen(filp->private_data) + offset;
                        break;
                default:
                        return -EINVAL;
        }
        pos = pos > BUF_SIZE ? BUF_SIZE : pos;
        pos = pos < 0 ? 0 : pos;
        filp->f_pos = pos;
        return pos;

}

static struct file_operations fops = {
        .open    = device_open,
        .release = device_release,
        .read    = device_read,
        .write   = device_write,
        .llseek  = device_llseek
};

static int __init init_mod(void)
{
        dev_t dev = MKDEV(major, minor);
        int res = register_chrdev_region(dev, 1, MOD_NAME);
        if (res < 0) {
                pr_err("Can't register char device region\n");
                return res;
        }
        cdev_init(&hcdev, &fops);
        hcdev.owner = THIS_MODULE;
        res = cdev_add(&hcdev, dev, 1);
        if (res < 0) {
                unregister_chrdev_region(dev, 1);
                pr_err("Can not add char device\n");
                return res;
        }
        return res;
}

static void __exit exit_mod(void)
{
        cdev_del(&hcdev);
        unregister_chrdev_region(MKDEV(major, minor), 1);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Task2");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
