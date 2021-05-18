primeiro :: (a -> Bool) -> [a] -> Maybe a
primeiro f [] = Nothing
primeiro f (x : xs) = if f x then Just x else primeiro f xs