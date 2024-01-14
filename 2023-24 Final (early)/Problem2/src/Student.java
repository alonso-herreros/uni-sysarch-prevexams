import java.util.*;
import java.util.concurrent.*;

class Student extends Thread {
    private int identifier;
    private Semaphore rASem, rBSem, rCSem;
    private static int numInA, numInB, numInC;

    private Semaphore mutexA, mutexB, mutexC;
    private Random rnd = new Random();

    Student(int id, Semaphore rASem, Semaphore rBSem, Semaphore rCSem,
           Semaphore mutexA, Semaphore mutexB, Semaphore mutexC) {
        this.rASem = rASem;
        this.rBSem = rBSem;
        this.rCSem = rCSem;
        this.mutexA = mutexA;
        this.mutexB = mutexB;
        this.mutexC = mutexC;
        this.identifier = id;
    }

    private void roomAin(int time) {
        String room = "A" + time + " Cafeteria";
        String activity = time==1? "Ordering food" : "Exiting the Cafeteria";

        if (time == 1)
            try { rASem.acquire(); } catch (InterruptedException e) {}
        else {
            try { mutexB.acquire(); } catch (InterruptedException e) {}
            rBSem.release();
            numInB--;
            mutexB.release();
        }

        try { mutexA.acquire(); } catch (InterruptedException e) {}

        numInA++;
        System.out.printf("[ %2d ] %-17s (total %2d students)     ...%s...\n",
                identifier, room, numInA, activity);

        mutexA.release();
    }

    private void roomBin() {
        String room = "B Canteen";
        String activity = "Eating";

        try { rBSem.acquire(); } catch (InterruptedException e) {}

        try {
            mutexA.acquire();
            mutexB.acquire();
        } catch (InterruptedException e) {}

        numInA--;
        numInB++;
        System.out.printf("[ %2d ] %-17s (total %2d students)     ...%s...\n",
                identifier, room, numInB, activity);

        mutexB.release();
        mutexA.release();
    }

    private void roomCin() {
        String room = "C class";
        String activity = "In class";

        try { rCSem.acquire(); } catch (InterruptedException e) {}

        try {
            mutexA.acquire();
            mutexC.acquire();
        } catch (InterruptedException e) {}

        rASem.release();
        numInA--;
        numInC++;

        System.out.printf("[ %2d ] %-17s (total %2d students)     ...%s...\n",
                identifier, room, numInC, activity);

        mutexC.release();
        mutexA.release();
    }

    private void roomCout() {
        try { mutexC.acquire(); } catch (InterruptedException e) {}
        rCSem.release();
        numInC--;
        mutexC.release();
    }

    public void run() {
        System.out.println("[ " + identifier + " ] In Leganes, waiting to enter");
        roomAin(1); // Cafeteria
        try{Thread.sleep(rnd.nextInt(2000));} catch (Exception e) {}
        roomBin(); // Canteen
        try{Thread.sleep(rnd.nextInt(5000));} catch (Exception e) {}
        roomAin(2); // Cafeteria 2
        try{Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
        roomCin(); // Class
        try{Thread.sleep(rnd.nextInt(3000));} catch (Exception e) {}
        roomCout();
        System.out.println("[ " + identifier + " ] Outside");
    }
}