package materia;
import java.util.ArrayList;


public class Physics {
    static final int NV=1, NF=1, ND=1;

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
