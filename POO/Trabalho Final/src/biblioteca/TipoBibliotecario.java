package biblioteca;

public enum TipoBibliotecario {
    NORMAL, ADMIN;
    public static TipoBibliotecario getTipo(int t){
        switch (t) {
            case 0:
                return ADMIN;
            default:
                return NORMAL;
        }
    }
}
