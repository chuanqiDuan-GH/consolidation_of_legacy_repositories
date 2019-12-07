package hq.practice;

import hq.span.Inherit_class;
//同包非子类和同包子类,访问权限相同,有三种:public、protect、默认
public class Run {
	public static void main(String[] args) {
		Attribute_Func_authority afa = new Attribute_Func_authority();
		// 实例afa和AFa类在同一个包下，所以可以调用除private修饰以外的其他所有属性和方法
		int i = Attribute_Func_authority.a;
		Inherit_class ic = new Inherit_class();
		

	}
}
