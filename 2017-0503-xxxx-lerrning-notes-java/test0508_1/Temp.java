package test0508_1;


/**
 * 将下面类中的变量和方法改为静态的， 使程序能正确编译执行。
 * 如果保持用实例变量和 方法就必须创建对象，
 * 请创建 A 的对象并通过该对象来引用实例变量和方法。
 * @author cqd
 *
 */
public class Temp {
    int a =  9;
    public void show(int a){
	System.out.println(a * 10);
    }

    public static void main(String[] args){
	Temp tt = new Temp();
	tt.a += tt.a;
	tt.show(tt.a);
    }
}
