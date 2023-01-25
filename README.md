linux中混杂设备的定义：在linux中存在一类字符设备，它们共享一个主设备号，但次设备号不同，这类字符设备被称为混杂设备。主设备号为10。
申请混杂设备步骤:
1.定义miscdevice结构体
static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,	//动态分配次设备号
	.name = "misc",
	.fops = &fops,	//将fops和设备关联
};
2.定义file_operations结构体
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = misc_open,
	.read = misc_read,
	.write = misc_write,
	.release = misc_release,
};
3.注册/注销混杂设备
misc_register(&misc);
misc_deregister(&misc);
