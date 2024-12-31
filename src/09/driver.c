#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

int beep_probe(struct platform_device *pdev) {
	printk("beep_probe!!! \n");
	return 0;
}

int beep_remove(struct platform_device *pdev) {
	printk("beep_remove!!! \n");
	return 0;
}


struct platform_driver beep_device = {
	.probe = beep_probe,
	.remove = beep_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = "beep_test"
	}
};

static int beep_drive_init(void) {
	int ret = 0;

	ret = platform_driver_register(&beep_device);
	if (ret < 0) {
		printk("platform_drive_register error !!! \n");
		return ret;
	}

	printk("platform driver register success !!! \n");
	return 0;
}

static void beep_drive_exit(void) {
	printk("bye bye!! \n");
	platform_driver_unregister(&beep_device);
}

module_init(beep_drive_init);
module_exit(beep_drive_exit);

MODULE_LICENSE("GPL");

