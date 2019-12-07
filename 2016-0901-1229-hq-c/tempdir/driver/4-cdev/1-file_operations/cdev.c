#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define CDEV_MAJOR  512	//主设备号
#define CDEV_MINOR  2	//次设备起始号
#define CDEV_AMOUNT	10  //设备数量,主设备号为512,次设备号从2开始

const char *devName = "myDev";	//设备名称
struct cdev myDev;


static int myDevOpen(struct inode* inode, struct file* file)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static int myDevRelease(struct inode* inode, struct file* file)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,   //指定该文件操作的属主(属于哪个模块)
    .open = myDevOpen,	//相关文件操作，打开操作,要定义函数去执行操作
    .release = myDevRelease,	//释放操作
};

static int __init cdevInit(void)
{
    int ret;

    //申请设备号
    ret = register_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT, devName); 
    if(ret < 0)
    {
	printk("register chrdev_region failed\n"); 
	return ret;
    }

    //初始化字符设备
    //这里要注意第二个参数是file_operations结构体
    cdev_init(&myDev, &fops);

    //注册字符设备
    ret = cdev_add(&myDev, MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    if(ret < 0)
    {
	printk("cdev_add failed\n"); 
	//如果这里注册设备失败，需要将申请的设备号释放
	unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
	return ret;
    }
    printk("cedv init\n"); 

    return  0;
}

void __exit cdevExit(void)
{
    //注销字符设备
    cdev_del(&myDev);
    //释放设备号
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);

    printk("cedv exit\n");
}

module_init(cdevInit);
module_exit(cdevExit);

MODULE_LICENSE("GPL");
