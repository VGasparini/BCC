package atm;

import javafx.util.Pair;

public class Operacao extends Banco{
        private Pair<Integer, Integer> to;
	private Conta from;
	private double valor;

	public void setFrom(Conta id) {
            this.from = id;
	}

	public void setTo(int banco, int conta) {
            this.to =  new Pair<>(banco,conta);
	}

            
        public void setTo(int conta) {
            this.to =  new Pair<>(Operacoes.getBanco().getId(),conta);
	}
        
        public void setTo(Conta conta) {
            this.to =  new Pair<>(Operacoes.getBanco().getId(),conta.getId());
	}
        
	public void setValor(double valor) {
            this.valor = valor;
	}
        
        public Conta getTo(){
            return getConta(this.to.getValue());
        }
        public Conta getFrom(){
            return this.from;
        }
        public double getValor(){
            return this.valor;
        }

}
