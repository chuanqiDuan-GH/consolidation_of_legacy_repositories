#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include "common.h"

#define CDEV_MAJOR 512
#define CDEV_MINOR 2   

#define GPD0CON       0x114000a0
#define TIMER_BASE    0x139D0000           
#define TCFG0         0x0000               
#define TCFG1         0x0004                            
#define TCON          0x0008             
#define TCNTB0        0x000C          
#define TCMPB0        0x0010  
      
static dev_t devno;
static struct class *cls;
static struct device *test_device;

static unsigned int *gpd0con;
static void *timer_base;



static void fs4412_beep_init(void)
{
    gpd0con = ioremap(GPD0CON,4);
    timer_base = ioremap(TIMER_BASE,0x14);

    writel ((readl(gpd0con)&~(0xf<<0)) | (0x2<<0),gpd0con);
    writel ((readl(timer_base +TCFG0  )&~(0xff<<0)) | (0xff <<0),timer_base +TCFG0); 
    writel ((readl(timer_base +TCFG1 )&~(0xf<<0)) | (0x2 <<0),timer_base +TCFG1 ); 

    writel (500, timer_base +TCNTB0  );
    writel (250, timer_base +TCMPB0 );
    writel ((readl(timer_base +TCON )&~(0xf<<0)) | (0x2 <<0),timer_base +TCON ); 
}

void fs4412_beep_on(void)
{
    writel ((readl(timer_base +TCON )&~(0xf<<0)) | (0x9 <<0),timer_base +TCON );
}

void fs4412_beep_off(void)
{
    writel ((readl(timer_base +TCON )&~(0xf<<0)) | (0x0 <<0),timer_base +TCON );
}


static int beep_open (struct inode *inode, struct file *filep)
{
    //	fs4412_beep_on();
    return 0;
}

static int beep_release(struct inode *inode, struct file *filep)
{
    fs4412_beep_off();
    return 0;
}

#define BEPP_IN_FREQ 100000
static void beep_freq(unsigned long arg)
{
    writel(BEPP_IN_FREQ/arg, timer_base +TCNTB0  );
    writel(BEPP_IN_FREQ/(2*arg), timer_base +TCMPB0 );

}

static long beep_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    switch(cmd)
    {
	case BEEP_ON:
	    fs4412_beep_on();
	    break;
	case BEEP_OFF:
	    fs4412_beep_off();
	    break;
	case BEEP_FREQ:
	    beep_freq( arg );
	    break;
	default :
	    return -EINVAL;
    }
    return 0;
}

static struct file_operations beep_ops=
{
    .open = beep_open,
    .release = beep_release,
    .unlocked_ioctl = beep_ioctl,
};

static int beep_init(void)
{
    int ret;    
    devno = MKDEV(CDEV_MAJOR, CDEV_MINOR);
    ret = register_chrdev(CDEV_MAJOR,"beep",&beep_ops);

    cls = class_create(THIS_MODULE, "myclass");
    if(IS_ERR(cls))
    {
	unregister_chrdev(CDEV_MAJOR,"beep");
	return -EBUSY;
    }
    test_device = device_create(cls,NULL,devno,NULL,"beep");
    if(IS_ERR(test_device))
    {
	class_destroy(cls);
	unregister_chrdev(CDEV_MAJOR,"beep");
	return -EBUSY;
    }   
    fs4412_beep_init();
    return 0;
}

void fs4412_beep_unmap(void)
{
    iounmap(gpd0con);
    iounmap(timer_base);
}

static void beep_exit(void)
{
    fs4412_beep_unmap();

    device_destroy(cls,devno);
    class_destroy(cls);	
    unregister_chrdev(CDEV_MAJOR,"beep");
    printk("beep_exit \n");
}

module_init(beep_init);
module_exit(beep_exit);

MODULE_LICENSE("GPL");
