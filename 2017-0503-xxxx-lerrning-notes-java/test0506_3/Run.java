package test0506_3;

/*
 * Java基础教程第四章习题-3：
 * 编写 MyPoint 的一个子类 MyXYZ，表示三维坐标点，
 * 重写 toString 方法用来显示 这个对象的 x、y、z 的值，
 * 如显示（1，2，3），最后用 main 方法测试。
 */
public class Run {
	
	public static void main(String[] args){

		MyXYZ point1 = new MyXYZ();
		System.out.println(point1.ToString());
		
		MyXYZ point2 = new MyXYZ(1, 2, 3);
		System.out.println(point2.ToString());
	}
}
