import java.util.Random;
import java.util.concurrent.Semaphore;

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
		if (time == 1) {
			try {
				rASem.acquire();
			} catch (InterruptedException e) {
			} // //Threads acquire permits using the acquire() method. If there are available
				// permits, the thread proceeds; otherwise, it waits.
		}

		try {
			mutexA.acquire();
		} catch (InterruptedException e) {
		} // //To ensure mutual exclusion, a semaphore is often used in conjunction with a
			// mutex semaphore. The mutex semaphore protects critical sections where shared
			// variables are accessed or modified.
		numInA++;
		mutexA.release(); //

		if (time == 2) {
			try {
				mutexB.acquire();
			} catch (InterruptedException e) {
			}
			numInB--;
			mutexB.release();
			rBSem.release();
		}

		try {
			mutexA.acquire();
		} catch (InterruptedException e) {
		}
		if (time == 1) {
			System.out.println(
					"[ " + identifier + " ] A1 Cafeteria \t(total " + numInA + " students) \t...Ordering food...");
		}
		if (time == 2) {
			System.out.println("[ " + identifier + " ] A2 Cafeteria \t(total " + numInA
					+ " students) \t...Exiting the Cafeteria...");
		}
		mutexA.release();
	}

    
    private void roomBin() {
    	try {rBSem.acquire();} catch(InterruptedException e) {}	 
    	try {mutexB.acquire();} catch(InterruptedException e) {} 
    	try {mutexA.acquire();} catch(InterruptedException e) {} 
    	numInB++; 
    	numInA--; 
    	System.out.println("[ "+ identifier +" ] B Canteen \t(total " + numInB + " students) \t...Eating..."); 
    	mutexB.release(); 
    	mutexA.release(); 
    	//rASem.release();	//Only in roomCin You cannot release it until you leave room 40 for the second time. 
    	//Otherwise, there will be a deadlock
    }

    private void roomCin() {
	    try {rCSem.acquire();} catch(InterruptedException e) {}	 
	    try {mutexC.acquire();} catch(InterruptedException e) {}
	    try {mutexA.acquire();} catch(InterruptedException e) {}
		numInC++;
		numInA--;
        System.out.println("[ " + identifier + " ] C Class         \t(total " + numInC + " students) \t...In class...");
		mutexC.release();
		mutexA.release();
		rASem.release();     
    }

    private void roomCout() {
        try {mutexC.acquire();} catch(InterruptedException e) {}  
        numInC--;
        mutexC.release(); 
        rCSem.release(); 
    }

    public void run() {
        System.out.println("[ " + identifier + " ] In Leganes, waiting to enter");
        roomAin(1);
    	try{Thread.sleep(rnd.nextInt(2000));} catch (Exception e) {}
        roomBin();
    	try{Thread.sleep(rnd.nextInt(5000));} catch (Exception e) {}
        roomAin(2);
    	try{Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
        roomCin();
    	try{Thread.sleep(rnd.nextInt(3000));} catch (Exception e) {}
        roomCout();  	
        System.out.println("[ " + identifier + " ] Outside");
    }
}

public class University {
    public static void main(String[] args) {
        Student st;
        Semaphore rASem, rBSem, rCSem;
        Semaphore mutexA, mutexB, mutexC;

        rASem = new Semaphore(40, true); //A Cafeteria
        rBSem = new Semaphore(30, true); //B Canteen
        rCSem = new Semaphore(20, true); //C Class

        mutexA = new Semaphore(1);
        mutexB = new Semaphore(1);
        mutexC = new Semaphore(1);

        for (int i = 0; i < 150; i++) {
            st = new Student(i, rASem, rBSem, rCSem, mutexA, mutexB, mutexC);
            st.start();
        }
    }
}

