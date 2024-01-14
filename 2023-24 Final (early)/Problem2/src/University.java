public class University {
    public static void main(String[] args) {
        Student st;
        Semaphore rASem, rBSem, rCSem;
        ______________ mutexA, mutexB, mutexC;

        rASem = new Semaphore(__, true); //A Cafeteria
        rBSem = new Semaphore(__, true); //B Canteen
        rCSem = new Semaphore(__, true); //C Class

        mutexA = new Semaphore(__);
        mutexB = new Semaphore(__);
        mutexC = new Semaphore(__);

        for (int i = 0; i < __; i++) {
            st = new _________(i, rASem, rBSem, rCSem, mutexA, mutexB, mutexC);
            st._________();
        }
    }
}