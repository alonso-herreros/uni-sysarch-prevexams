import java.util.Random;
import java.util.concurrent.Semaphore;

public class Q11Phi extends Thread {
	private Semaphore a,b,c,d,e,f;
	public static int counter;
	private int id;
	private Random rd;
	public Q11Phi(Semaphore a, Semaphore b, Semaphore c, Semaphore d, Semaphore e, Semaphore f) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		id= ++counter;
		rd = new Random();
	}

	public void run() {
		if(id == 1) {
			while(true) {
				try {f.acquire();}catch(Exception e) {}
				try{a.acquire();}catch(Exception e) {}
				try{Thread.sleep(100);}catch(Exception e) {}
				try{b.acquire();}catch(Exception e) {}
				f.release();
				System.out.println("Thread 1 is executing");
				try{Thread.sleep(rd.nextInt(1000));}catch(Exception e) {}
				a.release();
				b.release();
			}
		} else if(id == 2){
			while(true) {
				try {f.acquire();}catch(Exception e) {}
				try{b.acquire();}catch(Exception e) {}
				try{Thread.sleep(100);}catch(Exception e) {}
				try{c.acquire();}catch(Exception e) {}
				f.release();
				System.out.println("Thread 2 is executing");
				try{Thread.sleep(rd.nextInt(1000));}catch(Exception e) {}
				b.release();
				c.release();
			}
		} else if(id == 3) {
			while(true) {
				try {f.acquire();}catch(Exception e) {}
				try{c.acquire();}catch(Exception e) {}
				try{Thread.sleep(100);}catch(Exception e) {}
				try{d.acquire();}catch(Exception e) {}
				f.release();
				System.out.println("Thread 3 is executing");
				try{Thread.sleep(rd.nextInt(1000));}catch(Exception e) {}
				c.release();
				d.release();
			}
		} else if(id == 4) {
			while(true) {
				try {f.acquire();}catch(Exception e) {}
				try{d.acquire();}catch(Exception e) {}
				try{Thread.sleep(100);}catch(Exception e) {}
				try{e.acquire();}catch(Exception e) {}
				f.release();
				System.out.println("Thread 4 is executing");
				try{Thread.sleep(rd.nextInt(1000));}catch(Exception e) {}
				d.release();
				e.release();
			}
		} else {
			while(true) {
				try {f.acquire();}catch(Exception e) {}
				try{e.acquire();}catch(Exception e) {}
				try{Thread.sleep(100);}catch(Exception e) {}
				try{a.acquire();}catch(Exception e) {}
				f.release();
				System.out.println("Thread 5 is executing");
				try{Thread.sleep(rd.nextInt(1000));}catch(Exception e) {}
				e.release();
				a.release();
			}
		}
	}
	public static void main(String[] args) {
		Semaphore a = new Semaphore(1);
		Semaphore b = new Semaphore(1);
		Semaphore c = new Semaphore(1);
		Semaphore d = new Semaphore(1);
		Semaphore e = new Semaphore(1);
		Semaphore f = new Semaphore(1,true);
		Q11Phi q1 = new Q11Phi(a,b,c,d,e,f);
		Q11Phi q2 = new Q11Phi(a,b,c,d,e,f);
		Q11Phi q3 = new Q11Phi(a,b,c,d,e,f);
		Q11Phi q4 = new Q11Phi(a,b,c,d,e,f);
		Q11Phi q5 = new Q11Phi(a,b,c,d,e,f);
		q1.start();
		q2.start();
		q3.start();
		q4.start();
		q5.start();
	}

}
