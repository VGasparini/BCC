package atm;

import static java.lang.Math.toIntExact;

public class Pagamento {

    private long codBoleto;
    private Operacao pag;
    private int banco;
    private int conta;
    private double valor;

    Pagamento(long cod){
        setBanco(cod);
        setConta(cod);
        setValor(cod);
    }

    public void setCodBoleto(long cod) {
        this.codBoleto = cod;
    }

    public void setBanco(long cod){
        int codi = toIntExact(cod);
        this.banco = codi%(int)10e11/(int)10e11;
    }

    public void setConta(long cod){
        int codi = toIntExact(cod);
        this.conta = (codi%(int)10e8 - codi%(int)10e5)/(int)10e5;
    }

    public void setValor(long cod){
        int codi = toIntExact(cod);
        double val;
        val = codi%(int)10e5/10;
        this.valor = val;
    }
    
    public int getBanco() {
        return banco;
    }

    public int getConta() {
        return conta;
    }

    public double getValor() {
        return valor;
    }

    public Operacao parseBoleto(long cod) {
        int codi = toIntExact(cod);
        this.pag.setFrom(Operacoes.getSecao());
        this.pag.setTo(this.getBanco(), this.getConta());
        this.pag.setValor(this.getValor());
        return pag;
    }

}
