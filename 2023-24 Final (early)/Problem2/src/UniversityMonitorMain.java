import java.util.Random;

class UniversityMonitor {
    final static int caps[] = {40, 30, 20};
    int loads[];
    int occu[];

    public UniversityMonitor() {
        this.loads = new int[]{0, 0, 0};
        this.occu = new int[]{0, 0, 0};
    }

    public synchronized int enter(String room) throws InterruptedException {
        return enter(room, true);
    }
    public synchronized int enter(String room, boolean occupy) throws InterruptedException {
        int i = room.charAt(0)-'A';
        if (occupy) {
            while (occu[i] >= caps[i]) { wait(); }
            occu[i]++;
        }
        return ++loads[i];
    }

    public synchronized int leave(String room) {
        return leave(room, true);
    }
    public synchronized int leave(String room, boolean deoccu) {
        int i = room.charAt(0)-'A';
        if (deoccu) {
            occu[i]--;
            notifyAll();
        }
        return --loads[i];
    }

    public synchronized int move(String from, String to) throws InterruptedException {
        return move(from, to, true, true);
    }
    public synchronized int move(String from, String to, boolean occupy, boolean deoccu)
        throws InterruptedException
    {
        int load = enter(to, occupy);
        leave(from, deoccu);
        return load;
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

    public synchronized void printRoom(String room, int load, String activity) {
        System.out.printf("[ %2d ] %-16s (total %-2d students)     ...%s...\n",
                identifier, room, load, activity);
    }

    public void run() {
        try {
            System.out.println("[ " + identifier + " ] In Leganes, waiting to enter");

            printRoom("A1 Cafeteria", m.enter("A"), "Ordering food");
            Thread.sleep(rnd.nextInt(2000));

            printRoom("B Canteen", m.move("A", "B", true, false), "Eating");
            Thread.sleep(rnd.nextInt(5000));

            printRoom("A2 Cafeteria", m.move("B", "A", false, true), "Exiting the Cafeteria");
            Thread.sleep(rnd.nextInt(1000));

            printRoom("C Class", m.move("A", "C"), "In class");
            Thread.sleep(rnd.nextInt(3000));
        } catch (InterruptedException e) {}

        m.leave("C");
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