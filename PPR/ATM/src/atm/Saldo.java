package atm;

public class Saldo {

	private double valor;

	public double getSaldo() {
	    return Operacoes.getSecao().getSaldo();
	}

}
