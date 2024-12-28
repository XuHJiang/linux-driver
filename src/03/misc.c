#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

struct file_operations misc_fops = {
	.owner = THIS_MODULE
};

struct miscdevice misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "hello_misc",
	.fops = &misc_fops
};

static int misc_init(void) {
	int ret;

	ret = misc_register(&misc_dev);
	if(ret < 0) {
		printk("misc register is error\n");
	}

	printk("misc register is success\n");

	return 0;
}

static void misc_exit(void) {

	misc_deregister(&misc_dev);
	printk("misc unregister is success\n");

}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL"); 

