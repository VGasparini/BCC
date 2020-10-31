package atm;

public class AtivaCartao {

	private int pin;
	private String CPF;
        
        AtivaCartao(int pin, String cpf){
            this.pin = pin;
            this.CPF = cpf;
	}
        
        private int getPin(){
            return this.pin;
        }
        private String getCPF(){
            return this.CPF;
        }
        
        public boolean ativar(Conta C){
            boolean flag1 = false, flag2 = false;
            if(!C.getAtiva()){
                if(C.getPin() == this.getPin()) flag1 = true;
                if(C.getCliente().getCPF().equals(this.getCPF())) flag2 = true;
                if(flag1 && flag2){
                    C.setAtiva(true);
                    return true;
                }
            }
            return false;
        }

}
