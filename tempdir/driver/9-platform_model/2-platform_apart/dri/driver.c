#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/platform_device.h>

int my_probe(struct platform_device *dev)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

int my_remove(struct platform_device *dev)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

struct platform_driver myDriver =
{
    .probe = my_probe,
    .remove = my_remove,
    .driver = 
    {
	.name = "myDev"	, 
    },
};

static int __init my_init(void)
{
    platform_driver_register(&myDriver);

    return 0;
}

static void __exit my_exit(void)
{
    platform_driver_unregister(&myDriver);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
