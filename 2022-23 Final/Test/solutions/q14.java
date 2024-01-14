public class q14
    {
    public static int c = 0;

    public static void main(String[] args)
        {
        T[] ts = new T[3];
        for (int i=0; i<3; i++)
            ts[i] = new T();
        for (int i=0; i<3; i++)
            ts[i].start();
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
        synchronized(q14.c) {q14.c++;}

        try{Thread.sleep(100);}
        catch(Exception e){System.exit(666);}
 
        synchronized(q14.c) {q14.c++;}
        }
    }

