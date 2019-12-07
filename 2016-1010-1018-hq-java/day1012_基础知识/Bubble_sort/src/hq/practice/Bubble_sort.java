package hq.practice;

public class Bubble_sort {
	public static void main(String[] args) {

		int tmp;
		int[] arr = { 23, 3, 42, 9, 0, 8, 3 };

		for (int i = arr.length - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {

				// if(arr[j] > arr[j+1]) //升序
				if (arr[j] < arr[j + 1]) // 降序
				{
					tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
				}
			}
		}

		for (int num : arr) {
			System.out.print(num + " ");
		}

		return;
	}
}
