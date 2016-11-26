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
char myData[DATA_SIZE] = "i'm kernel message";
//定义原子变量，并初始化为1
static atomic_t opt_available = ATOMIC_INIT(1);

static int myDevOpen(struct inode *inode, struct file *file)
{
    //atomic_dec_test()测试其是否为0，为0返回true，否则返回false
    /*
    第一次进来为1，设备可用，调用a_d_t函数后结果为true，取反为false，
    继续执行正常操作
    */
    if(!atomic_dec_and_test(&opt_available))
    {
	//当设备已经被占用时，再打开设备会进入此条件判断内，
	//但在return前需要将原子变量加1置0
	printk("device is busy\n"); 
	//退出前加1置0
	atomic_inc(&opt_available);
	return -EBUSY;
    }
    
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static int myDevRelease(struct inode *inode, struct file *file)
{
    //释放原子变量
    atomic_inc(&opt_available);
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

ssize_t myDevRead(struct file *file, char __user *to, size_t len, loff_t *pos)
{
    //发送数据的长度不能超过buf的最大长度
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    if(copy_to_user(to, myData, len))
	return -EFAULT;

    //返回发送数据的长度
    return len;
}

ssize_t myDevWrite(struct file *file, const char __user *from, size_t len, loff_t *pos)
{
    //接收数据的长度不能超过buf的最大长度
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    if(copy_from_user(myData, from,  len))
	return -EFAULT;

    printk("data from user space:%s\n", myData);

    return len;
}

struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = myDevOpen,
    .release = myDevRelease,
    .read = myDevRead,
    .write = myDevWrite,
    //.unlocked_ioctl = myDevLock,
};

static int __init myDevInit(void)
{
    int ret;

    //申请设备号 
    ret = register_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT, devName);
    if(ret < 0)
    {
	printk("register_chrdev_region failed\n");
	return ret;
    }

    //初始化字符设备
    //关联字符设备和file_operations文件操作集结构体
    cdev_init(&myDev, &fops);

    //注册字符设备
    ret = cdev_add(&myDev, MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    if(ret < 0)
    {
	printk("cdev_add failed\n"); 
	//释放设备号
	unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
	return ret;
    }
    return 0;
}

static void __exit myDevExit(void)
{
    //释放设备号
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    //注销字符设备
    cdev_del(&myDev);
}


module_init(myDevInit);
module_exit(myDevExit);

MODULE_LICENSE("GPL");
