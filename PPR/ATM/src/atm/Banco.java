package atm;

import java.util.List;

public class Banco {

	private int id;

	private List<Conta> contas;

	public int getId() {
            return this.id;
	}
        
	public Conta getConta(int id) {
            for(Conta conta : contas){
                if (conta.getId()==id){
                    return conta;
                }
            }
            return null;
	}

	public double getSaldo(Conta id) {
            return this.contas.get(id.getId()).getSaldo();
	}

	public boolean setSaldo(Conta id, double valor) {
            this.contas.get(id.getId()).setSaldo(valor);
            return true;
	}

	public Senha getSenha(Conta id) {
		return this.contas.get(id.getId()).getSenha();
	}

	public boolean setSenha(Conta id, Senha nova) {
		this.contas.get(id.getId()).setSenha(nova);
                return true;
	}

	public boolean getAtiva(Conta id) {
		return this.contas.get(id.getId()).getAtiva();
	}

	public boolean setAtivo(Conta id, boolean estado) {
		return this.contas.get(id.getId()).setAtiva(estado);
	}
}
