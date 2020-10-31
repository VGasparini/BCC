package prova2q1;

import java.text.DecimalFormat;

/**
 * Prova 2 - Dia 15/10 - Questão 1
 * @author gasparini
 * @param <N> Objeto genérico que extends Number (garantia de númerico)
 */

public class Fracao <N extends Number>{
    
    private N num;
    private N den;
    
    /**
     * Construtor da Fracao genérico do tipo Number
     * @param num 
     * @param den
     * @throws ArithmeticException quando esta sendo criado uma fração com
     * denominador igual a 0
     */
    
    Fracao(N num,N den) throws ArithmeticException {
        this.num = num;
        if(den.intValue()==0) throw new ArithmeticException("Denominador igual a 0");
        else this.den = den;
    }
    
    /**
     * @return Retorna o numerador
     */
    
    public N getNum() {
        return num;
    }

    /**
     * @param num Define o numerador
     */
    
    public void setNum(N num) {
        this.num = num;
    }

    /**
     * @return Retorna o denominador
     */
    
    public N getDen() {
        return den;
    }

    /**
     * @param den Define o denominador
     */
    
    public void setDen(N den) {
        this.den = den;
    }
    
    /**
     * @return Método toString retorna a fração no formato num / den
     * com 4 casas decimais
     */
    
    public String toString(){
        DecimalFormat df = new DecimalFormat("#.####");
        String n = df.format(getNum());
        String d = df.format(getDen());
        return (n+" / "+d);
    }
    
    /**
     * @return Método sqrt retorna um objeto do tipo Fracao que descreve a raiz
     * quadrada do instância
     */
    
    public Fracao sqrt(){
        if(this.den.intValue()<0 || this.num.intValue()<0) throw new InvalidSquareRootException();
        else{
            Fracao tmp = new Fracao(Math.sqrt(this.num.doubleValue()),Math.sqrt(this.den.doubleValue()));
            return tmp;
        }
    }
    
}