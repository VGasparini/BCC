package prova2q2;

/**
 * Prova 2 - Dia 15/10 - Questão 2
 * @author Vinicius Gasparini
 */

public abstract class Midia extends Produto{
    private String dataEmprestimoAtual;
    private int dataEmprestimo;
    
    public Midia(int cod, String nome, int tempoVida){
       super(cod,nome,tempoVida);
       this.dataEmprestimoAtual = null;
       this.dataEmprestimo = 0;
    }
    
    public double alugar(int dias, String data){
        setDataEmprestimoAtual(data);
        setDataEmprestimo(dias);
        if(this.getTempoVida()<365) return 4.0f * getDataEmprestimo();
        else return 2.50f * getDataEmprestimo();
    }

    /**
     * @return the dataEmprestimoAtual
     */
    public String getDataEmprestimoAtual() {
        return dataEmprestimoAtual;
    }

    /**
     * @param dataEmprestimoAtual the dataEmprestimoAtual to set
     */
    public void setDataEmprestimoAtual(String dataEmprestimoAtual) {
        this.dataEmprestimoAtual = dataEmprestimoAtual;
    }

    /**
     * @return the dataEmprestimo
     */
    public int getDataEmprestimo() {
        return dataEmprestimo;
    }

    /**
     * @param dataEmprestimo the dataEmprestimo to set
     */
    public void setDataEmprestimo(int dataEmprestimo) {
        this.dataEmprestimo = dataEmprestimo;
    }

}
