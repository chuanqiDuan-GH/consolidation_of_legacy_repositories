#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define CDEV_MAJOR  512
#define CDEV_MINOR  2
#define CDEV_AMOUNT 10
#define DATA_SIZE   64

char *devName = "myDevName";
struct cdev myDev;
char myData[DATA_SIZE] = "hi i'm kernel";

static int myDevOpen(struct inode *inode, struct file *file)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static int myDevRelease(struct inode *inode, struct file *file)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

ssize_t myDevRead(struct file *file, char __user *to, size_t len, loff_t *pos)
{
    if(len > DATA_SIZE)
	len = DATA_SIZE;	

    //从内核空间 读 数据并拷贝到用户空间
    if(copy_to_user(to, myData, len))
	return -EFAULT;

    return len;
}

ssize_t myDevWrite(struct file *file, const char __user *from, size_t len, loff_t *pos)
{
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    //向内核空间 写 从用户空间 拷贝过来的数据
    if(copy_from_user(myData, from, len))
	return -EFAULT;

    printk("data from user %s\n", myData);
    return len;
}

struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open  = myDevOpen,
    .release = myDevRelease,
    .read = myDevRead,
    .write = myDevWrite,
    //.unlocked_ioctl = myDevLock,
};

static int __init myDevInit(void)
{
    int ret;

    printk("%s %d\n", __func__, __LINE__);
    //申请设备号
    ret = register_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT, devName); 
    if(ret < 0)
    {
	printk("register_chrdev_region failed\n");
	return ret;
    }

    //初始化字符设备
    //初始化字符设备要关联file_operations
    cdev_init(&myDev, &fops);

    //注册字符设备
    ret = cdev_add(&myDev, MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    if(ret < 0)
    {
	printk("cdev_add failed\n"); 
	unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
	return ret;
    }
    return 0;
}

static void __exit myDevExit(void)
{
    printk("%s %d\n", __func__, __LINE__);
    //释放设备号
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);

    //注销字符设备
    cdev_del(&myDev);
}


module_init(myDevInit);
module_exit(myDevExit);

MODULE_LICENSE("GPL");
