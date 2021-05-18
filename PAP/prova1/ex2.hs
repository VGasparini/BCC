-- Exercicio 2

verificaImpar :: Int -> Bool
verificaImpar n = (n `mod` 2) == 1

verificaPar :: Int -> Bool
verificaPar n = (n `mod` 2) == 0

filtrar :: (a -> Bool) -> [a] -> [a]
-- Caso base
filtrar _ [] = []
-- Recursao
filtrar a (x : xs)
  | a x = x : filtrar a xs
  | otherwise = filtrar a xs