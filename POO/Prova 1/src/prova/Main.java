
package prova;

import java.util.Scanner;
import java.util.Random;

/**
 *
 * @author Filipe Cattoni Elias e Vinicius Gasparini
 */ 

public class Main {

    public static void main(String[] args) {
        
        TrunfoCard[] cartas = new TrunfoCard[3];
        cartas[0] = new TrunfoCard("Corvette","A2",423,1.9,1950);
        cartas[1] = new TrunfoCard("Fusca","B2",102,9.7,2100);
        cartas[2] = new TrunfoCard("QQ","B1",150,5.5,23);
        Jogador jogador1 = new Jogador("Cattoni");
        Jogador jogador2 = new Jogador("Gasparini");
        Jogador.distribuirCartas(jogador1, jogador2, cartas);
        Jogador.disputa(jogador1.sacar(), jogador2.sacar(), "Classe");
        jogador1.mostraCartas();
        jogador2.mostraCartas();
    }
    
}
