package biblioteca;

public class Biblioteca {

    public static void main(String[] args) {
        Facade facade = new Facade();
        facade.get().defaultvalues();
        FormLogin login = new FormLogin();
        login.show();
    }
    
}
