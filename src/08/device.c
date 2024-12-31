#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

void beep_relase(struct device *dev) {
	printk("bye bye, release!!! \n");
}

struct resource beep_res[] = {
	[0] = {
		.start = 0x20ac000,
		.end   = 0x20ac003,
		.flags  = IORESOURCE_MEM,
		.name  = "GPIO5_DR"
	}
};

struct platform_device beep_device = {
	.name = "beep_test",
	.id = -1,
	.resource = beep_res,
	.num_resources = ARRAY_SIZE(beep_res),
	.dev = {
		.release = beep_relase
	}
};

static int device_init(void) {
	printk("hello world!! \n");
	return platform_device_register(&beep_device);
}

static void device_exit(void) {
	printk("bye bye!! \n");
	platform_device_unregister(&beep_device);
}

module_init(device_init);
module_exit(device_exit);

MODULE_LICENSE("GPL");

