#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/rwlock.h>

static int major = 0;
static char test_string[15] = "Hello world!";
static rwlock_t lock;


static ssize_t test_read(struct file *fd, char __user *buf, size_t size, loff_t *off)
{
    ssize_t rc;
    read_lock(&lock);
    rc = simple_read_from_buffer(test_string, 15, off, buf, size);
    read_unlock(&lock);

    return rc;
}

static ssize_t test_write(struct file *fd, const char __user *buf, size_t size, loff_t *off)
{
    ssize_t rc = 0;
    if(size > 15)
        return -EINVAL;
    write_lock(&lock);
    rc = simple_write_to_buffer(buf, size, off, test_string, 15);
    write_unlock(&lock);

    return rc;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read  = test_read,
    .write = test_write,
};


int init_module(void)
{
    rwlock_init(&lock);
    major = register_chrdev(major, "test_1", &fops);
    if (major < 0)
        return major;
    pr_info("Load of module is done. Major number = %d\n", major);
    return 0;
}


void cleanup_module(void)
{
    unregister_chrdev(major, "test_1");
    pr_info("Module is cleaned\n");
}
MODULE_LICENSE("GPL");