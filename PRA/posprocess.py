#!/usr/bin/env python
# -*- coding: utf-8 -*-

arq = open("data_sorted.txt", "r")
fim = open("data.txt", "w+")
t = []
sep = ";"
cont = 1
for line in arq:
    t = line.split(";")
    t[0] = str(cont).zfill(18)
    cont += 69
    fim.write(sep.join(t))
