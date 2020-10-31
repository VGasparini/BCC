package prova2q1;

/**
 * Prova 2 - Dia 15/10 - Questão 1
 * @author Vinicius Gasparini
 */

public class Main {
    public static void main(String[] args) {
        try {
            Fracao f1 = new Fracao(-3, 0);
            System.out.println("Fração 1 --> "+f1+"\n");
            Fracao f1r = f1.sqrt();
            System.out.println("Raiz da Fração 1 --> "+f1r+"\n\n");
        } catch (Exception e) {
            System.err.print(e);
        }
        
        try {
            Fracao f2 = new Fracao(1, 2.0f);
            System.out.println("Fração 2 --> "+f2+"\n");
            Fracao f2r = f2.sqrt();
            System.out.println("Raiz da Fração 2 --> "+f2r+"\n\n");
        } catch (Exception e) {
            System.err.print(e);
        }
    }
    
}