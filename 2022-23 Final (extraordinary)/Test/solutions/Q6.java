package prueba;


class T1 extends Thread{
	public void run() {
		for(int i=0; i<10; i++)
			System.out.println("tic");			
	}
}

class T2 implements Runnable{
	public void run() {
		for(int i=0; i<10; i++)
			System.out.println("toc");
	}
}

public class Q6 {
	public static void main(String[] args) {
		T1 t1 = new T1();
		T2 t2 = new T2();
		t1.start();
		Thread t3 = new Thread(t2);
		t3.start();
		
	}
}


