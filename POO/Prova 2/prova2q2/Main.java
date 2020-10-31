package prova2q2;
import java.util.ArrayList;

/**
 * Prova 2 - Dia 15/10 - Questão 2
 * @author Vinicius Gasparini
 */

public class Main {
    public static void main(String[] args) {
        ArrayList<Produto> produtos = new ArrayList<>();
        boolean add = produtos.add(new Revista(1,"Globo",200,15,29) {});
    }
    
    static double realizarVendaPrazo(Venal item,int parcelas){
        return item.getPrecoPrazo(parcelas);
    }
    
    static String getPeriodoEmprestimo(Produto item){
        if(item instanceof Serie){
            if(((Serie) item).getDataEmprestimoAtual() != null) return ("Serie emprestado no dia "+((Serie) item).getDataEmprestimoAtual()+" por "+((Serie) item).getDataEmprestimo()+"dias\n");
        }
        else if(item instanceof Filme){
            if(((Filme) item).getDataEmprestimoAtual() != null) return ("Filme emprestado no dia "+((Filme) item).getDataEmprestimoAtual()+" por "+((Filme) item).getDataEmprestimo()+"dias\n");
        }
        return("Item não pode ser emprestado!");
    }
}