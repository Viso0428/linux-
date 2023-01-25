#include "drv_head.h"

dev_t devid;
struct cdev chr_cdev;
struct class *chr_class;
struct device *chr_device;
#define CHRDASE_NAME 	"chrbase"

static int chrbase_open(struct inode *inode, struct file *filp);
static int chrbase_release(struct inode *inode, struct file *filp);
static  ssize_t chrbase_read(struct file *filp, char __user *buffer, size_t size, loff_t *p);
static ssize_t chrbase_write(struct file *filp, const char __user *buffer, size_t count, loff_t *ppos);

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = chrbase_open,
	.read = chrbase_read,
	.write = chrbase_write,
	.release = chrbase_release,
};
static int __init chrbase_init(void)
{
	int ret = 0;

	//1.申请设备号
	ret = alloc_chrdev_region(&devid, 0, 1, CHRDASE_NAME);	//动态
	if(ret < 0)
		goto chrdev_error;

	//2. 注册cdev到内核
	cdev_init(&chr_cdev, &fops);
	chr_cdev.owner = THIS_MODULE;
	ret = cdev_add(&chr_cdev, devid, 1);
	if(ret < 0)
		goto cdev_error;

	//3. 创建设备类
	chr_class = class_create(THIS_MODULE, CHRDASE_NAME);
	if(IS_ERR(chr_class))
		goto class_error;

	//4. 创建设备节点
	chr_device = device_create(chr_class, NULL, devid, NULL, CHRDASE_NAME);
	if(IS_ERR(chr_device))
		goto device_error;

	printk("chrbase_init()\n");
	return 0;

device_error:
	printk("device_create() exit\n");
	class_destroy(chr_class);	//注销类
	cdev_del(&chr_cdev);		//注销cdev
	unregister_chrdev_region(devid, 1);	//注销字符设备
class_error:
	printk("class_create() exit\n");
	cdev_del(&chr_cdev);		//注销cdev
	unregister_chrdev_region(devid, 1);	//注销字符设备
cdev_error:
	printk("cdev_add() exit\n");
	unregister_chrdev_region(devid, 1);	//注销字符设备
chrdev_error:
	printk("lloc_chrdev_region() exit\n");
	return 0;
}
static void __exit chrbase_exit(void)
{
	device_destroy(chr_class, devid);	//注销设备
	class_destroy(chr_class);			//注销类
	cdev_del(&chr_cdev);				//注销cdev
	unregister_chrdev_region(devid, 1);	//注销字符设备

	printk("chrbase_exit\n");
}
module_init(chrbase_init);
module_exit(chrbase_exit);
MODULE_LICENSE("GPL");

static int chrbase_open(struct inode *inode, struct file *filp)
{return 0;}
static int chrbase_release(struct inode *inode, struct file *filp)
{return 0;}
static  ssize_t chrbase_read(struct file *filp, char __user *buffer, size_t size, loff_t *p)
{return 0;}
static ssize_t chrbase_write(struct file *filp, const char __user *buffer, size_t count, loff_t *ppos)
{return 0;}