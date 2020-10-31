package prova2q2;

/**
 * Prova 2 - Dia 15/10 - Questão 2
 * @author Vinicius Gasparini
 */

public abstract class Produto implements Venal{
    private int cod;
    private String nome;
    private int tempoVida;
    
    public Produto(int cod, String nome, int tempoVida){
        setCod(cod);
        setNome(nome);
        setTempoVida(tempoVida);
    }

    /**
     * @return the cod
     */
    public int getCod() {
        return cod;
    }

    /**
     * @param cod the cod to set
     */
    public void setCod(int cod) {
        this.cod = cod;
    }

    /**
     * @return the nome
     */
    public String getNome() {
        return nome;
    }

    /**
     * @param nome the nome to set
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * @return the tempoVida
     */
    public int getTempoVida() {
        return tempoVida;
    }

    /**
     * @param tempoVida the tempoVida to set
     */
    public void setTempoVida(int tempoVida) {
        this.tempoVida = tempoVida;
    }
    
}
