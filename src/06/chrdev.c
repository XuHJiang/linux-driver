#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>

#define DEVICE_NUMBER 1
#define DEVICE_SNAME "schrdev"
#define DEVICE_DNAME "dchrdev"

#define DEVICE_MINOR_NUMBER 0

static int major_num, minor_num;

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
		
	printk("hello world!! \n");
	return 0;
}

static void hello_exit(void) {
	unregister_chrdev_region(MKDEV(major_num, minor_num), DEVICE_NUMBER);
	printk("bye bye!! \n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

