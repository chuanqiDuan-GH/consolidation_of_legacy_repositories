package hq.practice;

public class Accumulation {
	public static void main(String[] args) {

		int amount = 0;
		int j = 1;

		for (int i = 1; i < 101; i++) {

			amount += i;
		}
		System.out.println(amount);

		amount = 1;
		while ((j++) < 100) {
			amount += j;
		}
		System.out.println(amount);

		return;
	}
}