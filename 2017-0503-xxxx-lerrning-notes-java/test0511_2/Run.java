package test0511_2;


/**
 * 数组的初始化
 * @author cqd
 *
 */
public class Run {
    public static void main(String[] args){
	String names[] = {
	    new String(),
	    new String(),	//最后这个逗号加不加都可以
	};

	names[0] = "Goergianna";
	names[1] = "Simon";

	System.out.println(names[0]);
    }
}

