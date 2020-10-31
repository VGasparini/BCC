package prova2q2;

/**
 * Prova 2 - Dia 15/10 - Questão 2
 * @author Vinicius Gasparini
 */

public abstract class Revista extends Produto implements Venal{
    private final int paginas;
    private final double valorBase;
    
    public Revista(int cod, String nome, int tempoVida, int paginas, double valorBase){
        super(cod,nome,tempoVida);
        this.paginas = paginas;
        this.valorBase = valorBase;
    }
    
    @Override
    public double getPrecoVista(){
        return getValorBase() * 1.5f;
    }
    @Override
    public double getPrecoPrazo(int parcelas){
        return getValorBase() * (1.5f + parcelas * 0.05f);
    }

    /**
     * @return the paginas
     */
    public int getPaginas() {
        return paginas;
    }

    /**
     * @return the valorBase
     */
    public double getValorBase() {
        return valorBase;
    }
}
