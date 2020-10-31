package prova;
import java.util.Random;

/**
 *
 * @author Filipe Cattoni Elias e Vinicius Gasparini
 */
public class Jogador {
    public final int MAX_CARTAS = 40;
    private String name;
    private TrunfoCard[] cartas = new TrunfoCard[MAX_CARTAS];
    public int tamanhoBaralho = 0;
    
    Jogador(String name){
        if(name.length() < 1 || name.contains("palavrao")){
            this.name = "-";
            System.out.println("Nome inválido!");
        } else {
            this.name = name;
        }
    }
    
    public void limparDeck(){
        for(int i = 0; i < tamanhoBaralho; i++){
            cartas[i].setDono(null);
        }
        cartas = new TrunfoCard[MAX_CARTAS];
        tamanhoBaralho = 0;
    }
    
    public void addCarta(TrunfoCard carta){
        if(tamanhoBaralho >= MAX_CARTAS) System.out.println("Baralho cheio");
        else{
            cartas[tamanhoBaralho] = carta;
            cartas[tamanhoBaralho].setDono(this);
            tamanhoBaralho++;
        }
    }
    
    private TrunfoCard popCarta(int carta){
        if(carta < tamanhoBaralho){
            TrunfoCard tmp = cartas[carta];
            for (int i = carta; i < tamanhoBaralho-1; i++) {
                cartas[i] = cartas[i+1];
            }
            cartas[tamanhoBaralho-1] = null;
            tamanhoBaralho--;
            return tmp;
        }
        return null;
    }
    
    public TrunfoCard sacar(){
        if(tamanhoBaralho != 0){
            Random r = new Random();
            return popCarta(r.nextInt(tamanhoBaralho));
        } else {
            System.out.println("Baralho vazio");
            return null;
        }
    }
    
    public static void distribuirCartas(Jogador j1, Jogador j2, TrunfoCard[] cartas){
        int pivot = cartas.length/2;
        for (int i=0; i<pivot; i++){
            j1.addCarta(cartas[i]);
        }
        for (int i=pivot; i<cartas.length; i++){
            j2.addCarta(cartas[i]);
        }
    }
    
    
    public static boolean disputa(TrunfoCard t1, TrunfoCard t2, String tipodisputa){
        int vencedor = TrunfoCard.compara(t1, t2, tipodisputa);
        if (vencedor == 1) {
            Jogador j = t2.getDono();
            j.addCarta(t1);
            j.addCarta(t2);
            return false;
        }
        else if (vencedor == -1) {
            Jogador j = t1.getDono();
            j.addCarta(t1);
            j.addCarta(t2);
            return true;
        }
        else {
            Jogador j1 = t1.getDono();
            Jogador j2 = t2.getDono();
            j1.addCarta(t1);
            j2.addCarta(t2);
            return true;
        }
    }
    
    public void mostraCartas(){
        System.out.println("JOGADOR: "+this.name);
        for (int i=0; i<tamanhoBaralho; i++){
            System.out.println(this.cartas[i]);
        }
        System.out.println("--------------\n");
    }
}
