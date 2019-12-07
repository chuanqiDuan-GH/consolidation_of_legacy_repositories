package hq.span;

import hq.practice.Attribute_Func_authority;
//不同包子类内,访问权限:public、protected
public class Inherit_class extends Attribute_Func_authority{
public static void main(String[] args) {
	Inherit_class ic = new Inherit_class();
	//ic是AFa的继承类Ic实例，但子类Ic和父类AFa并不在一个包内，所以在跨包的子类中，只能看到public和protected的内容
}
}
