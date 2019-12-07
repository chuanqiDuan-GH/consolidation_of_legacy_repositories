package test0516_1;


/**
 * 数组的复制
 * @author cqd
 *
 */
public class Run {
    public static void main(String args[]){
	int[] arr1 = {1, 2, 3, 4, 5};
	int[] arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};

	/**
	 * Java编程语言在System类中提供了一种特殊方法拷贝函数arraycopy()
	 * 参数分别为：源数组，源数组拷贝起始位置，目的数组，目的数组拷贝其实位置，拷贝长度
	 */
	System.arraycopy(arr1, 0, arr2, 0, arr1.length);

	/**
	 * 数组遍历的简易写法		
	 */
	for (int i : arr2) {
	    System.out.println(i);
	}
    }
}
