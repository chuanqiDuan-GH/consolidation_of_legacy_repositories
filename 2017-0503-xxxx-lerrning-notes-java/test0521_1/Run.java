package test0521;

import java.util.Arrays;
import java.util.List;

/**
 * 数组实用类Arrays
 * 此类包含用来操作数组的各种方法(比如排序和搜索)
 * @author cqd
 *
 */
public class Run {
    public static void main(String args[]){

	/**
	 * Arrays类的asList方法
	 * 返回一个指定数组支持的固定大小的列表
	 */
	List<Integer> arr = Arrays.asList(1, 2, 3);
	List<String> str = Arrays.asList("duan", "chaun", "qi");

	int arrOri[] = {1, 2, 3};
	int arrCmp[] = {1, 2, 3};
	String strOri[] = {"duan", "chuan", "qi"};
	String strCmp[] = {"duan", "chuan", "qi"};

	for (String string : str) {
	    System.out.print(string + " ");
	}	
	System.out.println();

	for (Integer in : arr) {
	    System.out.print(in + " ");
	}
	System.out.println();

	/**
	 * Arrays类的equals方法
	 * boolean equals(数组参数1,数组参数2)
	 * 比较两个数组参数是否相同，数组参数可以使基本数据类型，也可以是引用数据类型
	 */
	System.out.println("arrOri equal arrCmp is " + Arrays.equals(arrOri, arrCmp));
	System.out.println("strOri equal strCmp is " + Arrays.equals(strOri, strCmp));

	/**
	 * Arrays类的fill方法
	 * void fill(数组,数据类型)
	 * 向数组中填充数据参数,把数组中左右元素的值设置为该数据
	 * 输出:cqd cqd cqd cqd cqd
	 */
	String strFil[] = new String[5];
	Cla cc[] = new Cla[5];
	Arrays.fill(strFil, "cqd");
	Arrays.fill(cc, new Cla());
	for (String string : strFil) {
	    System.out.print(string + " ");
	}
	System.out.println();

	/**
	 * fill方法的重载
	 * void fill(数组,int fromIndex,int toIndex,数据参数 )
	 * 向数组中指定的范围填充数据参数,此范围包含fromIndex,不包含toIndex
	 * 输出:null cqd cqd null null 
	 */
	String strFill[] = new String[5];
	Arrays.fill(strFill, 1, 3, "cqd");
	for (String string : strFill) {
	    System.out.print(string + " ");
	}	
	System.out.println();

	/**
	 * binarySearch方法
	 * 查找数组元素的值与给定数据相同的元素
	 * int binarySearch(数组,数据参数)
	 * 注意:采用二分查找时必须保证数组中的元素已经按照升序排列
	 * 输出:数组元素7的下标为:3
	 */
	int arrBS[] = {2, 3, 5, 7, 9, 20};
	int ret = Arrays.binarySearch(arrBS, 7);
	System.out.println("数组元素7的下标为:" + ret);

	/**
	 * sort方法
	 * 将数组中的元素按升序排列
	 * void sort(数组)
	 */
	int arrSO[] = {9, 8, 7, 6, 5, 3};
	Arrays.sort(arrSO);
	for (int i : arrSO) {
	    System.out.print(i + " ");
	}
	System.out.println();

	/**
	 * copyOf方法
	 * 数组 copyOf(数组,int newLength)
	 * 复制指定的数组部分,截取下标0(包括)至newLength(不包括)范围
	 * 输出:2, 4, 6, 7
	 */
	int arrCO[] = {2, 4, 6, 7, 9, 10, 20};
	int arrCP[] = Arrays.copyOf(arrCO, 4);//拷贝下标0-3的元素
	for (int i : arrCP) {
	    System.out.print(i + " ");
	}
	System.out.println();

	/**
	 * copyOfRange方法
	 * 数组 copyOfRange(数组,int form,int to)
	 * 复制数组指定范围的元素到一个新数组，从from(包括)到to(不包括)
	 * 输出:4 6 7 
	 */
	int arrCPR[] = Arrays.copyOfRange(arrCO, 1, 4);
	for (int i : arrCPR) {
	    System.out.print(i + " ");
	}
	System.out.println();

	/**
	 * toString方法
	 * String toString(数组)
	 * 返回指定数组内容的字符串拜师形式
	 * 输出:[2, 4, 6, 7, 9, 10, 20]
	 */
	System.out.println(Arrays.toString(arrCO));
    }
}
