package test0504;

/*
 * 本地内部类测试
 */
public final class Outer {
	public static final int total_number = 5;
	public int id = 123;
	public void func1(){
		final int a = 15;
		String s = "cqd";
		class Inner{
			public void func2(){
				System.out.println(total_number);
				System.out.println(id);
				System.out.println(a);
				/*
				 * 本地内部类只能访问本地final变量
				 */
				//System.out.println(s);
			}
		}
		new Inner().func2();
	}
	
//	public static void main(String args[]){
//		Outer t = new Outer();
//		t.func1();
//	}
}
