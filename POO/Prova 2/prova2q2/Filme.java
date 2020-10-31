package prova2q2;

/**
 * Prova 2 - Dia 15/10 - Questão 2
 * @author Vinicius Gasparini
 */

public abstract class Filme extends Midia{

    private int duracao;
    
    public Filme(int cod, String nome, int tempoVida, int duracao){
       super(cod,nome,tempoVida);
       this.duracao = duracao;
    }
    
    
    /**
     * @return the duracao
     */
    public int getDuracao() {
        return duracao;
    }

    /**
     * @param duracao the duracao to set
     */
    public void setDuracao(int duracao) {
        this.duracao = duracao;
    }    
}
