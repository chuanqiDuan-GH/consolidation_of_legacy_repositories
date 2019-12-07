package test0506_3;

public class MyXYZ extends MyPoint{
	private int x;
	private int y;
	private int z;
	
	public MyXYZ(){
		x = 0;
		y = 0;
		z = 0;
	}
	
	public MyXYZ(int cx, int cy, int cz){
		x = cx;
		y = cy;
		z = cz;
	}
	
	public int getX(){
		return x;
	}
	
	public int getY(){
		return y;
	}
	
	public int getZ(){
		return z;
	}
	
	public String ToString(){
		return "(" + getX() + "," + getY() + "," + getZ() + ")";
	}
}
