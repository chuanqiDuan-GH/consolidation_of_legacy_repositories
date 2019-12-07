package hq.practice;

import java.util.Scanner;

public class Lottery {
	public static void main(String[] args) {

		//String num = new String();
		int num;
		int sum = 0;

		System.out.print("please input four numbers:");
		Scanner input = new Scanner(System.in);

		num = input.nextInt();
		//System.out.println(num);
		
		while (0 != (num % 10)) {
			
			sum += (num % 10);
			num /= 10;
		}
		System.out.println(sum);
		return;
	}
	
}
