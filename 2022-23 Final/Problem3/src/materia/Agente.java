package materia;
abstract class Agente extends Thread
    {
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
        int tiempo = min + (int) (Math.random()*max);
        Pausa(tiempo) ;
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