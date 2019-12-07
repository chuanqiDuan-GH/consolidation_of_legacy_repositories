package test0507_1;

public class Mystery {

    /*
     * String未初始化,默认为null
     * 所以mm.go调用后打印为null
     */
    String s;
    static boolean flag;
    public static void main(String[] args){
	Mystery mm = new Mystery();
    }	
    /*
     *可以定义和类名相同的非构造函数(报警告),但一般不要这么写
     */
    void Mystery(){
	s = "constructor构造函数";
    }

    void go() {
	System.out.println(s);
    }
}
