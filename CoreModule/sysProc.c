#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/string.h>

#define PROC_NAME "myproc"
#define SYSFS_DIR "mykmod"
#define SYSFS_ATTR "myval"
#define BUFFER_LEN 128

static char test_value[BUFFER_LEN] = "Hello, world!";
static struct proc_dir_entry *proc_file;
static struct kobject *sysfs_kobj;

static ssize_t proc_read(struct file *fd, char __user *buf, size_t size, loff_t *off)
{
	ssize_t ret;

	if (!buf || size == 0) 
	{
		pr_err("proc_read Переданы неверные аргументы\n");
		return -EINVAL;
	}

	ret = simple_read_from_buffer(buf, size, off, test_value, strlen(test_value));
	if (ret < 0) 
		pr_err("simple_read_from_buffer\n",);

	pr_info("proc_read Прочитано %zd байт\n", ret);
	return ret;
}


static ssize_t proc_write(struct file *fd, const char __user *buf, size_t size, loff_t *off)
{
	if (!buf || size == 0) 
	{
		pr_err("proc_write Переданы неверные аргументы\n");
		return -EINVAL;
	}

	ssize_t ret = simple_write_to_buffer(test_value, BUFFER_LEN, off, buf, size);

	if (ret <= 0) 
	{
		pr_err("simple_write_to_buffer\n");
		return -EFAULT;
	}

	pr_info("proc_write Записано %zu байт\n", to_copy);

	return size;
}

static const struct proc_ops proc_fops = 
{
	.read = proc_read,
	.write = proc_write,
};


static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	if (!buf) 
	{
		pr_err("sysfs_show Переданы неверные аргументы\n");
		return -EINVAL;
	}

	return scnprintf(buf, BUFFER_LEN, "%s\n", test_value);
}


static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t size)
{
	size_t to_copy;

	if (!buf || size == 0) 
	{
		pr_err("sysfs_store Переданы неверные аргументы\n");
		return -EINVAL;
	}

	to_copy = min(size, sizeof(test_value) - 1);
	memset(test_value, 0, sizeof(test_value));

	strncpy(test_value, buf, to_copy);
	test_value[to_copy] = '\0';

	pr_info("sysfs_store записано %zu байт\n", to_copy);

	return size;
}

static struct kobj_attribute myval_attr = __ATTR(myval, 0664, sysfs_show, sysfs_store);


static int init_module(void)
{
	proc_file = proc_create(PROC_NAME, 0666, NULL, &proc_fops);
	if (!proc_file) 
	{
		pr_err("Ошибка при создании объекта proc\n");
		return -ENOMEM;
	}

	sysfs_kobj = kobject_create_and_add(SYSFS_DIR, kernel_kobj);
	if (!sysfs_kobj) 
	{
		pr_err("Ошибка при создании объекта /sys/kernel\n");
		remove_proc_entry(PROC_NAME, NULL);
		return -ENOMEM;
	}

	if (sysfs_create_file(sysfs_kobj, &myval_attr.attr)) {
		pr_err("Ошибка при создании sysfs\n");
		kobject_put(sysfs_kobj);
		remove_proc_entry(PROC_NAME, NULL);
		return -ENOMEM;
	}

	pr_info("Модуль успешно загрузился\n");
	return 0;
}


static void cleanup_module(void)
{
	remove_proc_entry(PROC_NAME, NULL);
	sysfs_remove_file(sysfs_kobj, &myval_attr.attr);
	kobject_put(sysfs_kobj);
	pr_info("Модуль выгружен\n");
}

MODULE_LICENSE("GPL");