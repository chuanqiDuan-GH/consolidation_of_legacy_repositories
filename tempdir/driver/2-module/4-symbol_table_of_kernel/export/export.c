/*这是依赖模块中的导出模块(被依赖模块),该模块提供了调用模块所需的变量和函数*/

#include <linux/kernel.h>
#include <linux/module.h>

//先声明要传递的参数和函数
int num;
void ExportFunc(void)
{
    printk("%s func\n", __func__);
}

//模块参数导出,类似函数参数传递，这时模块之间的参数传递,也可以传递函数
EXPORT_SYMBOL_GPL(num);	//变量
EXPORT_SYMBOL_GPL(ExportFunc);	//函数


static int __init MyInit(void)
{
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
