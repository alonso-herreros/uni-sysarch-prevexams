package prueba;

public class Q7 extends Thread {
	private String profile;
	private static int dishes_available;
	
	public Q7(String profile) {
		this.profile = profile;
	}
	
	public void run() {
		if(profile.equals("waiter")) { // Camarero
			synchronized(Q7.class) {
			dishes_available++;
			System.out.println("A new dish is available. Total: " + dishes_available);
			Q7.class.notify();
			}
		}
		if(profile.equals("guest")) { // Comensal/invitado
			synchronized(Q7.class) {
				while(dishes_available==0) {
					System.out.println("Wait");
					try {Q7.class.wait();} catch (InterruptedException e) {}
				}
				dishes_available--;
				System.out.println("A dish has been eaten. Total: " + dishes_available);
			}
		}
	}
	
	public static void main(String args[]) {
		Q7[] waiters = new Q7[10];
		Q7[] guests = new Q7[10];
		for(int i=0; i<10;i++) {
			waiters[i] = new Q7("waiter");
			guests[i] = new Q7("guest");
			guests[i].start();
			waiters[i].start();
		}
	}
}
