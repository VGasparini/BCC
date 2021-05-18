-- Exercicio 1
concatenacao :: [a] -> [a] -> [a]
-- base
concatenacao [] ys = ys
-- recursivo
concatenacao (x : xs) ys =
  x : concatenacao xs ys

-- Exercicio 2
pertence :: Eq a => a -> [a] -> Bool
-- base
pertence x [] = False
-- recursivo
pertence x (y : ys) =
  (x == y) || pertence x ys

-- Exercicio 3
intersecao :: Eq a => [a] -> [a] -> [a]
-- base
intersecao x [] = []
intersecao [] y = []
-- recursivo
intersecao (x : xs) y =
  if pertence x y then x : intersecao xs y else intersecao xs y

-- Exercicio 4
inverso :: [a] -> [a]
-- base
inverso [] = []
-- recursivo
inverso (x : xs) =
  concatenacao (inverso xs) [x]

-- Exercicio 5
primeiros :: Int -> [a] -> [a]
-- base
primeiros n [] = []
primeiros 0 _ = []
-- recursivo
primeiros n (x : xs) =
  x : primeiros (n -1) xs

-- Exercicio 6
ultimos :: Int -> [a] -> [a]
-- base
ultimos n [] = []
ultimos 0 _ = []
-- recursivo
ultimos n x =
  inverso (primeiros n (inverso x))

-- Exercicio 7
tam :: String -> Int
tam [] = 0
tam (x : xs) = 1 + tam xs

binParaInt :: String -> Int
-- base
binParaInt "0" = 0
binParaInt "1" = 1
-- recursivo
binParaInt ('0' : xs) =
  binParaInt xs
binParaInt ('1' : xs) =
  2 ^ tam xs + binParaInt xs
binParaInt xs =
  error "Valor nao é binario"

-- Exercicio 8
intParaBin :: Int -> String
-- base
intParaBin 0 = "0"
intParaBin 1 = "1"
intParaBin n
  | mod n 2 == 0 = concatenacao (intParaBin (div n 2)) "0"
  | otherwise = concatenacao (intParaBin (div n 2)) "1"

-- Exercicio 9
menorValor :: Ord a => [a] -> a
-- base
menorValor [x] = x
-- recursivo
menorValor (x:y:xs)
  | x < y = menorValor $ x:xs
  | otherwise = menorValor $ y:xs
-- erro
menorValor [] = error "Lista nao pode ser vazia"

-- Exercicio 10
removerPrimeiro :: Eq a => [a] -> a -> [a]
-- base
removerPrimeiro [] _ = []
-- recursivo
removerPrimeiro (x : xs) y
  | x == y = xs
  | otherwise = concatenacao [x] (removerPrimeiro xs y)

-- Exercicio 11
ordenar :: Ord a => [a] -> [a]
-- base
ordenar [x] = [x]
-- recursivo
ordenar xs =
  menorValor xs : ordenar (removerPrimeiro xs (menorValor xs))

-- Exercicio 12
dobrar_dir :: (a -> b -> b) -> b -> [a] -> b
-- base
dobrar_dir f t [] = t 
-- recursivo
dobrar_dir f t (x:xs) = f x (dobrar_dir f t xs)

-- Exercicio 13
dobrar_esq :: (b -> a -> b) -> b -> [a] -> b
-- base
dobrar_esq f t [] = t 
-- recursivo
dobrar_esq f t (x:xs) = dobrar_esq f (f t x) xs

-- Exercicio 14
filtrar :: (a -> Bool) -> [a] -> [a]
-- base
filtrar _ [] = []
-- recursivo
filtrar f (x:xs)
  | f x = x : filtrar f xs
  | otherwise = filtrar f xs

-- Exercicio 15
impares :: [Int] -> [Int]
impares y = filtrar (\x -> x `mod` 2 == 1) y

-- Exercicio 16
mapear :: (a -> b) -> [a] -> [b]
-- base
mapear _ [] = []
-- recursivo
mapear f (x:xs) = (f x) : mapear f xs

-- Exercicio 17
primeiro :: (a, b) -> a
primeiro (x, y) = x

primeiros_ :: [(a, b)] -> [a]
primeiros_ x = mapear primeiro x

-- Exercicio 18
todos :: [Bool] -> Bool
-- and = foldr (&&) True
todos x = dobrar_esq (&&) True x

-- Exercicio 19
-- Tipos
data Tree a = Leaf a
  | Branch (Tree a) (Tree a)

maior :: Ord a => Tree a -> a
maior (Leaf x) = x
maior (Branch x y)
  | maior_x > maior_y = maior_x
  | otherwise = maior_y
  where maior_x = maior x
        maior_y = maior y

-- Exercicio 20
altura :: Tree a -> Int
-- base
altura (Leaf x) = 0
-- recursivo
altura (Branch x y) = 1 + max (altura x) (altura y) 