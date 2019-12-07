#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
#define SIZE 3
/*模块参数*/

int num = 1;	//声明整型变量
//module_param传参宏函数,第一个参数变量名,第二个参数数据类型,第三个参数的访问权限
module_param(num, int, 0644);	
MODULE_PARM_DESC(num, "an integer number"); //模块参数声明,描述参数在干什么.囧rz

int arrNum = 0;
int arr[SIZE] = {0};	//声明数组
module_param_array(arr, int, &arrNum, 0644); //专门用来对数组进行传参的宏函数

static int __init MyInit(void)
{
    int i = 0;
    printk("%d\n", num); 
    for( ;i<3; i++)
    {
	printk("%d ", arr[i]);
    }
    printk("\n");
    printk("MyInit func\n");
    return 0;
}

static void __exit MyExit(void)
{

    printk("MyExit func\n");
}


module_init(MyInit);
module_exit(MyExit);
