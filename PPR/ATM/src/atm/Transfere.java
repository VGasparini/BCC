package atm;

public class Transfere  {

	private double valor;
        private int bancoId;
        private int contaId;

        private Operacao trans;
        
        Transfere(double valor, int d1, int d2){
            setValor(valor);
            setBancoId(d1);
            setContaId(d2);
        }
        
	public void setValor(double valor) {
            this.valor = valor;
	}
        
        public void setBancoId(int banco){
            this.bancoId = banco;
        }
        
        public void setContaId(int conta){
            this.contaId = conta;
        }
        
        public Operacao Transferir() {
            this.trans.setFrom(Operacoes.getSecao());
            this.trans.setTo(this.bancoId,this.contaId);
            this.trans.setValor(this.valor);
            return trans;
	}

}
