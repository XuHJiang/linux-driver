#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

#define DEVICE_NUMBER 1
#define DEVICE_SNAME "schrdev"
#define DEVICE_DNAME "dchrdev"

#define DEVICE_MINOR_NUMBER 0

static int major_num, minor_num;

static struct cdev cdev;

int chrdev_open(struct inode *node, struct file *file) {

	printk("chrdev_open open \n");
	return 0;
}

struct file_operations chrdev_ops = {
	.owner = THIS_MODULE,
	.open = chrdev_open
};

// 模块传参
module_param(major_num, int, S_IRUSR);
module_param(minor_num, int, S_IRUSR);

//module_param_array(a, int, &count, S_IRUSR);

static int hello_init(void) {
	dev_t dev_num;
	int ret;

	if (major_num) {
		// 静态分配设备号
		printk("major_num is %d \n", major_num);
		printk("minor_num is %d \n", minor_num);
	
		dev_num = MKDEV(major_num, minor_num);
		
		ret = register_chrdev_region(dev_num, DEVICE_NUMBER, DEVICE_SNAME);
		if (ret < 0) {
			printk("register_chrdev_region error!! \n");
		}
		printk("register_chrdev_region success!! \n");
	} else {
		// 动态分配设备号
		ret = alloc_chrdev_region(&dev_num, DEVICE_MINOR_NUMBER, DEVICE_NUMBER, DEVICE_DNAME);
		if (ret < 0) {
			printk("alloc_chrdev_region error!! \n");
		}
		printk("alloc_chrdev_region success!! \n");

		major_num = MAJOR(dev_num);
		minor_num = MINOR(dev_num);
		
		printk("major_num is %d \n", major_num);
		printk("minor_num is %d \n", minor_num);
	}

	cdev.owner = THIS_MODULE;
	cdev_init(&cdev, &chrdev_ops);

	cdev_add(&cdev, dev_num, 1);
	
	return 0;
}

static void hello_exit(void) {
	unregister_chrdev_region(MKDEV(major_num, minor_num), DEVICE_NUMBER);
	cdev_del(&cdev);
	printk("bye bye!! \n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

