package prueba;

import java.util.concurrent.Semaphore;

class Writer extends Thread {
	private int id;
	private static int currentBook;
	private static int numReaders;
	private Semaphore writerSemaphore;
	private Semaphore[] bookSemaphore;

	public Writer(int id, Semaphore writerSemaphore, Semaphore[] bookSemaphore, int nReaders) {
    	this.id = id;
    	this.writerSemaphore = writerSemaphore;
    	this.bookSemaphore = bookSemaphore;
    	numReaders = nReaders;
	}

	public void run() {
    	for (int i = 0; i < 5; i++) { // Each Writer writes 5 books
        	try {
            	writerSemaphore.acquire();
            	System.out.println("Writer " + id + " is writing book " + currentBook);
            	Thread.sleep(200);
            	bookSemaphore[currentBook].release(numReaders);
            	currentBook++;
            	writerSemaphore.release();
        	} catch (InterruptedException e) {
            	e.printStackTrace();
        	}
    	}
	}
}

class Reader extends Thread {
	private Semaphore readerSemaphore;
	private Semaphore[] bookSemaphore;
	private int id;
	private int numBooks;

	public Reader(Semaphore readerSemaphore, Semaphore[] bookSemaphore, int id, int numBooks) {
    	this.readerSemaphore = readerSemaphore;
    	this.bookSemaphore = bookSemaphore;
    	this.id = id;
    	this.numBooks = numBooks;
	}

	public void run() {
    	for(int i=0; i<numBooks; i++) { // Finish after reading all the books
        	try {
        		readerSemaphore.acquire();
        		bookSemaphore[i].acquire();
        		System.out.println("Reader " + id + " is reading book " + i);
            	Thread.sleep(100);
        		bookSemaphore[i].release();
        		readerSemaphore.release();
        	} catch (InterruptedException e) {
            	e.printStackTrace();
        	}
    	}
	}
}

class Library {

	public static void main(String[] args) {
		int nWriters= 3;
		int numBooks = 5*nWriters;
		int numReaders = 10;
		Semaphore writerSemaphore = new Semaphore(1, true); // Only 1 writer can write at a time
		Semaphore[] bookSemaphore = new Semaphore[numBooks];
		for(int i=0; i<numBooks;i++) { bookSemaphore[i] = new Semaphore(0);}
		Semaphore readerSemaphore =  new Semaphore(3, true); 
		
    	System.out.println("Starting library");
    	// Create and start writer threads
    	for (int i = 0; i < nWriters; i++) {
        	Writer writer = new Writer(i, writerSemaphore, bookSemaphore, numReaders );
        	writer.start();
    	}

    	// Create and start reader threads
    	for (int i = 0; i < numReaders; i++) {
        	Reader reader = new Reader(readerSemaphore, bookSemaphore, i, numBooks);
        	reader.start();
    	}
	}
}


