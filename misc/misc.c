#include "drv_head.h"


static int misc_open(struct inode *inode, struct file *filp);
static int misc_release(struct inode *inode, struct file *filp);
static  ssize_t misc_read(struct file *filp, char __user *buffer, size_t size, loff_t *p);
static ssize_t misc_write(struct file *filp, const char __user *buffer, size_t count, loff_t *ppos);

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = misc_open,
	.read = misc_read,
	.write = misc_write,
	.release = misc_release,
};
static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,	//动态分配次设备号
	.name = "misc",
	.fops = &fops,	//将fops和设备关联
};
static int __init misc_init(void)
{
	misc_register(&misc);
	printk("misc_init()\n");
	return 0;
}
static void __exit misc_exit(void)
{
	misc_deregister(&misc);
	printk("misc_exit\n");
}
module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("GPL");

static int misc_open(struct inode *inode, struct file *filp)
{return 0;}
static int misc_release(struct inode *inode, struct file *filp)
{return 0;}
static  ssize_t misc_read(struct file *filp, char __user *buffer, size_t size, loff_t *p)
{return 0;}
static ssize_t misc_write(struct file *filp, const char __user *buffer, size_t count, loff_t *ppos)
{return 0;}