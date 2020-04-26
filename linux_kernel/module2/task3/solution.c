#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "solution_node"
#define MY_MAJOR 240
#define MY_MINOR 0

static dev_t dev;
static struct cdev my_cdev;
static int cnt = 1;

static int open_cnt = 0;
static unsigned int char_cnt = 0;
static char msg_buf[16];
static char *msg_ptr;

static int device_open(struct inode *inode, struct file *filp)
{
        open_cnt++;
        sprintf(msg_buf, "%u %u\n", open_cnt, char_cnt);
        msg_ptr = msg_buf;
        return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
        return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
        if (*msg_ptr == 0) {
                return 0;
        }

        int bytes_read = 0;
        while (length && *msg_ptr) {
                put_user(*(msg_ptr++), buffer++);
                length--;
                bytes_read++;
        }
        return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
        char_cnt += len;
        return len;
}

static struct file_operations fops = {
        .read = device_read,
        .write = device_write,
        .open = device_open,
        .release = device_release
};

static int __init init_mod(void)
{
        dev = MKDEV(MY_MAJOR, MY_MINOR);
        int res = register_chrdev_region(dev, cnt, DEVICE_NAME);
        if (res < 0) {
                pr_err("Can not reg dev.");
                return res;
        }
        cdev_init(&my_cdev, &fops);
        my_cdev.owner = THIS_MODULE;
        res = cdev_add(&my_cdev, dev, cnt);
        if (res < 0) {
                pr_err("Can not add dev.");
        }
        pr_info("Module load suc.");
        return 0;
}

static void __exit exit_mod(void)
{
        cdev_del(&my_cdev);
        unregister_chrdev_region(MKDEV(MY_MAJOR, MY_MINOR), cnt);
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module2Task3");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
