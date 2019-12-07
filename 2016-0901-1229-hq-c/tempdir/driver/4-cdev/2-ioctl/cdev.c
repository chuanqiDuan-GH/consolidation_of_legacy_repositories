#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define CDEV_MAGIC  'C'
#define IOCTL_CMD_1 _IO(CDEV_MAGIC, 1)
#define IOCTL_CMD_2 _IOW(CDEV_MAGIC, 2, int)
#define IOCTL_CMD_3 _IO(CDEV_MAGIC, 3)

#define CDEV_MAJOR  512
#define CDEV_MINOR  2
#define CDEV_AMOUNT 10
#define DATA_SIZE   64

const char *devName = "myDev";
struct cdev myDev;
char data[DATA_SIZE] = "cdev ioctl program";


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

ssize_t myDevRead(struct file *file, char __user *to, size_t len, loff_t *pos)
{
    printk("%s %d\n", __func__, __LINE__);

    if(len > DATA_SIZE)
	len = DATA_SIZE; 

    if(copy_to_user(to, data, len))
	return -EFAULT;
    
    return len;
}

//write的第二个参数是const类型，与read的第二个参数不同
ssize_t myDevWrite(struct file *file, const char __user *from, size_t len, loff_t *pos)
{
    printk("%s %d\n", __func__, __LINE__);

    if(len > DATA_SIZE)
	len = DATA_SIZE; 

    if(copy_from_user(data, from, len))
	return -EFAULT;

    printk("%s\n", data);
    
    return len;
}

//写自定义的操作命令
//cmd传递命令，arg传递参数
long myDevLock(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch(cmd)
    {
	case IOCTL_CMD_1:
	    printk("cdev cmd 1 received\n");
	    break;
	case IOCTL_CMD_2:
	    printk("cdev cmd 2 received\n");
	    printk("arg = %d\n", arg);
	    break;
	case IOCTL_CMD_3:
	    printk("cdev cmd 3 received\n");
	    break;
	default:
	    printk("unkonw cmd");
    }
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = myDevOpen,
    .release = myDevRelease,
    .read = myDevRead,
    .write = myDevWrite,
    .unlocked_ioctl = myDevLock,
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
    //要用到字符设别结构体 struct cedv
    //要用到文件操作结构体 struct file_operations
    cdev_init(&myDev, &fops);

    //注册字符设备
    ret = cdev_add(&myDev, MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    if(ret < 0) 
    {
	printk("cdev_add failed\n");
	unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT); 
	return ret;
    }

    printk("cdev init\n");

    return 0;
}

static void __exit myDevExit(void)
{
    //注销字符设备
    cdev_del(&myDev);
    
    //释放设备号
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);

    printk("cdev exit\n");
}


module_init(myDevInit);
module_exit(myDevExit);

MODULE_LICENSE("GPL");
