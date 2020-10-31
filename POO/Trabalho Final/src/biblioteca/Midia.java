package biblioteca;
import java.util.Calendar;
import java.util.Date;

public abstract class Midia {
    
    private String nome;
    private boolean emprestado = false;

    public String getNome() {
        return nome;
    }
    
    public boolean getEmprestado() {
        return emprestado;
    }
    
    public void setEmprestado(boolean b) {
        emprestado = b;
    }
    
    public void setNome(String n) {
        this.nome = n;
    }
    
    public Date getDataRetorno(Date emp) {
        Calendar c = Calendar.getInstance();
        c.setTime(emp);
        c.add(Calendar.DATE, 7);
        return c.getTime();
    }
    
    @Override
    public String toString() {
        return getNome();
    }
    
    abstract public String desc();
    
}
