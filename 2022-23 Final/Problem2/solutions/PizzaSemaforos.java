import java.util.concurrent.Semaphore;

class Oven extends Thread {
	int ident;
	PizzaSem f;

	public Oven(int id, PizzaSem f) {
		this.ident = id;
		this.f = f;
	}

	public void run() {
		int numPizzas = f.nTables * 5;
		int pizzas = numPizzas / 6;
		for (int i = 0; i < pizzas; i++) {
			f.preparePizzas(ident);
			try { Thread.sleep(200); } catch (Exception e) {
			}
		}
	}
}

class Cashier extends Thread {
	PizzaSem f;

	public Cashier(PizzaSem f) {
		this.f = f;
	}

	public void run() {
		for (int i = 0; i < f.nTables; i++) {
			f.chargeBill();
			try { Thread.sleep(75);	} catch (Exception e) {}
		}
	}
}

class Waiter extends Thread {
	PizzaSem f;

	public Waiter(PizzaSem f) {
		this.f = f;
	}

	public void run() {
		for (int i = 0; i < f.nTables; i++) {
			f.servePizzas();
			try { Thread.sleep(100); } catch (Exception e) {}
		}
	}
}

class PizzaSem {
	public static final int MAX_NUM_PIZZAS = 6;
	public static final int NUM_CLIENTS = 5;
	public int nTables;

	public PizzaSem(int nTables) {
		this.nTables = nTables;
	}

	private Semaphore semA = new Semaphore(1);
	private Semaphore semB = new Semaphore(0);
	private Semaphore semC = new Semaphore(0);
	private Semaphore semD = new Semaphore(0);

	private int nPizzas = 0;
	private int nServedCustomers = 0;
	private int nChargedTables = 0;
	private int nTablesToBeCharged = 0;

	public String toString() {
		return "[" + nPizzas + "][" + nServedCustomers + "][" + nTablesToBeCharged + "][" + nChargedTables + "]";
	}

	public void preparePizzas(int id) {
		try {semA.acquire(); } catch (Exception e) {}
		while (nPizzas >= MAX_NUM_PIZZAS) {
			try { semA.release(); } catch (Exception e) {}
			try { semB.acquire(); } catch (Exception e) {}
			try { semA.acquire(); } catch (Exception e) {}
		}

		nPizzas = nPizzas + 2;
		if ((nPizzas) / NUM_CLIENTS - (nPizzas - 2) / NUM_CLIENTS > 0)
			nTablesToBeCharged++;
		
		System.out.println("Oven " + id + ": " + toString());
		semC.release();
		semD.release();
		semA.release();
	}

	public void chargeBill() {
		try { semA.acquire(); } catch (Exception e) {}
		while (nTablesToBeCharged < 1) {
			try { semA.release(); } catch (Exception e) {}
			try { semD.acquire(); } catch (Exception e) {}
			try { semA.acquire(); } catch (Exception e) {}
		}

		nChargedTables = nChargedTables + 1;
		nTablesToBeCharged--;
		System.out.println("Cashier: " + toString() + " total cashed tables " + nChargedTables);
		semB.release();
		semA.release();
	}

	public void servePizzas() {
		try { semA.acquire(); } catch (Exception e) {}
		while ((nPizzas < NUM_CLIENTS)) {
			try { semA.release(); } catch (Exception e) {}
			try { semC.acquire(); } catch (Exception e) {}
			try { semA.acquire(); } catch (Exception e) {}
		}
		nPizzas -= NUM_CLIENTS;
		nServedCustomers += NUM_CLIENTS;
		System.out.println("Waiter: " + toString() + " total served customers " + nServedCustomers);
		semB.release();
		semA.release();
	}
}

public class PizzaSemaforos {
	public static void main(String args[]) {
		int nMesas = 6;
		PizzaSem f = new PizzaSem(nMesas);
		for (int i = 0; i < 3; i++) {
			new Oven(i, f).start();
		}
		new Cashier(f).start();
		new Waiter(f).start();
	}
}