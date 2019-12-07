package test0506_2;


/*
 * Java基础教程第四章习题-2：
 * 创建 Rodent（啮齿动物）：Mouse（老鼠），Gerbil（鼹鼠），
 * Hamster（大颊鼠）等的一个继承分级结构。在基础类中，提供适用于所有 Rodent 的方法，
 * 并在衍生类 中覆盖它们，从而根据不同类型的 Rodent 采取不同的行动。
 * 创建一个 Rodent 数组，在 其中填充不同类型的 Rodent，然后调用自己的基础类方法，看看会有什么情况发生。
 */
public class Run {

	public static void main(String[] args){
		
		Mouse mm = new Mouse();
		Gerbil gg = new Gerbil();
		
		mm.name();
		gg.name();
		
		Rodent rr[] = new Rodent[2];
		rr[0] = mm;
		rr[1] = gg;
		
		rr[0].name();
		rr[1].name();
	}
}
