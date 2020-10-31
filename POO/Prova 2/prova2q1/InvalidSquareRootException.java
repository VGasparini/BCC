package prova2q1;

/**
 * Prova 2 - Dia 15/10 - Questão 1
 * @author Vinicius Gasparini
 */

public class InvalidSquareRootException extends RuntimeException {

    /**
     * O erro é acionado no momento em que uma operação de raiz quadrada
     * retorne um valor negativo
     */
    public InvalidSquareRootException() {
        super("Invalid square root. Imaginary numbers required.");
    }
}
