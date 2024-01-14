import java.util.ArrayList;
import java.lang.Math;

enum Quark  {UP,DOWN};
enum Hadron {PROTON,NEUTRON}
enum Nucleo {HIDROGENO,HELIO,LITIO}

public class Materia
    {
    static final int NV = 3;
    static final int NF = 3;
    static final int ND = 3;
   
    public static void main (String[] args)
        {
        Thread hilo;
        ArrayList<Agente> hilos = new ArrayList<>();
        Espacio espacio = new Espacio();

        for (int i=0; i<NV; i++) hilos.add(new Vacio(espacio));
        for (int i=0; i<NF; i++) hilos.add(new Fuerte(espacio));
        for (int i=0; i<ND; i++) hilos.add(new Debil(espacio));
        for (Agente h : hilos) h.start();
        for (Agente h : hilos) h.Join();
        }
    }

class Espacio
    {
    private int n_ups = 0;
    private int n_downs = 0;
    private int n_protones = 0;
    private int n_neutrones = 0;
    private int n_hidrogenos = 0;
    private int n_helios = 0;
    private int n_litios = 0;

    public String Estado()
        {
        return ("["+n_ups+","+n_downs+"] ["+n_protones+","+n_neutrones+"] ["+n_hidrogenos+","+n_helios+","+n_litios+"]");
        }

    public synchronized void Add(Quark q)
        {
        switch (q)
            {
            case UP: n_ups++; break;
            default: n_downs++; break;
            }
        notifyAll();
        }  
    public synchronized void Add(Hadron h)
        {
        switch (h)
            {
            case PROTON: n_protones++; break;
            default: n_neutrones++; break;
            }
        notifyAll();
        } 
    public synchronized void Add(Nucleo n) 
        {
        switch (n)
            {
            case HIDROGENO: n_hidrogenos++; break;
            case HELIO: n_helios++; break;
            default: n_litios++; break;
            }
        } 
    public synchronized void Get_quarks(int nu, int nd)
        {
        while (n_ups < nu || n_downs < nd) Wait();
        n_ups -= nu;
        n_downs -= nd;
        }
    public synchronized void Get_hadrones(int np, int nn)
        {
        while (n_protones < np || n_neutrones < nn) Wait();
        n_protones -= np;
        n_neutrones -= nn;
        }

    private void Wait()
        {
        try
            {
            wait();
            }
        catch (Exception e)
            {
            System.err.println(e.getMessage());
            System.exit(666);
            }
        }
    }

abstract class Agente extends Thread
    {
    protected String tabs;
    
    public Agente(String tabs)
        {
        this.tabs= tabs;
        }
    protected void Print(String s) 
        {
        System.out.println(tabs+"["+getId()+"]"+s);
        }
    public void Join()
        {
        try {join();}
        catch(InterruptedException e)
            {
            System.err.println(e);
            System.exit(-1);
            }  
        }
    public void Pausa(int min, int max)
        {
        int tiempo = min + (int)(Math.random()*max);
        Pausa(tiempo);
        }
    public void Pausa(int tiempo)
        {
        try
            {
            Thread.sleep(tiempo);
            }
        catch(InterruptedException e)
            {
            System.err.println(e);
            System.exit(-1);
            }  
        }
    }

class Vacio extends Agente
    {
    Espacio espacio;
    
    public Vacio(Espacio espacio)
        {
        super("");
        this.espacio = espacio;
        }

    private Quark Next()
        {
        double v = Math.random();
        Quark q = (v>0.5) ? Quark.UP : Quark.DOWN;
        return(q);
        }

    public void run()
        {
Print("");
        Quark q;
        while (true)
            {
            Pausa (1000, 2000);
            q = Next();
Print(q+"");
Print(espacio.Estado()+"<");
            
            espacio.Add(q);

Print(espacio.Estado()+">");
            }
        }
    }
class Fuerte extends Agente
    {
    Espacio espacio;

    public Fuerte(Espacio espacio)
        {
        super("\t\t");
        this.espacio = espacio;
        }

    private Hadron Next()
        {
        double v = Math.random();
        Hadron h = (v>0.3) ? Hadron.PROTON : Hadron.NEUTRON;
        return(h);
        }

    public void run()
        {
        Hadron h;

Print("");

        while (true)
            {
Print(espacio.Estado()+"<");
            h = Next();
Print(h+"");
            
            switch (h)
                {
                case PROTON:
                    espacio.Get_quarks(2,1);
                    break;
                case NEUTRON: 
                    espacio.Get_quarks(1,2);
                    break;
                default:
                    System.err.println("Error en el tipo de hadron");
                    System.exit(666);
                    break;
                }

            Pausa (100, 500);
            espacio.Add(h);
Print(espacio.Estado()+">");
            }
        }
    }

class Debil extends Agente
    {
    Espacio espacio;

    public Debil(Espacio espacio)
        {
        super("\t\t\t\t");
        this.espacio = espacio;
        }

    public Nucleo Next()
        {
        double v = Math.random();
        Nucleo n = (v>0.90) 
            ? Nucleo.LITIO 
            : (v>0.60)  
                ? Nucleo.HELIO 
                : Nucleo.HIDROGENO;
        return(n);
        }

    public void run()
        {
Print("");

        Nucleo n;
        while (true)
            {
            Pausa (1000, 2000);

Print(espacio.Estado()+"<");
            n = Next();
Print(n+"");

            switch (n)
                {
                case HIDROGENO:
                    espacio.Get_hadrones(1,0);
                    break;
                case HELIO:
                    espacio.Get_hadrones(2,2);
                    break;
                case LITIO:
                    espacio.Get_hadrones(3,4);
                    break;
                default:
                    System.err.println("Error en el tipo de hadron");
                    System.exit(666);
                    break;
                }
            Pausa(100,500);
            espacio.Add(n);
Print(espacio.Estado()+">");
            }
        }
    }
