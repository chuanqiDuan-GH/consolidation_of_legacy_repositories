package hq.practice;

//接口类可以理解为一个抽象方法的集合,抽象类中也可以全部定义成抽象方法,但是无法实现多继承
//抽象方法只能定义在抽象类中
//接口类中没有方法的实现，接口类中的抽象方法全部在对应接口类的实现类中去实现
public interface I_Human {

	//接口类内的方法不需要实现体 Abstract methods do not specify a body
	//public abstract void action(){};	//错误写法
	
	//接口类内的的方法默认是abstract(抽象方法),而且默认的访问级别为public
	//所以在接口类对应的实现类中的方法访问级别必须定义为public，不然会报错
	public abstract void action();
	
	void thought();
	
	
}
