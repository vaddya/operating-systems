#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#define MODULE_NAME "TestModule"
#define DEVICE_NAME "chardev"
#define MAJOR_NUMBER 126
#define BUF_LENGTH 128

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(MODULE_NAME);
MODULE_VERSION("0.1");

int device_init(void);
void device_exit(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

module_init(device_init);
module_exit(device_exit);

static int major;
static char driver_buffer[BUF_LENGTH];
static int cursor = 0;
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

int device_init(void) {
    major = register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT
        "Registering char device failed for major=%d\n", major);
        return -1;
    };
    printk(KERN_INFO
    "%s: major number %d. Use mknod /dev/%s c %d 0\n", MODULE_NAME, major, DEVICE_NAME, major);
    return 0;
}

void device_exit(void) {
    printk(KERN_INFO
    "%s: removing character device /dev/%s\n", MODULE_NAME, DEVICE_NAME);
    unregister_chrdev(major, DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO
    "%s: opening character device /dev/%s\n", MODULE_NAME, DEVICE_NAME);
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO
    "%s: releasing character device /dev/%s\n", MODULE_NAME, DEVICE_NAME);
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *fd, char *buffer, size_t length, loff_t *offset) {
    ssize_t bytes = 0;

    printk(KERN_INFO
    "%s: reading from character device /dev/%s\n", MODULE_NAME, DEVICE_NAME);
    for (; length && cursor > 0; length--, bytes++) {
        put_user(driver_buffer[--cursor], buffer++);
    }

    printk(KERN_INFO
    "%s: %ld bytes were read from /dev/%s'.\n", MODULE_NAME, bytes, DEVICE_NAME);

    return bytes;
}

static ssize_t device_write(struct file *fd, const char *buffer, size_t length, loff_t *offset) {
    ssize_t bytes = 0;

    printk(KERN_INFO
    "%s: writing to character device /dev/%s\n", MODULE_NAME, DEVICE_NAME);

    for (; length && cursor < BUF_LENGTH; cursor++, length--, bytes++) {
        get_user(driver_buffer[cursor], buffer++);
    }

    printk(KERN_INFO
    "%s: %ld bytes were written to /dev/%s'.\n", MODULE_NAME, bytes, DEVICE_NAME);

    return bytes;
}
