#include <linux/kernel.h>
#include <linux/module.h>

/*这俩个函数的具体操作由内核模块,这里只是调用,且函数名不能写错*/

//模块加载函数,模块的入口相当于应用程序的main入口函数
int init_module(void)
{
    printk("module test by cqd: %s\n", __func__);
    return 0;
}

//模块卸载函数
void cleanup_module(void)
{
    printk("module test by cqd: %s\n", __func__);
}

