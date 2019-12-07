package hq.master;

import java.util.ArrayList;
import java.util.Scanner;

import hq.other.Science;
import hq.other.Arts;
import hq.other.Stu;

public class Run {
	public static void main(String[] args) {

		// Science stu1 = new Science("alpha", 1, 2);
		// Science stu2 = new Science("beta", 3, 4);
		//
		// ArrayList<Stu> list = new ArrayList<Stu>();
		// list.add(stu1);
		// list.add(stu2);
		// for (Stu stu : list) {
		// ((Science) stu).show();
		// stu.course();
		// }

		String symbol;
		while (true) {
			Opt.size();
			Scanner input = new Scanner(System.in);
			symbol = input.next();
			if (symbol.equals("add")) {
				Opt.add();
			} else if (symbol.equals("delete")) {
				Opt.delete();
			} else if (symbol.equals("modify")) {
				Opt.modify();
			} else if (symbol.equals("show")) {
				Opt.show();
			}
			else if (symbol.equals("bye")) {
				//System.err.println("b");
				break;
			}
			else
			{
				System.out.println("wrong input T.T");
			}
		}
		System.out.println("thx for using ^-^");
	}
}
