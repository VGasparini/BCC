package atm;

public class BancoController {

	private Operacao operacao;
	private Banco banco;

	public int getId() {
		return this.banco.getId();
	}

	public Conta getConta(int id) {
            return this.banco.getConta(id);
	}

	public boolean setConta(Operacao op) {
            op.getTo().setSaldo(op.getValor());
            return true;
	}

}
