package atm;

import java.util.Scanner;

public class Operacoes {

        Scanner scan = new Scanner(System.in);
	private static Conta secao;
        private static Banco banco;

	private viewATM viewATM;

	public boolean saque() {
            double val;
            Senha senha;
            System.out.println("----- MODULO SAQUE -----\n\n");
            System.out.println("Escolha o valor desejado\n");
            val = scan.nextDouble();
            System.out.println("Digite a senha\n");
            senha = new Senha(scan.next());
            if(getSecao().getSenha().compareSenha(senha)){
                Saque saq = new Saque(val,senha.toString());
                saq.Sacar();
                return true;
            } else{
                System.out.println("Senha incorreta\n\nSaindo...");
                return false;
            }            
	}

	public boolean saldo() {
            Senha senha;
            System.out.println("----- MODULO SALDO -----\n\n");
            System.out.println("Digite a senha\n");
            senha = new Senha(scan.next());
            if(getSecao().getSenha().compareSenha(senha)){
                Saldo sal = new Saldo();
                System.out.println("Saldo\n\nR$"+sal.getSaldo());
                return true;
            } else{
                System.out.println("Senha incorreta\n\nSaindo...");
                return false;
            }
	}

	public boolean transfere() {
            double val;
            int d1,d2;
            Senha senha;
            System.out.println("----- MODULO TRANFERENCIA -----\n\n");
            System.out.println("Escolha o valor desejado\n");
            val = scan.nextDouble();
            System.out.println("Digite o codigo do banco de destino\n");
            d1 = scan.nextInt();
            System.out.println("Digite o numero da conta de destino\n");
            d2 = scan.nextInt();
            System.out.println("Digite a senha\n");
            senha = new Senha(scan.next());
            if(getSecao().getSenha().compareSenha(senha)){
                Transfere trans = new Transfere(val,d1,d2);
                trans.Transferir();
                return true;
            } else{
                System.out.println("Senha incorreta\n\nSaindo...");
                return false;
            }
	}

	public boolean alteraSenha() {
		return false;
	}

	public boolean ativa_cartao() {
		return false;
	}

	public boolean deposito() {
            double val;
            int d1,d2;
            Senha senha;
            System.out.println("----- MODULO DEPOSITO -----\n\n");
            System.out.println("Escolha o valor desejado\n");
            val = scan.nextDouble();
            System.out.println("Digite o codigo do banco de destino\n");
            d1 = scan.nextInt();
            System.out.println("Digite o numero da conta de destino\n");
            d2 = scan.nextInt();
            System.out.println("Digite a senha\n");
            senha = new Senha(scan.next());
            if(getSecao().getSenha().compareSenha(senha)){
                Deposita dep = new Deposita(val,d1,d2);
                dep.Deposito();
                return true;
            } else{
                System.out.println("Senha incorreta\n\nSaindo...");
                return false;
            }
	}

	public boolean pagamento() {
            long cod;
            Senha senha;
            System.out.println("----- MODULO PAGAMENTOS -----\n\n");
            System.out.println("Digite o código do boleto (11 digitos)\n");
            cod = scan.nextLong();
            Pagamento pag = new Pagamento(cod);
            System.out.println("Dados do boleto\n");
            System.out.println("Cod Banco: "+pag.getBanco());
            System.out.println("Cod Conta: "+pag.getConta());
            System.out.println("Valor: "+pag.getValor());
            System.out.println("\n\nDigite a senha\n");
            senha = new Senha(scan.next());
            if(getSecao().getSenha().compareSenha(senha)){
                pag.parseBoleto(cod);
                return true;
            } else{
                System.out.println("Senha incorreta\n\nSaindo...");
                return false;
            }
	}

	public static Conta getSecao() {
            return Operacoes.secao;
	}
        
        public static Banco getBanco() {
            return Operacoes.banco;
	}

}
