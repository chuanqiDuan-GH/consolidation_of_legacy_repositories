package hq.master;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import hq.other.Arts;
import hq.other.Stu;
import hq.other.Science;

public class Opt {

	static List<Stu> list = new ArrayList<Stu>();
	static String cou;
	static int len = 0;

	public static void size() {
		len = list.size();
	}

	public static void add() {
		String name;
		int age;
		int grand;

		System.out.println("please select your major course: art or sci");
		Scanner course = new Scanner(System.in);
		cou = course.next();
		if (!(cou.equals("art") || cou.equals("sci"))) {
			System.out.println("bad choise");
			return;
		}

		System.out.println("please input your info:");
		Scanner input = new Scanner(System.in);
		name = input.next();
		age = input.nextInt();
		grand = input.nextInt();

		System.out.println("add finish");
		if (cou.equals("art")) {
			Arts stu = new Arts(name, age, grand);
			list.add(stu);
		} else if (cou.equals("sci")) {
			Science stu = new Science(name, age, grand);
			list.add(stu);
		}
	}

	public static void delete() {
		System.out.println("please input index");
		Scanner input = new Scanner(System.in);
		int index = input.nextInt();
		// System.out.println(len);
		if (index > len || index < 0) {
			System.out.println("data does not exist");
			return;
		}

		list.remove(index - 1);

		System.out.println("delete success");
	}

	public static void modify() {
		int index;
		String name;
		int age;
		int grand;

		System.out.println("please input index");
		Scanner input = new Scanner(System.in);
		index = input.nextInt();
		// System.out.println(len);
		if (index > len || len < 0) {
			System.out.println("data does not exist");
			return;
		}

		System.out.println("please input data:");

		Scanner data = new Scanner(System.in);
		name = data.next();
		age = data.nextInt();
		grand = data.nextInt();

		System.out.println("modify finish");

		// 这如果Stu类内的这三个属性不声明为public,这里是无法访问到的,或者采用另一种方式去修改，在Stu类内写getter和setter
		list.get(index - 1).name = name;
		list.get(index - 1).age = age;
		list.get(index - 1).grade = grand;
	}

	public static void show() {

		for (Stu stu : list) {
			stu.show();
			stu.course();
		}
	}
}
