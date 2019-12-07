package hq.other;

public class Arts extends Stu {

	Arts() {

	}

	public Arts(String name, int age, int grand) {
		super.name = name;
		super.age = age;
		super.grade = grand;
	}

	// public void show() {
	// System.out.print(super.name + " ");
	// System.out.print(super.age + " ");
	// System.out.println(super.grade);
	// }

	@Override
	public void course() {
		System.out.println("i'm a arts stu.");
	}

}
