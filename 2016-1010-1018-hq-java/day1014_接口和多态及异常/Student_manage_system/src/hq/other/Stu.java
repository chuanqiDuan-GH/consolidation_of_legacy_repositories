package hq.other;

public abstract class Stu {

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
