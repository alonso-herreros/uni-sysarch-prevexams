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
        for (int i = 0; i < _____(1)______; i++) {
            f.preparePizzas(____(2)_______);
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
        for (int i = 0; i < _____(3)_______; i++) {
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
        for (int i = 0; i < _____(4)_____; i++) {
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

    private Semaphore semA = new Semaphore(__(5)___);
    private Semaphore semB = new Semaphore(__(6)___);
    private Semaphore semC = new Semaphore(__(7)___);
    private Semaphore semD = new Semaphore(__(8)___);

    private int nPizzas = 0;
    private int nServedCustomers = 0;
    private int nChargedTables = 0;
    private int nTablesToBeCharged = 0;

    public String toString() {
        return "[" + nPizzas + "][" + nServedCustomers + "][" + nTablesToBeCharged + "][" + nChargedTables + "]";
    }

    public void preparePizzas(int id) {
        try {semA.acquire(); } catch (Exception e) {}
        while (___(9)____ >= MAX_NUM_PIZZAS) {
            try { ______(10)______; } catch (Exception e) {}


            try { ______(11)______; } catch (Exception e) {}
            try { ______(12)______; } catch (Exception e) {}
        }

        nPizzas = nPizzas + 2;
        if ((nPizzas) / NUM_CLIENTS - (nPizzas - 2) / NUM_CLIENTS > 0)
            ________(13)_________++;

        System.out.println("Oven " + id + ": " + toString());
        semC.release();
        _______(14)________;
        semA.release();
    }

    public void chargeBill() {
        try { semA.acquire(); } catch (Exception e) {}
        while (_____(15)______ < 1) {
            try { ______(16)_______; } catch (Exception e) {}
            try { semD.acquire(); } catch (Exception e) {}
            try { ______(17)_______; } catch (Exception e) {}
        }

        nChargedTables = nChargedTables + 1;
        ______(18)________--;
        System.out.println("Cashier: " + toString() + " total cashed tables " + nChargedTables);
        _______(19)________;
        semA.release();
    }

    public void servePizzas() {
        try { semA.acquire(); } catch (Exception e) {}
        while ((____(20)_____ < NUM_CLIENTS)) {
            try { ____(21)________; } catch (Exception e) {}
            try { _____(22)________; } catch (Exception e) {}
            try { ______(23)_______; } catch (Exception e) {}
        }
        ____(24)_______ -= _____(25)_______;
        ______(26)_____ += ______(27)______;
        System.out.println("Waiter: " + toString() + " total served customers " + nServedCustomers);
        _______(28)_________;
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