
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>

#define CDEV_MAJOR 1024
#define CDEV_MINOR_FIRST 8
#define CDEV_MINOR_COUNT 10

#define DATA_SIZE 64

const char *devname = "hello_dev";
struct cdev hello_dev;
struct class *pcls = NULL;
struct device *pdevice = NULL;

char data[DATA_SIZE] = {0};
int available_num = 0; // 有多少字节可读
wait_queue_head_t  my_queue;

static int hello_open(struct inode *inode, struct file *file)
{
	printk("%s,%s,%d\n", __FILE__, __func__, __LINE__);		
	
	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	printk("%s,%s,%d\n", __FILE__, __func__, __LINE__);	
	
	return 0;
}

ssize_t hello_read (struct file *file, char __user *to, size_t len, loff_t *pos)
{
	printk("%s,%s,%d\n", __FILE__, __func__, __LINE__);	
	
	if(file->f_flags & O_NONBLOCK) {  // 非阻塞方式打开
		if(available_num <= 0) {
			return -EAGAIN;
		} 
	} else {  // 阻塞方式打开
		if(available_num <= 0) {
			//wait_event(my_queue, available_num>0);
			wait_event_interruptible(my_queue, available_num>0);
		}
	}
	
	if(len>available_num) {
		len = available_num;
	}
	
	if(len > DATA_SIZE) {
		len = DATA_SIZE;
	}
	
	if(copy_to_user(to, data, len)) {
		return -EFAULT;
	}
	
	available_num = 0;
	
	return len;
}

ssize_t hello_write (struct file *file, const char __user *from, size_t len, loff_t *pos)
{
	printk("%s,%s,%d\n", __FILE__, __func__, __LINE__);
	
	if(len > DATA_SIZE) {
		len = DATA_SIZE;
	}	
	
	if(copy_from_user(data, from, len)) {
		return -EFAULT;
	}
	
	available_num = len;
	wake_up(&my_queue);
	
	printk("write data: %s\n", data);
	
	return len;	
}

unsigned int hello_poll (struct file *file, struct poll_table_struct *pts)
{
	unsigned int mask = 0;

	poll_wait( file, &my_queue, pts);
	
	if (available_num>0) //可读
	{
        mask |= POLLIN | POLLRDNORM; /*标示数据可获得*/
	}   

	return mask;
}

struct file_operations fops = {
	.owner	= THIS_MODULE,
	.open	= hello_open,
	.release = hello_release,
	.read	= hello_read,
	.write	= hello_write,
	.poll	= hello_poll,
};

static int __init hello_init(void)
{
	int ret;
	int i,j;
	printk("%s,%s,%d\n", __FILE__, __func__, __LINE__);
	
	// 申请设备号
	ret = register_chrdev_region( MKDEV(CDEV_MAJOR, CDEV_MINOR_FIRST), CDEV_MINOR_COUNT, devname);
	if(ret<0) {
		printk("register_chrdev_region error\n");
		return ret;
	}
	
	// 初始化字符设备
	cdev_init(&hello_dev, &fops);
	
	// 注册字符设备
	ret = cdev_add(&hello_dev, MKDEV(CDEV_MAJOR, CDEV_MINOR_FIRST), CDEV_MINOR_COUNT);
	if(ret<0) {
		printk("cdev_add\n");
		goto UNREG_CHEDEV;
	}

	pcls = class_create(THIS_MODULE, "hello");
	if (IS_ERR(pcls)) {
		ret = PTR_ERR(pcls);
		goto CDEV_DEL;
	}
	
	for(i=0;i<CDEV_MINOR_COUNT;i++) {
		pdevice = device_create(pcls, NULL, MKDEV(CDEV_MAJOR, CDEV_MINOR_FIRST+i), NULL, "hello%d", i);
		if (IS_ERR(pdevice)) {
			ret = PTR_ERR(pdevice);
			goto DEV_DESTROY;	
		}
	}
	
	init_waitqueue_head(&my_queue);
	
	printk("init ok!\n");
	
	return 0;
	
DEV_DESTROY:
	for(j=0;j<i;j++) {
		device_destroy(pcls, MKDEV(CDEV_MAJOR, CDEV_MINOR_FIRST+j));
	}
	class_destroy(pcls);
	
CDEV_DEL:	
	cdev_del(&hello_dev);
	
UNREG_CHEDEV:	
	unregister_chrdev_region( MKDEV(CDEV_MAJOR, CDEV_MINOR_FIRST), CDEV_MINOR_COUNT);
	
	return ret;
}

static void __exit hello_exit(void)
{
	int i;
	printk("%s,%s,%d\n", __FILE__, __func__, __LINE__);	
	
	for(i=0;i<CDEV_MINOR_COUNT;i++) {
		device_destroy(pcls, MKDEV(CDEV_MAJOR, CDEV_MINOR_FIRST+i));
	}
	
	class_destroy(pcls);	
	
	// 注销字符设备 
	cdev_del(&hello_dev);
	
	// 释放设备号
	unregister_chrdev_region( MKDEV(CDEV_MAJOR, CDEV_MINOR_FIRST), CDEV_MINOR_COUNT);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jesse");
MODULE_DESCRIPTION("This is a char device");
MODULE_VERSION("1.0.0.2");
