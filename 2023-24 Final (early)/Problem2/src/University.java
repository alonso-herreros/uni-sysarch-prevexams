import java.util.concurrent.*;

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

        for (int i = 0; i < 100; i++) {
            st = new Student(i, rASem, rBSem, rCSem, mutexA, mutexB, mutexC);
            st.start();
        }
    }
}