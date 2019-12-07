/*这是依赖模块中的调用模块(calling),该模块中使用了另一模块(export)导出的变量和函数*/

/****************************************************************************************
加载方式|--手动加载
i	    |--1.先insmod导出模块(export.ko),在insmod调用模块(calling.ko)
		 eg:sudo insmod export.ko
	    |--2.先rmmod调用模块,再rmmod导出模块
	|--自动加载
	    |--1.分别make两模块并正确生成.ko文件
	    |--2.将存在依赖关系的两个模块的.ko文件拷贝到/lib/modules/3.5.0-23-generic/misc
		 路径下
	    |--3.在两模块文件中任意一个的路径下运行depmod命令,将依赖关系建立到系统默认文件
		 /lib/modules/3.5.0-23-generic/module.dep中
	    |--4.运行sudo modprobe xxx(调用模块文件名,calling,不需要加.ko)
	    |--5.卸载模块也只需直接卸载调用模块即可,要加-r选项
		 sudo modprobe -r xxx(调用模块文件名,calling,不需要加.ko)
*****************************************************************************************/

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
