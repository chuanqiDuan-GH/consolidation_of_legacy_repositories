package hq.practice;

import java.io.FileWriter;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;


public class Char_stream {
	public static void main(String[] args) {

		String path = "D:/JavaLearning/day1018_Socket网络通信/char_io/src/hq/practice/char_stream.txt";

		try {


			FileWriter fw = new FileWriter(path);
			String str = "";
			Scanner input = new Scanner(System.in);
			str = input.nextLine();

			fw.write(str);
			
			fw.close();
			
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
