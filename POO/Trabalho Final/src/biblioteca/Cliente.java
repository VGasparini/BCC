package biblioteca;
import java.util.Date;
import java.util.Vector;

public class Cliente {
    
    private final String nome;
    private final int cpf;
    private Vector<Emprestimo> emprestimos = new Vector();
    
    public Cliente(String n, int cpf) {
        this.nome = n;
        this.cpf = cpf;
    }

    public String getNome() {
        return nome;
    }

    public int getCpf() {
        return cpf;
    }
    
    public Vector<Emprestimo> getEmprestimos() {
        return emprestimos;
    }
    
    public Emprestimo getEmprestimo(Midia m) {
        for (Emprestimo e : emprestimos) {
            if (e.getMidia() == m) {
                return e;
            }
        }
        return null;
    }
    
    public void realizarEmprestimo(Midia m, Date d) {
        Emprestimo e = new Emprestimo(m, d);
        m.setEmprestado(true);
        emprestimos.add(e);
    }
    
    public void devolverEmprestimo(Emprestimo e) {
        e.getMidia().setEmprestado(false);
        emprestimos.remove(e);
    }
    
    public void devolverEmprestimo() {
        for (Emprestimo e : emprestimos) {
            e.getMidia().setEmprestado(false);
        }
        emprestimos.clear();
    }
    
    @Override
    public String toString() {
        return nome;
    }
    
}
