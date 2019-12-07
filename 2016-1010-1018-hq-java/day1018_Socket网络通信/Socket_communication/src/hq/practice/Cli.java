package hq.practice;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

import java.net.UnknownHostException;

public class Cli {
	public static void main(String[] args) {
		try {
			// 指定服务端的ip地址，端口号
			Socket socket = new Socket("127.0.0.1", 8888);

			// 客户端给服务器发消息

			String str = "i'm client";

			// 打开输出流

			OutputStream os = socket.getOutputStream();// 拿到字节输出流

			PrintWriter pw = new PrintWriter(os);// 打印输出流

			pw.println(str);// 输出一条信息

			pw.flush();

		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
