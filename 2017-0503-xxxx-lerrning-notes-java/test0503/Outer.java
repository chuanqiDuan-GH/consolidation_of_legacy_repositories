package test0503;

/*
 * 成员内部类测试
 */
public class Outer {
	private int size;
	public class Inner{
		private int counter = 10;
		public void innerFunc(){
			size++;
		}
	}
	
	public static class Inner1{
		private int counter = 10;
		public void innerFunc(){
			counter++;
		}
	}
	/*
	 * 内部类作为外部类成员被调用
	 */
	public void outerFunc(){
		Inner inner = new Inner();
		inner.innerFunc();
	}
	
//	public static void main(String args[]){
//		/*
//		 * 在另一个外部类中使用非静态内部类中定义的方法时，
//		 * 要先创建外部类的对象，再创建与外部类相关的内部类的对象，
//		 * 再调用内部类的方法
//		 */
//		Outer outer = new Outer();
//		Inner inner = outer.new Inner();
//		/*
//		 * static 内部类相当于其外部类的 static 成分，
//		 * 它的对象与外部类对象间不存在依赖 关系，
//		 * 因此可直接创建
//		 */
//		Outer.Inner1 ineer1 = new Outer.Inner1();
//		
//		inner.innerFunc();
//		outer.outerFunc();
//		
//		System.out.println(outer.size);
//		System.out.println(inner.counter);
//	}
}
