#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/device.h>
#include <linux/sched.h>

#define CDEV_MAJOR  512
#define CDEV_MINOR  2
#define CDEV_AMOUNT 3
#define DATA_SIZE   64

char *devName = "myDevName";
struct cdev myDev;
char myData[DATA_SIZE] = "i'm kernel message";
struct class *pcls = NULL;
struct device *pdev = NULL;
//定义等待头队列
wait_queue_head_t my_queue;
int wait_avail_flag = 0;  //等待队列标识,记录可读数据,等于0表示没数据,阻塞等待

static int my_open(struct inode *inode, struct file *file)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk("%s %d\n", __func__, __LINE__);
    return 0;
}

ssize_t my_read(struct file *file, char __user *to, size_t len, loff_t *pos)
{
    if(file->f_flags & O_NONBLOCK)
    {
	if(wait_avail_flag <= 0) 
	    return -EAGAIN;
    }
    else
    {
	if(wait_avail_flag <= 0)
	{
	    //wait_event()也是等待阻塞函数,但是不能被任何中断打断,_interruptible可以被打断
	    //wait_avail_flag>0表示通过阻塞的条件是有数据可读
	    //用户调用设备驱动后,会阻塞在这里,等待条件达成(wait_avail_flag>0), 
	    //手动或自动的向设备文件内写入数据后会使条件达成,手动写入设备文件需要切换到root用户,sudo命令echo无效
	    wait_event_interruptible(my_queue, wait_avail_flag>0); 
	}
    }

    if(len > wait_avail_flag)
	len = wait_avail_flag;

    //发送数据的长度不能超过buf的最大长度
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    if(copy_to_user(to, myData, len))
	return -EFAULT;

    //返回发送数据的长度
    return len;
}

ssize_t my_write(struct file *file, const char __user *from, size_t len, loff_t *pos)
{
    //接收数据的长度不能超过buf的最大长度
    if(len > DATA_SIZE)
	len = DATA_SIZE;

    memset(myData, 0, 64);
    if(copy_from_user(myData, from,  len))
	return -EFAULT;

    wait_avail_flag = len;
    wake_up(&my_queue);
    printk("data from user space:%s\n", myData);

    return len;
}

struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
    //.unlocked_ioctl = my_ioctl,
};

static int __init my_init(void)
{

    int ret;
    int i;
    int j;
    printk("my_cdev_init\n"); 

    //申请设备号
    ret = register_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT, devName);
    if(ret < 0)
    {
	printk("register_chrdev_region failed\n"); 
	return -1;
    }

    //初始化字符设备
    cdev_init(&myDev, &fops);

    //注册字符设备
    ret = cdev_add(&myDev, MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    if(ret < 0)
    {
	printk("cdev_add failed\n"); 
	ret = -1;
	goto UNREG_CHRDEV;
    }

    //初始化等待队列
    init_waitqueue_head(&my_queue);

    //自动创建设备文件节点,不许要用mknod手动创建设备文件节点,
    //只需要创建一次,所以在init函数内完成
    /*
    关键函数:
    class_create()
    device_create()
    class_destory()
    device_destory()
    */

    pcls = class_create(THIS_MODULE, "my");
    if(IS_ERR(pcls))
    {
	ret = PTR_ERR(pcls);
	goto CDEV_DEL; 
    }

    for(i=0; i<CDEV_AMOUNT; i++)
    {
	pdev = device_create(pcls, NULL, MKDEV(CDEV_MAJOR, CDEV_MINOR+i), NULL, "myDev%d", i); 
	if(IS_ERR(pdev))
	{
	    ret = PTR_ERR(pdev);
	    goto DEV_DESTORY;
	}
    }
    printk("%s %d\n", __func__, __LINE__);

    return 0;

DEV_DESTORY:
    for(j=0;j<i;j++) 
    {
	device_destroy(pcls, MKDEV(CDEV_MAJOR, CDEV_MINOR+j));
    }
    class_destroy(pcls);

CDEV_DEL:
    cdev_del(&myDev);

UNREG_CHRDEV:
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);
    

    return ret;
}


static void __exit my_exit(void)
{
    int i;

    //释放文件节点
    for(i=0;i<CDEV_AMOUNT;i++) 
    {
	device_destroy(pcls, MKDEV(CDEV_MAJOR, CDEV_MINOR+i));
    }
    class_destroy(pcls);

    //释放设备号
    unregister_chrdev_region(MKDEV(CDEV_MAJOR, CDEV_MINOR), CDEV_AMOUNT);

    //注销字符设备
    cdev_del(&myDev);
    
    printk("%s %d\n", __func__, __LINE__);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
