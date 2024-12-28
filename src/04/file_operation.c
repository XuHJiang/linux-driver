#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

int misc_open(struct inode *node, struct file *file) {

	printk("hello misc open \n");
	return 0;
}

int misc_release(struct inode *node, struct file *file) {

	printk("hello misc release bye bye \n");
	return 0;
}

int misc_read(struct file *file, char __user *ubuf, size_t size, loff_t *loff_t ) {
	char kbuf[64] = "read buf from misc device";

	if (copy_to_user(ubuf, kbuf, strlen(kbuf)) != 0) {
		printk("copy to user error \n");
	}
	
	printk("invoke misc read \n");
	return 0;
}

int misc_write(struct file *file, const char __user *ubuf, size_t size, loff_t *loff_t) {

	char kbuf[64] = {0};

	if (copy_from_user(kbuf, ubuf, size) != 0) {
		printk("copy from user error \n");
	}
	
	printk("recv kbuf from user is %s \n", kbuf);
	printk("invoke misc write \n");
	return 0;
}

struct file_operations misc_fops = {
	.owner = THIS_MODULE,
	.open = misc_open,
	.release = misc_release,
	.read = misc_read,
	.write = misc_write
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

