package test0507_2;

public class Run {
    public static void main(String[] args){
	Man mm = new Man();
	Person pp = new Person();

	Person pp0 = (Person)new Man();
	Person pp1 = (Person)mm;
    }
}
