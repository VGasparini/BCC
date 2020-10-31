package atm;

public class Saque {

	private double valor;

	private Senha senha;
        
        private Operacao saq;

        Saque(double valor, String senha){
            setValor(valor);
            setSenha(senha);
        }
        
	public void setValor(double valor) {
            this.valor = valor;
	}

	public void setSenha(String senha) {
            this.senha = new Senha(senha);
	}
        
        public Operacao Sacar() {
            this.saq.setFrom(Operacoes.getSecao());
            this.saq.setTo(Operacoes.getSecao().getId());
            this.saq.setValor(-this.valor);
            return saq;
	}

}
