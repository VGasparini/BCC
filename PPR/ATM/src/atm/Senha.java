package atm;

public class Senha {
    String senha;
    
    Senha(String s){
        this.senha = s;
    }
    
    private String getSenha(){
        return senha;
    }
    
    public boolean compareSenha(Senha s){
        return this.getSenha().equals(s.getSenha());
    }
}
