package hq.master;

import hq.other.Stu;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.List;

public class File_io {
	static String path = "D:\\JavaLearning\\day1017_IO操作\\SMS_enhanced\\src\\hq\\master\\iofile.bin";
	static File datafile = new File(path);

/*
 * 这一片注释的想法是将这几个文件变量的初始化从原读写过程中剔除出来,
 * 以便可以将文件流的关闭操作也封装成一个函数以供调用,
 * 但调试有问题：关闭过程未完全拿出来
 */
	// public ObjectInputStream readcreat() {
	// try {
	// FileInputStream fis = new FileInputStream(datafile);
	// ObjectInputStream ois = new ObjectInputStream(fis);
	//
	// return ois;
	// } catch (FileNotFoundException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// } catch (IOException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	// return null;
	//
	// }
	//
	// public ObjectOutputStream writecreat() {
	// try {
	// FileOutputStream fos = new FileOutputStream(datafile);
	// ObjectOutputStream oos = new ObjectOutputStream(fos);
	//
	// return oos;
	// } catch (FileNotFoundException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// } catch (IOException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	// return null;
	// }

	public void write_data(List<Stu> list) {
		try {
			FileOutputStream fos = new FileOutputStream(datafile);
			ObjectOutputStream oos = new ObjectOutputStream(fos);

			oos.writeObject(list);

			oos.close();
			fos.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@SuppressWarnings("unchecked")
	public List<Stu> read_data() {
		List<Stu> list = null;
		try {
			FileInputStream fis = new FileInputStream(datafile);
			ObjectInputStream ois = new ObjectInputStream(fis);

			list = (List<Stu>) ois.readObject();

			ois.close();
			fis.close();

			// for (Stu student : list) {
			//
			// System.out.println(student.toString());
			//
			// }
			// return list;
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return list;
	}

	public void close_file() {

	}
}
