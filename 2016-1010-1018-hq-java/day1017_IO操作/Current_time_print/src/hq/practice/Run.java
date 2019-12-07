package hq.practice;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Run implements Runnable {

	static int flag = 0;

	public static void main(String[] args) {

		String symbol = "";
		
		//thread.start();
		while (true) {					
		Scanner input = new Scanner(System.in);
		symbol = input.next();
		
			if (symbol.equals("stop")) {
				flag = 0;

			} else if (symbol.equals("start")) {
				
				if(flag == 0)
				{
					System.out.println("create new sub thread");
					Thread thread = new Thread(new Run());
					thread.start();
				}
				flag = 1;
			}
			else if(symbol.equals("bye"))
			{
				System.out.println("main thread exit");
				break;
			}
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub

		while (true && flag == 1) {
			Date cur_time = new Date();
			SimpleDateFormat sim = new SimpleDateFormat(
					"EEE, d MMM yyyy HH:mm:ss");

			String date_str = sim.format(cur_time);
			System.out.println(date_str);
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		System.out.println("sub thread exit");
	}
}
