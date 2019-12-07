package test0512_1;

/**
 * 数组元素访问
 * @author dWX458270
 * 
 */
public class Run {
    public static void main(String[] args) {
	int list[] = new int[10];

	/**
	 * 普通的for循环遍历数组
	 */
	for (int k = 0; k < list.length; k++) {
	    // System.out.println(k);
	    list[k] = k;
	}

	/**
	 * 数组遍历的简易写法，输入fore按提示键自动弹出 这里的i代表list[n],也就是每一个数组元素的值，与上面的k的意义不同
	 */
	for (int i : list) {
	    /**
	     * 这里直接打印的就是每个数组元素的值
	     */
	    System.out.println(i);
	}
    }
}
