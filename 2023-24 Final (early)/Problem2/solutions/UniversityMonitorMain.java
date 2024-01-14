
import java.util.Random;

class UniversityMonitor {
	private int numInA, numInB, numInC, numInAB;
	
	public synchronized void roomAin(int identifier, int time) {
		if(time == 1) {
			while(numInAB >=40) {
				try{this.wait();}catch(Exception e) {}
			}
			numInA++;
			numInAB++;
			System.out.println("[ " + identifier + " ] A1 Cafeteria \t(total " + numInA + " students) \t...Ordering food...");
		} else {
			numInB--;
			numInA++;
			System.out.println("[ " + identifier + " ] A2 Cafeteria \t(total " + numInA + " students) \t...Exiting the Cafeteria...");
			this.notifyAll();
		}
		
	}

	public synchronized void roomBin(int identifier) {
		while(numInB >=30) {
			try{this.wait();}catch(Exception e) {}
		}
		numInB++;
		numInA--;
    	System.out.println("[ "+ identifier +" ] B Canteen \t(total " + numInB + " students) \t...Eating...");
	}

	public synchronized void roomCin(int identifier) {
		while(numInC >=20) {
			try{this.wait();}catch(Exception e) {}
		}
		numInAB--;
		numInA--;
		numInC++;
		System.out.println("[ " + identifier + " ] C Class         \t(total " + numInC + " students) \t...In class...");
		this.notifyAll();
	}

	public synchronized void roomCout() {
		numInC--;
		this.notifyAll();
	}
}

class StudentMonitor extends Thread {
    private int identifier;
    private UniversityMonitor m;
    private Random rnd = new Random();

    public StudentMonitor(int id, UniversityMonitor m) {
    	this.m = m;
        this.identifier = id;
    }

    public void run() {
        System.out.println("[ " + identifier + " ] In Leganes, waiting to enter");
        m.roomAin(identifier,1);
    	try{Thread.sleep(rnd.nextInt(2000));} catch (Exception e) {}
        m.roomBin(identifier);
    	try{Thread.sleep(rnd.nextInt(5000));} catch (Exception e) {}
        m.roomAin(2,identifier);
    	try{Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
        m.roomCin(identifier);
    	try{Thread.sleep(rnd.nextInt(3000));} catch (Exception e) {}
        m.roomCout();  	
        System.out.println("[ " + identifier + " ] Outside");
    }
}

public class UniversityMonitorMain {
    public static void main(String[] args) {
        StudentMonitor st;
        UniversityMonitor m = new UniversityMonitor();
        for (int i = 0; i < 150; i++) {
            st = new StudentMonitor(i, m);
            st.start();
        }
    }
}
