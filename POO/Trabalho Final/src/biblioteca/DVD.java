package biblioteca;

import java.util.Calendar;
import java.util.Date;

public class DVD extends Midia {
    
    private final String produtor;
    private final int tempo_minutos;
    
    public DVD(String n, String p, int t) {
        this.setNome(n);
        this.produtor = p;
        this.tempo_minutos = t;
    }
    
    public String desc() {
        return "Nome: " + this.getNome() + 
                "\nProdutor: " + this.produtor + 
                "\nDuraçao: " + this.tempo_minutos + " minutos\n";
    }

    public String getProdutor() {
        return produtor;
    }

    public int getTempo_minutos() {
        return tempo_minutos;
    }
    
    @Override
    public Date getDataRetorno(Date emp) {
        Calendar c = Calendar.getInstance();
        c.setTime(emp);
        c.add(Calendar.DATE, 3);
        return c.getTime();
    }
    
}
