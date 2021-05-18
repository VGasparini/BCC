concatena :: [a] -> [a] -> [a]
concatena [] ys = ys
concatena (x : xs) ys = x : concatena xs ys

concatena [1, 2, 3] [7, 8]

-- concatena 1 [2,3] [7,8]
-- concatena 1 2 [3] [7,8]
-- concatena 1 2 3 [] [7,8]
-- concatena [1,2,3,7,8]
