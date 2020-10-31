package prova;

/**
 *
 * @author Filipe Cattoni Elias e Vinicius Gasparini
 */

public class TrunfoCard {
    
    private static int ccod = 100001;
    private final int cod;
    private final String name;
    private Jogador dono;
    private final String classe;
    private final double potencia;
    private final double aceleracao;
    private final int peso;
    private boolean erro;
    
    TrunfoCard(String name,String classe,double potencia,double aceleracao,int peso){
        this.cod = ccod;
        ccod++;
        if(name.length() < 5){
            this.erro = true;
            this.name = "?";
            System.out.println("Nome inválido!");
        } else {
            this.name = name;
        }
        if(potencia < 1 || potencia > 2000){
            this.erro = true;
            this.potencia = 0;
            System.out.println("Potência inválida!");
        } else {
            this.potencia = potencia*0.98623;
        }
        if(aceleracao < 0.1 || aceleracao > 50.0){
            this.erro = true;
            this.aceleracao = 0;
            System.out.println("Aceleração inválida!");
        } else {
            this.aceleracao = aceleracao;
        }
        if(peso < 50 || peso > 5000){
            this.erro = true;
            this.peso = 0;
            System.out.println("Peso inválido!");
        } else {
            this.peso = peso;
        }
        this.classe = classe;
        this.dono = null;
    }
    public String toString(){
        return "COD: "+cod+" / Nome: "+name+" / Classe: "+classe+"\nPotência: "+potencia+" cv / Aceleração (0-100km/h): "+aceleracao+"s / Peso: "+peso+"kg\n";
    }
    
    public static int compara(TrunfoCard t1, TrunfoCard t2, String tipodisputa){
        switch (tipodisputa){
            case "Classe":
                return t1.classe.compareTo(t2.classe);                
            case "Potência":
                if (t1.potencia == t2.potencia) return 0;              
                if (t1.potencia > t2.potencia) return -1;
                return 1;
            case "Aceleração":
                if (t1.aceleracao == t2.aceleracao) return 0;              
                if (t1.aceleracao < t2.aceleracao) return -1;
                return 1;                
            case "Peso":
                if (t1.peso == t2.peso) return 0;              
                if (t1.peso > t2.peso) return -1;
                return 1; 
            default:
                System.out.println("Comparação inválida: "+tipodisputa);
                return -2; 
        }
    }
    
    public Jogador getDono() {
        return dono;
    }

    public void setDono(Jogador dono) {
        this.dono = dono;
    }
    
}
