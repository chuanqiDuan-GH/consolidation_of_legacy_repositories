package hq.practice;

import java.util.Scanner;

public class Run {
	public static void main(String[] args) {
		System.out.println("please input expression like 1+2 without any BLANK");
		int num1 = 0;
		int num2 = 0;
		//String symbol;
		Functions func = new Functions();

		while (true) {
			System.out.print("dcq$$:");
			Scanner input = new Scanner(System.in);
			String str = input.next();
			
			if(0 < str.indexOf('+'))
			{
				String[] arr = str.split("\\+");
				num1 = Integer.parseInt(arr[0]);
				num2 = Integer.parseInt(arr[1]);
				System.out.println(func.add(num1, num2));
			}
			else if(0 < str.indexOf('-'))
			{	
				String[] arr = str.split("\\-");
				num1 = Integer.parseInt(arr[0]);
				num2 = Integer.parseInt(arr[1]);
				System.out.println(func.mins(num1, num2));
			}
			else if(0 < str.indexOf('*'))
			{	
				String[] arr = str.split("\\*");
				num1 = Integer.parseInt(arr[0]);
				num2 = Integer.parseInt(arr[1]);
				System.out.println(func.multi(num1, num2));
			}
			else if(0 < str.indexOf('/'))
			{	
				String[] arr = str.split("\\/");
				num1 = Integer.parseInt(arr[0]);
				num2 = Integer.parseInt(arr[1]);
				System.out.println(func.devide(num1, num2));
			}
			
//			 System.out.println(num1);
//			 System.out.println(num2);

//			if (symbol.equals("+")) {
//				System.out.println(func.add(num1, num2));
//			} else if (symbol.equals("-")) {
//				System.out.println(func.mins(num1, num2));
//			} else if (symbol.equals("*")) {
//				System.out.println(func.multi(num1, num2));
//			} else if (symbol.equals("/")) {
//				System.out.println(func.devide(num1, num2));
//			}

		}
	}
}
