#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/delay.h>

#define CDEV_MAJOR  512
#define CDEV_MINOR  2
#define CDEV_AMOUNT 10	
#define DATA_SIZE   64

char *devName = "lsDevName";
struct cdev lsDev;
char myData[DATA_SIZE] = "i'm kernel message";
int flag = 1;
//定义自旋锁
spinlock_t lock;

static int ls_open(struct inode *inode, struct file *file)
{
    spin_lock(&lock);
    if(--flag)
    {
	printk("in flag\n"); 
	flag++;
	spin_unlock(&lock);
	return -EBUSY;
    }
    ssleep(20);
    spin_unlock(&lock);
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static int ls_release(struct inode *inode, struct file *file)
{
    spin_lock(&lock);
    flag++;
    spin_unlock(&lock);
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

ssize_t ls_read(struct file *file, char __user *to, size_t len, loff_t *pos)
{
    //发送数据的长度不能超过buf的最大长度
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    if(copy_to_user(to, myData, len))
	return -EFAULT;

    //返回发送数据的长度
    return len;
}

ssize_t ls_write(struct file *file, const char __user *from, size_t len, loff_t *pos)
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
    .open = ls_open,
    .release = ls_release,
    .read = ls_read,
    .write = ls_write,
    //.unlocked_ioctl = ls_ioctl,
};

//自旋锁防止并发
static int __init sl_cdev_init(void)
{
    int ret;
    printk("sl_cdev_init\n"); 
    //申请设备号
    ret = register_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT, devName);
    if(ret < 0)
    {
	printk("register_chrdev_region failed\n"); 
	return -1;
    }

    //初始化字符设备
    cdev_init(&lsDev, &fops);

    //注册字符设备
    ret = cdev_add(&lsDev, MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    if(ret < 0)
    {
	printk("cdev_add failed\n"); 
	unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
	return -1;
    }

    //初始化自旋锁
    spin_lock_init(&lock);
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static void __exit sl_cdev_exit(void)
{

    //释放设备号
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);

    //注销字符设备
    cdev_del(&lsDev);
    
    printk("%s %d\n", __func__, __LINE__);
}


module_init(sl_cdev_init);
module_exit(sl_cdev_exit);

MODULE_LICENSE("GPL");
