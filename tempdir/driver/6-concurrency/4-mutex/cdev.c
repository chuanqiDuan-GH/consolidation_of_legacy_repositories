#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define CDEV_MAJOR  512
#define CDEV_MINOR  2
#define CDEV_AMOUNT 10	
#define DATA_SIZE   64

char *devName = "mutDevName";
struct cdev mutDev;
char myData[DATA_SIZE] = "i'm kernel message";
//定义互斥锁
struct mutex mut;


static int mut_open(struct inode *inode, struct file *file)
{
    //加锁
    mutex_lock(&mut);

    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static int mut_release(struct inode *inode, struct file *file)
{
    //解锁
    mutex_unlock(&mut);

    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

ssize_t mut_read(struct file *file, char __user *to, size_t len, loff_t *pos)
{
    //获取信号量

    //发送数据的长度不能超过buf的最大长度
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    if(copy_to_user(to, myData, len))
	return -EFAULT;

    //返回发送数据的长度
    return len;
}

ssize_t mut_write(struct file *file, const char __user *from, size_t len, loff_t *pos)
{
    //接收数据的长度不能超过buf的最大长度
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    memset(myData, 0, 64);
    if(copy_from_user(myData, from,  len))
	return -EFAULT;

    printk("data from user space:%s\n", myData);

    //释放信号量
    return len;
}

struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = mut_open,
    .release = mut_release,
    .read = mut_read,
    .write = mut_write,
    //.unlocked_ioctl = mut_ioctl,
};

static int __init mut_init(void)
{

    int ret;
    printk("mut_cdev_init\n"); 
    //申请设备号
    ret = register_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT, devName);
    if(ret < 0)
    {
	printk("register_chrdev_region failed\n"); 
	return -1;
    }

    //初始化字符设备
    cdev_init(&mutDev, &fops);

    //注册字符设备
    ret = cdev_add(&mutDev, MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    if(ret < 0)
    {
	printk("cdev_add failed\n"); 
	unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
	return -1;
    }
    
    //初始化互斥锁
    mutex_init(&mut);

    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static void __exit mut_exit(void)
{
    //释放设备号
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);

    //注销字符设备
    cdev_del(&mutDev);
    
    printk("%s %d\n", __func__, __LINE__);
}

module_init(mut_init);
module_exit(mut_exit);

MODULE_LICENSE("GPL");
