# Encontrar raizes

## Provar que existe raiz entre [a,b]

Teorema de Bolzano
Se f(a)*f(b) < 0, então existe pelo menos uma raiz [a,b]

## Método da Bisseção

Passo a passo

* Encontrar um intervalo [a,b] tal que f(a)*f(b) < 0
* Diminui o intervalo. p0 = (a+b)/2
* Testa se este ponto é agora a ou b.
** f(p0)*f(b) < 0
** f(a)*f(p0) < 0

Número de iterações
`n >= ( ln(b-a) - ln(E) ) / ln(2)`

## Método de Newton

`Xn+1 = Xn - (f(Xn) / f'(Xn))`

Converge se f'(x0) != 0 

f(Xn) = 0 quando f'(Xn) != 0 e |Xn-x0|< E

## Método das Secantes

`Xn+1 = Xn - f(Xn)*( (Xn - Xn-1) / ((f(Xn) - f(Xn-1))) )`

Este método precisa de dois chutes inicias (Xn e Xn-1)

## Método do Posição Falsa

`X = (a f(b) - b f(a)) / (f(b) - f(a))`

Testa-se Bolzano com X sendo a ou b
Pega o menor e usa como novo a/b

Parada com Erro
b-a < E
|f(a)| < E
|f(b)| < E

## Método do Ponto Fixo

Dado a função, existirá ponto fixo se g([a,b]) C [a,b] e g(x) é continua
Unicidade se |g'(x)| < L e 0<L<1

Número de iterações `n >= ( -ln(|p2-p1| / 1-L)  + ln E) / ln(L)`
Passo a passo

* Encontrar f(x) = 0 e chamar de g(x)
* Testar se g([a,b]) C [a,b]
* Se passar, só aplicar recursivamente em g(x)
