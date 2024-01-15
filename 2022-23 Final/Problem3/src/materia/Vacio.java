package materia;

class Vacio extends Agente
    {
    Espacio espacio;
    
    public Vacio(Espacio espacio)
        {
        super();
        this.espacio = espacio;
        }
    
    private Quark Next()
        {
        double v = Math. random();
        Quark q = (v>0.5) ? Quark.UP : Quark.DOWN;
        return(q);
        }
    
    public void run()
        {
        Quark q;
        while (true)
            {
            Pausa (1000, 2000);
            q = Next();
            espacio.Add(q);
            }
        }
    }