package hq.practice;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Character_io {
	public static void main(String[] args) {

		File ch_fl = new File("D:\\ch_fl.txt");

		try {
			FileWriter fw = new FileWriter(ch_fl);
			// BufferedWriter bw = new BufferedWriter(fw);

			System.out.println("please input some words");
			String str = "";
			Scanner input = new Scanner(System.in);
			// str = input.next(); //只能接收中间没有空格的字符串
			str = input.nextLine(); // 可以接收中间含有空格的字符串，以回车作为结束标识符

			fw.write(str);

			fw.flush();

			// bw.close();
			fw.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// ch_fl.mkdir();
	}
}
