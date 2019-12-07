package hq.practice;

public class Run {
	public static void main(String[] args) {
	
		int sum = 0;
		float avg = 0L;
		
		//对象数组的定义类似普通数组的定义，只要类比数组的定义将数组的类型换成对象类名，用new语法创建新的对象
		Hq_stu[] stu_class =new Hq_stu[5];
		
		stu_class[0] = new Hq_stu("alpha", 100);
		stu_class[1] = new Hq_stu("beta", 90);
		stu_class[2] = new Hq_stu("gamma", 95);
		stu_class[3] = new Hq_stu("delta", 90);
		stu_class[4] = new Hq_stu("epsilon", 92);
		
		for (Hq_stu hq_stu : stu_class) {
			sum = sum + hq_stu.score;
		}
		avg = sum / stu_class.length;
		System.out.println(avg);
	
	}
}
