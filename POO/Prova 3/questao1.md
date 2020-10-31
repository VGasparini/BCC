# Polimorfismo Adhoc
O polimorfismo Adhoc pode ser entendido como polimorfismo aparente, pois é explicito as condições polimórficas.
Funciona criando abstrações que operam sobre cada tipo abrangido por tal.

## Polimorfismo Adhoc de sobrecarga
O polimorfismo de sobrecarga permite que funções possam ser usadas para dois ou mais fins diferentes, desde que tenham o mesmo nome.
Funciona tanto para operadores(c++) quanto para funções/métodos(c++ e java).
Exemplo:

  int + float;
  int + int;

Nesse exemplo, o operador + atua de maneira polimórfica, atuando tanto com int,int quanto com int,float.

# Polimorfismo Universal
O polimorfismo Universal permite que uma função/método possa executar sobre elementos de diferentes tipos.

## Polimorfismo Universal paramétrico
O polimorfismo paramétrico é descrito quando há uma parametrização dos dados e funções em relação ao tipo de elementos sobre o qual operam.
Funciona gerando um dado genérico que pode ser utilizado por diversos tipos ou classes.
Exemplo:

  generic quadrado(objeto)

Nesse exemplo o método quadrado retorna o quadrado de um float, int, double. De acordo com o contexto, ele corresponderá a este.
