package test0508_2;


/**
 * 设计个 Circle 类，其属性为圆心点（类型为前面设计的类 MyPoint）和半径,
 * 并为 此类编写以下三个方法:
 * 一是计算圆面积的 calArea()方法;
 * 二是计算周长的 calLength();
 * 三是 boolean inCircle(MyPoint mp)方法，
 * 功能是测试作为参数的某个点是否在当前对 象圆内（圆内，包括圆上返回 true；在圆外，返回 false）。
 * @author cqd
 *
 */
public class Circle {
    private Point center;
    private double radius;

    public Circle(){
	center = new Point();
	center.SetX(1);
	center.SetY(1); 
	radius = 5.0;
    }

    public double calArea(int cradius){

	double area = cradius *cradius * 3.14;
	return area;
    }

    public double calLength(int cradius){
	double length = 2 * 3.14 *cradius;
	return length;
    }

    public boolean inCircle(Point pp){

	int x1 = pp.GetX();
	int y1 = pp.GetY();
	int x2 = center.GetX();
	int y2 = center.GetY();

	if(radius > Math.sqrt((Math.abs(x1-x2) * (Math.abs(x1-x2)) + (Math.abs(y1-y2) * Math.abs(y1-y2)))))
	    return true;
	else
	    return false;
    }

    public static void main(String[] args){
	Circle cc = new Circle();
	Point pp = new Point();
	pp.SetX(1);
	pp.SetY(6);

	System.out.println(cc.inCircle(pp));
    }
}
