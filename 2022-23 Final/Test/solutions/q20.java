public class P1
    {
    public static M m = new M();
    public static void main(String[] args)
        {
        T[] ts = new T[4];
        for (int i=0; i<4; i++)
            ts[i] = new T(i);

        for (int i=0; i<4; i++)
            ts[i].start();

        for (int i=0; i<4; i++)
            {
            try {ts[i].join();}
            catch(Exception e){System.exit(666);}
            }
        System.out.println("");
        }
    }

class T extends Thread
    {
    int n;
    public T(int n)
        {
        this.n = n;
        }
    public void run()
        {
        P1.m.Get_in(n);
        System.out.print(n);
        P1.m.Get_out(n);
        }
    }

class M
    {
    private int n;

    public synchronized void Get_in(int i) 
        {    
        int k;
   
        while (true)
            {
            k = 2*(n%2) - (n/2) +1;
            if (k==i) return;
            try {wait();}
            catch(Exception e) {System.exit(666);}
            }
        }
    public synchronized void Get_out(int i)
        {
        n = i;
        notifyAll();
        }
    }

