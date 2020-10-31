package biblioteca;
import java.util.Date;
import java.util.Vector;

public class Facade {
    
    private static Facade instance = new Facade();
    
    public static Facade get(){
        return instance;
    }
    
    public Vector<Bibliotecario> bibliotecarios = new Vector();
    public Vector<Cliente> clientes = new Vector();
    public Vector<Midia> midias = new Vector();
    public Bibliotecario logged;
    
    public Bibliotecario login(String u, String s) {
        for (Bibliotecario b : bibliotecarios) {
            if (b.getUsuario().equals(u)) {
                if (b.checkAuth(s)) {
                    return b;
                }
            }
        }
        return null;
    }
    
    public void cadastrarLivro(String nome, String autor, int isbn) {
        Livro l = new Livro(nome, autor, isbn);
        midias.add(l);
    }
    
    public void cadastrarDVD(String nome, String produtor, int tempo) {
        DVD d = new DVD(nome, produtor, tempo);
        midias.add(d);
    }
    
    public void cadastrarBibliotecario(String usuario, String senha) {
        Bibliotecario b = new Bibliotecario(usuario, senha, TipoBibliotecario.NORMAL);
        bibliotecarios.add(b);
    }
    
    public void cadastrarCliente(String usuario, int cpf) {
        Cliente c = new Cliente(usuario, cpf);
        clientes.add(c);
    }
    
    public void removerCliente(Cliente c) {
        clientes.remove(c);
    }
    
    public void removerMidia(Midia m) {
        midias.remove(m);
    }
    
    public void removerBibliotecario(Bibliotecario b) {
        bibliotecarios.remove(b);
    }
    
    public void realizarEmprestimo(Cliente c, Midia m, Date d) {
        c.realizarEmprestimo(m, d);
    }
    
    public int devolverMidia(Cliente c, Midia m, Date d) {
        Emprestimo e = c.getEmprestimo(m);
        int atraso = e.getAtraso(d);
        c.devolverEmprestimo(e);
        return atraso;
    }
    
    public int devolverMidia(Cliente c, Date d) {
        int atraso = 0;
        for (Emprestimo e : c.getEmprestimos()) {
            atraso += e.getAtraso(d);
        }
        c.devolverEmprestimo();
        return atraso;
    }
    
    public void defaultvalues() {
        Bibliotecario admin = new Bibliotecario("adm", "123", TipoBibliotecario.ADMIN);
        bibliotecarios.add(admin);
        Cliente c = new Cliente("Jõao", 123);
        clientes.add(c);
        Livro l = new Livro("Biblia", "Cristo", 10);
        midias.add(l);
        DVD d = new DVD("Shrek", "Dreamworks", 120);
        midias.add(d);
    }
    
    public Vector getMidiaItems() {
        Vector v = new Vector();
        for (Midia m : midias) {
            v.add(m);
        }
        return v;
    }
    
    public Cliente getCliente(int cpf){
        for (Cliente c : clientes) {
            if (c.getCpf() == cpf) {
                return c;
            }
        }
        return null;
    }
    
}
