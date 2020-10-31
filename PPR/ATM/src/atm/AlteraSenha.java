package atm;

public class AlteraSenha {

	private Senha senhaAtual;

	private Senha novaSenha;

	private Senha confirmaSenha;

	public void setNovaSenha(String senha) {
            this.novaSenha = new Senha(senha);
	}

	public void setSenha(String senha) {
            this.senhaAtual = new Senha(senha);
	}

	public void setConfirmaSenha(String senha) {
            this.confirmaSenha = new Senha(senha);
	}

	public boolean verifica(Senha nova, Senha confirma) {
		if(nova.compareSenha(confirma)){
                    this.senhaAtual = new Senha(confirma.toString());
                    return true;
                }
                return false;
	}

}
