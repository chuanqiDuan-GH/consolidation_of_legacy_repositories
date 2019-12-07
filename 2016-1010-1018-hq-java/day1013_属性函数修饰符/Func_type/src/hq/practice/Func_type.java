package hq.practice;

public class Func_type {

	int ret = 1;

	public void func1() {

		System.out.println("无参数无返回值");
	}

	public int func2() {

		System.out.print("有参数无返回值");
		return ret;
	}

	public void func3(int num) {

		System.out.println("有参数无返回值" + num);
	}

	public int func4(int num) {

		System.out.println("有参数有返回值" + num);
		return num;
	}

}
