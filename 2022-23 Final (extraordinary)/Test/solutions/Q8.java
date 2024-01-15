package prueba;

import java.util.concurrent.Semaphore;

public class Q8 extends Thread {
	private String profile;
	private int ident;
	private static Semaphore mutex = new Semaphore(1);
	private static Semaphore eat = new Semaphore(0);
	private static int dishes_available;
	
	public Q8(String profile, int ident) {
		this.profile = profile;
		this.ident=ident;
	}
	
	public void run() {
		if(profile.equals("waiter")) { // Camarero
			for(int i=0;i<10;i++) {
				try {mutex.acquire();} catch (InterruptedException e) {}
				dishes_available++;
				System.out.println("A new dish is available. Total: " + dishes_available);
				mutex.release();
				eat.release();
			}
			System.out.println("Finished waiter " + ident);
		}
		if(profile.equals("guest")) { // Comensal/invitado
			  int eaten_times = 0;
				while(eaten_times<10) {
					try {mutex.acquire();} catch (InterruptedException e) {}
					if(dishes_available > 0) {
						dishes_available--;
						eaten_times++;
						System.out.println("A dish has been eaten by guest " + ident + ". Total: " + dishes_available + " | Eaten times: " + eaten_times);
						mutex.release();
					} else {
						mutex.release();
						System.out.println("ACQUIRE###### by " + ident);
						try {eat.acquire();} catch (InterruptedException e) {}
					}
			  }
			  System.out.println("Finished guest " + ident);
		}
	}
	
	public static void main(String args[]) {
		Q8[] waiters = new Q8[10];
		Q8[] guests = new Q8[10];
		for(int i=0; i<10;i++) {
			waiters[i] = new Q8("waiter",i);
			guests[i] = new Q8("guest",i);
			guests[i].start();
			waiters[i].start();
		}
	}
}