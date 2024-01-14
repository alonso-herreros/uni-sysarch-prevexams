import java.util.Random;

class UniversityMonitor {
    // COMPLETE

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
        HIDDEN
        try{Thread.sleep(rnd.nextInt(2000));} catch (Exception e) {}
        HIDDEN
        try{Thread.sleep(rnd.nextInt(HIDDEN));} catch (Exception e) {}
        HIDDEN
        try{Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
        HIDDEN
        try{Thread.sleep(rnd.nextInt(HIDDEN));} catch (Exception e) {}
        HIDDEN
        System.out.println("[ " + identifier + " ] Outside");
    }
}

public class UniversityMonitorMain {
    public static void main(String[] args) {
        StudentMonitor st;
        UniversityMonitor m = new UniversityMonitor();
        for (int i = 0; i < 150; i++) {
            st = new HIDDEN(i, m);
            st.HIDDEN();
        }
    }
}