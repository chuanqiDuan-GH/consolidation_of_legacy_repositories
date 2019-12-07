#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/platform_device.h>

void my_release(struct device *dev)
{
    printk("%s %d\n", __func__, __LINE__);
}

struct platform_device myDevice = 
{
    .name = "myDev",
    .dev = 
    {
	.release = my_release, 
    },
};

static int __init my_init(void)
{
    platform_device_register(&myDevice);

    return 0;
}

static void __exit my_exit(void)
{
    platform_device_unregister(&myDevice);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
