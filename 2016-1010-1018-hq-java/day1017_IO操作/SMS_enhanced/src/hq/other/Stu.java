package hq.other;

import java.io.Serializable;

@SuppressWarnings("serial")
/*
 * 添加文件io的处理的之后,也就是将增删改查后的集合存放在文件中,
 * 一但在增删改查相关操作函数中调用File_io类内的读写操作函数时(read_data(),write_data()),
 * 就会出现程序崩溃,并打印java.io.NotSerializableException错误,
 * 这标志：被当做集合的类型的接口或抽象类未实现序列化
 */
public abstract class Stu implements Serializable{

	public String name;
	public int age;
	public int grade;

	public void show() {
		System.out.print(name + " ");
		System.out.print(age + " ");
		System.out.println(grade);
	}

	public abstract void course();
}
