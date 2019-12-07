package hq.practice;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Svr {
public static void main(String[] args) {
	
	try {
		/*
		 * ServerSocket(8888)重写方式会自动获取本机ip
		 * ServerSocket()方法有很多的重写形式，通过这些方法的重载可以实现端口号和ip号的设置
		 * 如果不设置ip号，默认会使用本机ip
		 */
		ServerSocket sso = new ServerSocket();
		sso.bind(new InetSocketAddress("127.0.0.1",8888));
		Socket socket = sso.accept();
		
		InputStream is = socket.getInputStream();
		InputStreamReader isr = new InputStreamReader(is);
		BufferedReader bfr = new BufferedReader(isr);
		
		System.out.println(bfr.readLine());
		
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
}
}
