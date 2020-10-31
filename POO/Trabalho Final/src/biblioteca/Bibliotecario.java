package biblioteca;

public class Bibliotecario {
    
    private final String usuario;
    private final String senha;
    private final TipoBibliotecario tipo;
    
    public Bibliotecario(String u, String s, TipoBibliotecario t) {
        this.usuario = u;
        this.senha = s;
        this.tipo = t;
    }
    
    public boolean checkAuth(String s) {
        return s.equals(senha);
    }
    
    public String getUsuario() {
        return usuario;
    }
    
    public TipoBibliotecario getTipo() {
        return tipo;
    }
    
    public String toString() {
        return usuario;
    }
    
}
