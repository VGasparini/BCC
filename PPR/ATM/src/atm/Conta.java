package atm;

public class Conta {

	private int id;
	private Pessoa cliente;
	private double saldo;
	private boolean ativa;
	private int pin;        
        private Senha senha;
        private int bancoId;

	public int getId() {
            return this.id;
	}
        
	public int getBancoId() {
            return this.bancoId;
	}

	public double getSaldo() {
            return this.saldo;
	}

	public boolean setSaldo(double valor) {
            this.saldo += valor;
            return true;
	}

	public boolean getAtiva() {
            return this.ativa;
	}

	public boolean setAtiva(boolean estado) {
            this.ativa = estado;
            return this.ativa;
	}

	public int getPin() {
            return this.pin;
	}
        
        public Pessoa getCliente(){
            return this.cliente;
        }
        
        public Senha getSenha(){
            return this.senha;
        }
        
        public void setSenha(Senha senha){
            this.senha = senha;
        }

}
