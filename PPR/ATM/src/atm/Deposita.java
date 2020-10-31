package atm;

public class Deposita{

	private double valor;
        private int bancoId;
        private int contaId;

        private Operacao dep;
        
        Deposita(double valor, int d1, int d2){
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
        
        public Operacao Deposito() {
            this.dep.setFrom(Operacoes.getSecao());
            this.dep.setTo(this.bancoId,this.contaId);
            this.dep.setValor(this.valor);
            return dep;
	}
}
