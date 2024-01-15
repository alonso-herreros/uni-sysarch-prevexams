class Fuerte extends Agente
    {
    Espacio espacio;
    
    public Fuerte(Espacio espacio)
        {
        this.espacio = espacio;
        }

    private Hadron Next()
        {
        double v = Math. random() ;
        Hadron h = (v>0.3)
            ? Hadron. PROTON : Hadron.NEUTRON;
        return(h);
        }
    
    public void run()
        {
        Hadron h;
        
        while (true)
            {
            h = Next ();

            switch (h)
                {
                case PROTON:
                    espacio.Get_quarks(2,1);
                    break;
                default:
                    espacio.Get_quarks(1,2);
                    break;
                }
            Pausa (100, 500);
            espacio.Add(h);
            }
        }
    }