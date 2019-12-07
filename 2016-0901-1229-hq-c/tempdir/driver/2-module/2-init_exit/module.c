#include <linux/kernel.h>
#include <linux/module.h>


static int __init MyModuleInit(void)
{
    printk("MyModule init func\n");
    return 0;
}

static void __exit MyModuleExit(void)
{
    printk("MyModule exit func\n");
}

/*
因为这里通过调用加载和卸载宏来封装自己的函数，所以这里的函数可以自己定义名称,
现在只需要将对应的函数传入对应的宏函数中就可以
*/
/*
init_module是默认的模块的入口，
如果你想指定其他的函数作为模块的入口就需要module_init函数来指定。
*/
module_init(MyModuleInit);
module_exit(MyModuleExit);

//模块声明
MODULE_LICENSE("GPL");	//许可证(常用)
MODULE_AUTHOR("cqd");	//作者
MODULE_DESCRIPTION("module pratice");	//描述
MODULE_VERSION("0.0.0.1");  //版本






