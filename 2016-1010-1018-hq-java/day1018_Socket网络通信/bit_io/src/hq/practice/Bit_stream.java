package hq.practice;


import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

public class Bit_stream {
	public static void main(String[] args) {
		String path = "D:/JavaLearning/day1018_Socket网络通信/bit_io/src/hq/practice/bit_stream.txt";
		
		try {
			FileOutputStream fos = new FileOutputStream(path);
			Scanner input = new Scanner(System.in);
			String str = new String();
			str = input.nextLine();
			//这种字节初始化比较麻烦,要一个一个的填充byte数组
			//byte[] bt = {'j','a','v','a'};
			//通过字符串的getBytes()方法,将字符串转换成byte再放到byte数组中去,这样就比较方便
			byte[] bt = str.getBytes();
			
			//bt.lenght可以获取byte的现有长度
			fos.write(bt, 0, bt.length);
			
			fos.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
