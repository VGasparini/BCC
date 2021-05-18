-- equivalente a fmap
mapear :: (a -> b) -> [a] -> [b]
mapear _ [] = []
mapear f (x:xs) = (f x) : mapear f xs

converte :: [Int] -> [String]
converte [] = []
converte x = mapear show x