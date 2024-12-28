#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define GPIO5_DR 0x114000A4  // 每个开发板管脚是不一样的,虚拟机没成功 

unsigned int *vir_gpio5_dr;

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

	if (kbuf[0] == 1) {
		printk("aaaaaaa\n");
		*vir_gpio5_dr |= (1 << 1);
	} else if (kbuf[0] == 0) {
		*vir_gpio5_dr &= ~(1 << 1);
	}
	
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

	vir_gpio5_dr = ioremap(GPIO5_DR, 4);
	if (!vir_gpio5_dr) {
		printk("GPIO5_DR ioremap error \n");
	}

	printk("GPIO5_DR ioremap is success, vir addr is %p \n", vir_gpio5_dr);

	return 0;
}

static void misc_exit(void) { 

	misc_deregister(&misc_dev);
	
	iounmap(vir_gpio5_dr);
	
	printk("misc unregister is success\n");

}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL"); 

