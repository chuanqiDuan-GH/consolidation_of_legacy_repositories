/*这是依赖模块中的调用模块(calling),该模块中使用了另一模块(export)导出的变量和函数*/

/*
加载方式|--手动加载
i	    |--1.先insmod导出模块(export.ko),在insmod调用模块(calling.ko)
	    |--2.先rmmod调用模块,再rmmod导出模块
	|--自动加载
*/

#include <linux/kernel.h>
#include <linux/module.h>

//调用模块使用导出模块的变量或函数是需要进行全局声明
extern int num;
extern void ExportFunc(void);

static int __init MyInit(void)
{
    //调用
    printk("%d\n", num);
    ExportFunc();
    printk("%s func\n", __func__);
    return 0;
}

static void __exit MyExit(void)
{

    printk("%s func\n", __func__);
}

module_init(MyInit);
module_exit(MyExit);

MODULE_LICENSE("GPL");
