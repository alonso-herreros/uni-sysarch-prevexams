import java.util.concurrent.Semaphore;

public class P1
    {
    public static Semaphore semaforo = new Semaphore(0);
    public static int c = 0;

    public static void main(String[] args)
        {
        T[] ts = new T[3];
        for (int i=0; i<3; i++)
            ts[i] = new T();
        for (int i=0; i<3; i++)
            ts[i].start();

        semaforo.release();

        for (int i=0; i<3; i++)
            {
            try {ts[i].join();}
            catch(Exception e){System.exit(666);}
            }

        System.out.println(c);
        }
    }

class T extends Thread
    {
    public void run()
        {
        try {P1.semaforo.acquire();}
        catch(Exception e){System.exit(666);}

        P1.c++;
        P1.semaforo.release();
        }
    }

