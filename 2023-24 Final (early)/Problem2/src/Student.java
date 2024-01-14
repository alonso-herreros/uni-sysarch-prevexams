class Student extends Thread {
    private int identifier;
    private Semaphore rASem, rBSem, rCSem;
    private ______________ numInA, numInB, numInC;

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

    private void roomAin(int time){ //Section 2.3 }
    private void roomBin() { // Section 2.3 }
    private void roomCin() { // Section 2.3 }
    private void roomCout() { // Section 2.3 }

    public void run() {
        System.out.println("[ " + identifier + " ] In Leganes, waiting to enter");
        ______________;
        try{Thread.sleep(rnd.nextInt(2000));} catch (Exception e) {}
        ______________;
        try{Thread.sleep(rnd.nextInt(_____));} catch (Exception e) {}
        ______________;
        try{Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
        ______________;
        try{Thread.sleep(rnd.nextInt(_____));} catch (Exception e) {}
        ______________;
        System.out.println("[ " + identifier + " ] Outside");
    }
}