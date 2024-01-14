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
        for (int i = 0; i < ___________/*(1)*/; i++) {
            f.preparePizzas(___________/*(2)*/);
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
        for (int i = 0; i < ____________/*(3)*/; i++) {
            f.chargeBill();
            try { Thread.sleep(75); } catch (Exception e) {}
        }
    }
}

class Waiter extends Thread {
    PizzaSem f;

    public Waiter(PizzaSem f) {
        this.f = f;
    }

    public void run() {
        for (int i = 0; i < __________/*(4)*/; i++) {
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

    private Semaphore semA = new Semaphore(_____/*(5)*/);
    private Semaphore semB = new Semaphore(_____/*(6)*/);
    private Semaphore semC = new Semaphore(_____/*(7)*/);
    private Semaphore semD = new Semaphore(_____/*(8)*/);

    private int nPizzas = 0;
    private int nServedCustomers = 0;
    private int nChargedTables = 0;
    private int nTablesToBeCharged = 0;

    public String toString() {
        return "[" + nPizzas + "][" + nServedCustomers + "][" + nTablesToBeCharged + "][" + nChargedTables + "]";
    }

    public void preparePizzas(int id) {
        try {semA.acquire(); } catch (Exception e) {}
        while (_______/*(9)*/ >= MAX_NUM_PIZZAS) {
            try { ____________/*(10)*/; } catch (Exception e) {}
            try { ____________/*(11)*/; } catch (Exception e) {}
            try { ____________/*(12)*/; } catch (Exception e) {}
        }

        nPizzas = nPizzas + 2;
        if ((nPizzas) / NUM_CLIENTS - (nPizzas - 2) / NUM_CLIENTS > 0)
            _________________/*(13)*/++;

        System.out.println("Oven " + id + ": " + toString());
        semC.release();
        _______________/*(14)*/;
        semA.release();
    }

    public void chargeBill() {
        try { semA.acquire(); } catch (Exception e) {}
        while (___________/*(15)*/ < 1) {
            try { _____________/*(16)*/; } catch (Exception e) {}
            try { semD.acquire(); } catch (Exception e) {}
            try { _____________/*(17)*/; } catch (Exception e) {}
        }

        nChargedTables = nChargedTables + 1;
        ______________/*(18)*/--;
        System.out.println("Cashier: " + toString() + " total cashed tables " + nChargedTables);
        _______________/*(19)*/;
        semA.release();
    }

    public void servePizzas() {
        try { semA.acquire(); } catch (Exception e) {}
        while ((_________/*(20)*/ < NUM_CLIENTS)) {
            try { ____________/*(21)*/; } catch (Exception e) {}
            try { _____________/*(22)*/; } catch (Exception e) {}
            try { _____________/*(23)*/; } catch (Exception e) {}
        }
        ___________/*(24)*/ -= ____________/*(25)*/;
        ___________/*(26)*/ += ____________/*(27)*/;
        System.out.println("Waiter: " + toString() + " total served customers " + nServedCustomers);
        ________________/*(28)*/;
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