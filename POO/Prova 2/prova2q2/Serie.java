package prova2q2;

/**
 * Prova 2 - Dia 15/10 - Questão 2
 * @author Vinicius Gasparini
 */

public class Serie extends Midia implements Venal{
    private int temporada = 0;
    private int episodios = 0;
    private double b = (1 + episodios) / 100;
    
    public Serie(int cod, String nome, int tempoVida,int temporada, int episodios){
       super(cod,nome,tempoVida);
       this.temporada = temporada;
       this.episodios = episodios;
    }
    
    @Override
    public double alugar(int dias, String data){
        setDataEmprestimoAtual(data);
        setDataEmprestimo(dias);
        if(this.getTempoVida()<365) return 4.0f * getDataEmprestimo() * b;
        else return 2.50f * getDataEmprestimo() * b;
    }
    
    @Override
    public double getPrecoVista(){
        return 25;
    }
    @Override
    public double getPrecoPrazo(int parcelas){
        if(parcelas == 2) return 14;
        else if(parcelas == 3) return 10;
        else{
            System.out.println("Erro. Número de parcelas inválido. Retornando valor a vista");
            return 25;
        }
    }
    
    /**
     * @return the temporada
     */
    public int getTemporada() {
        return temporada;
    }

    /**
     * @param temporada the temporada to set
     */
    public void setTemporada(int temporada) {
        this.temporada = temporada;
    }

    /**
     * @return the episodios
     */
    public int getEpisodios() {
        return episodios;
    }

    /**
     * @param episodios the episodios to set
     */
    public void setEpisodios(int episodios) {
        this.episodios = episodios;
    }
}
