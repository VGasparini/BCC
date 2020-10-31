package biblioteca;
import java.util.Date;

public class Emprestimo {
    
    private final Midia midia;
    private final Date data_emp;
    private final Date data_ret;
    
    public Emprestimo(Midia m, Date d) {
        this.midia = m;
        this.data_emp = d;
        this.data_ret = m.getDataRetorno(d);
    }

    public Midia getMidia() {
        return midia;
    }

    public Date getData_emp() {
        return data_emp;
    }

    public Date getData_ret() {
        return data_ret;
    }
    
    public int getAtraso(Date d) {
        int dias = (int) ((d.getTime() - data_ret.getTime()) / (24 * 60 * 60 * 1000));
        if (dias <= 0) {
            return 0;
        } else {
            return dias;
        }
    }
    
}
