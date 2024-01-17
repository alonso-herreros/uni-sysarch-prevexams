package materia;

public class Espacio {

    private int quarks[] = new int[2];
    private int hadrons[] = new int[2];
    private int nuclei[] = new int[3];
    
    public synchronized void Get_quarks(int up, int down) {
        while(quarks[0]<up || quarks[1]<down){
            try { wait(); } catch (InterruptedException e) {}
        }
        quarks[0] -= up;
        quarks[1] -= down;
    }
    public synchronized void Get_hadrones(int protons, int neutrons) {
        while(hadrons[0]<protons || hadrons[1]<neutrons){
            try { wait(); } catch (InterruptedException e) {}
        }
        hadrons[0] -= protons;
        hadrons[1] -= neutrons;
    }

    public synchronized void print() {
        System.out.printf("[Q:%dU,%dD] [H:%dP,%dN] [N:%dH,%dHe,%dLi]\n",
            quarks[0], quarks[1], hadrons[0], hadrons[1], nuclei[0], nuclei[1], nuclei[2]);
    }


    public synchronized void Add(Quark q) {
        quarks[(q==Quark.UP?0:1)]++;
        print();
        notifyAll();
    }
    public synchronized void Add(Hadron h) {
        hadrons[(h==Hadron.PROTON?0:1)]++;
        print();
        notifyAll();
    }
    public synchronized void Add(Nucleo n) {
        switch (n) {
        case HIDROGENO: 
            nuclei[0]++;
            break;
        case HELIO:
            nuclei[1]++;
            break;
        case LITIO:
            nuclei[2]++;
            break;
        }
        print();
        notifyAll();
    }
}
