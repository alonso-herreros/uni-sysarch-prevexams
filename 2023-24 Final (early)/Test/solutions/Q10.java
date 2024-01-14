
public class Q10 extends Thread {
	private Integer i;
	public static int counter;
	public Q10(Integer i) { this.i = i;}
	public void run() {	synchronized(i) {counter++; System.out.println(counter);}}

	public static void main(String[] args) {
		Integer i = new Integer(5);
		Q10 q1 = new Q10(i);
		Q10 q2 = new Q10(i);
		q1.start();
		q2.start();

	}

}
