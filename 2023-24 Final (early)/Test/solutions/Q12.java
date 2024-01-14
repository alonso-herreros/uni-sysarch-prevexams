
class MonitorQ12 {
	private int counter;
	public synchronized void increase() { counter++; System.out.println(counter);}
}

public class Q12 extends Thread {
	private MonitorQ12 m;
	public Q12(MonitorQ12 m) { this.m=m;}
	public void run() {	
		m.increase();
	}

	public static void main(String[] args) {
		MonitorQ12 m = new MonitorQ12();
		Q12 q1 = new Q12(m);
		Q12 q2 = new Q12(m);
		q1.start();
		q2.start();
	}
}
