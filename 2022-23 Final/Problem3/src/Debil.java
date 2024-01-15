class Debil extends Agente
    {
    Espacio espacio;
    
    public Debil(Espacio espacio)
        {
        this.espacio = espacio;
        }
    
    public Nucleo Next()
        {
        double v = Math. random() ;
        Nucleo n = (v>0.90)
            ? Nucleo.LITIO
            : (v>0.60)
                ? Nucleo.HELIO
                : Nucleo.HIDROGENO;
        return(n);
        }
    
    public void run()
        {
        Nucleo n;
        while (true)
            {
            Pausa (1000, 2000);
            n = Next ();
            
            switch (n)
                {
                case HIDROGENO:
                    espacio.Get_hadrones(1,0);
                    break;
                case HELIO:
                    espacio.Get_hadrones(2,2);
                    break;
                default:
                    espacio.Get_hadrones(3,4);
                    break;
                }
            Pausa(100,500);
            espacio.Add(n);
            }
        }
    }