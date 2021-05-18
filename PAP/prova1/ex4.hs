-- Exercicio 4

ultimoElemento :: [a] -> a
-- Caso base
ultimoElemento [x] = x
-- Recursao
ultimoElemento (x : xs) = ultimoElemento xs
-- Erro
ultimoElemento [] = error "A lista precisa conter ao menos um elemento"