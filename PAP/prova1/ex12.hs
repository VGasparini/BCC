-- Exercicio 12

maiorElemento :: Ord a => [a] -> a
-- Caso base
maiorElemento [x] = x
-- Recursao
maiorElemento (x : y : xs)
  | x > y = maiorElemento (x : xs)
  | otherwise = maiorElemento (y : xs)
maiorElemento [] = error "A lista precisa conter ao menos um elemento"
