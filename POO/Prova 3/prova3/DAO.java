package prova3;

/**
 * @author Vinicius Gasparini
 * Prova 3 | Questão 3
 */
import java.util.ArrayList;

public class DAO {
    
    ArrayList<Produto> produtos;
    
    public boolean adicionarProduto ( Produto p ) {
        for (Produto prod: produtos)
            if (prod.getCodigo() == p.getCodigo()) {
                prod.setQuantidade(prod.getQuantidade() + 1);
                return true;
            }
        return produtos.add( p );
    }
    
    public Produto consultarProduto( int cod ) {
        for (Produto prod: produtos)
            if (prod.getCodigo() == cod) return prod;
        return null;
    }    
}

