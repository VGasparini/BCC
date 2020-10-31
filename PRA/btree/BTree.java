package btree;

import java.io.File; 
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Scanner; 

/**
 * PRA - Trabalho 3 | B-Tree
 * @author Vinicius Gasparini
 * @author Matheus Henrique
 */

public class BTree { 
    static Scanner scan = new Scanner(System.in);
    static NumberFormat formatter = new DecimalFormat("#0.0000");  
    
    public static void main(String[] args) throws Exception {
        String line;
        long cont = 1;
        String conts;

        System.out.println("\n\nDigite o tamanho M maximo de filhos por nodo (M = 2k, k >= 1)\n ->");
        File file = new File("//home//gasp//git//PRA//data.txt"); 
        Scanner sc = new Scanner(file);    

        Tree<String, String> st = new Tree<>(scan.nextInt());

        long startRead = System.currentTimeMillis();

        while (sc.hasNextLine()){
          line = sc.nextLine();
          conts = String.valueOf(cont);
          st.put(conts, line);
          cont+= 69;
        }

        long endRead = System.currentTimeMillis();
        System.out.println("Tempo de inserção:" +formatter.format((endRead - startRead)/1000f)+" s");

        System.out.println("\n\nDigite o indice K do registro a ser procurado (N = 1+69k, k>= 0)\n ->");
        String index = Integer.toString((scan.nextInt())*69+1);
        long startFind = System.currentTimeMillis();
        System.out.println(st.get(index));
        long endFind = System.currentTimeMillis();
        double process2 = (endFind - startFind)/(1000f);
        System.out.println("Tempo de busca:" +formatter.format(process2)+" s");

        System.out.println("\n\nDeseja imprimir a arvore criada?\n1 - Sim\n0 - Não");
        if(scan.nextInt() == 1) System.out.println(st);
        else System.out.println("\nFinalizando...");
    }
} 