package biblioteca;

public class Livro extends Midia {
    
    private final String autor;
    private final int isbn;
    
    public Livro(String n, String a, int i) {
        this.setNome(n);
        this.autor = a;
        this.isbn = i;
    }
    
    public String desc() {
        return "Nome: " + this.getNome() +
                "\nAutor: " + this.autor +
                "\nISBN: " + this.isbn + '\n';
    }

    public String getAutor() {
        return autor;
    }

    public int getIsbn() {
        return isbn;
    }
    
}
