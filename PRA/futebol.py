import os
import random as r
import time as t
import operator


class partida(object):
    def __init__(self, id, teamA, scoreA, teamB, scoreB, dates, public, locality):
        self.id = id
        self.teamA = teamA
        self.scoreA = scoreA
        self.teamB = teamB
        self.scoreB = scoreB
        self.dates = dates
        self.public = public
        self.locality = locality

    def __str__(self):
        return "#{:10} - {};{};{};{};{};{};{}".format(
            str(self.id).zfill(10),
            self.teamA,
            self.scoreA,
            self.teamB,
            self.scoreB,
            self.dates,
            self.public,
            self.locality,
        )


def date():
    """
    This function generate a random date in brazilian format, dd/mm/yyyy
    Days range: 1-30
    Months range: 1-12
    Years range: 2015-2018
    """
    return str(
        str(r.randint(1, 30)).zfill(2)
        + "/"
        + str(r.randint(1, 12)).zfill(2)
        + "/"
        + str(r.randint(2015, 2018))
    )


def match():
    """
    This function simulates a random match using @names, date, random audience and @local
    """
    return (
        names[r.randrange(len(names))]
        + ";"
        + str(r.randrange(9))
        + ";"
        + names[r.randrange(len(names))]
        + ";"
        + str(r.randrange(9))
        + ";"
        + date()
        + ";"
        + str(r.randrange(1000, 80000))
        + ";"
        + local[r.randrange(len(local))]
        + "\n"
    )


def convert_size(num, unit):
    """
    This function is used to convert data size typed into bytes
    """
    return int(num) * (1024 ** (["bytes", "KB", "MB", "GB"].index(unit)))


def createBySize(path, limit):
    """
    This function generates a file until size @limit is reached
    """
    limit //= 51
    f = open(path, "w")
    for instance in range(limit):
        f.write(match())
    f.close()


def createByInstances(path, limit):
    """
    This function generates a file until instances @limit is reached
    """
    f = open(path, "w")
    for instance in range(limit):
        f.write(match())
    f.close()


def readFile(path):
    teamA, scoreA, teamB, scoreB, dates, public, locality = [], [], [], [], [], [], []
    f = open(path, "r")
    id, data = 1, []
    for line in f.readlines():
        teamA, scoreA, teamB, scoreB, dates, public, locality = line.split(";")
        data.append(partida(id, teamA, scoreA, teamB, scoreB, dates, public, locality))
        id += 1
    return data


names = ["Real Madrid", "Barcelona", "PSG", "Liverpool", "JEC"]
local = [
    "Santiago Bernabeu",
    "Camp Nou",
    "Parc des Princes",
    "Anfield",
    "Arena Joinville",
]
path = "data.txt"


op = input(
    "Selecione modo de funcionamento\n----------\n\n1 - Limitar por tamanho\n2 - Limitar por partida(s)\n3 - Imprimir na tela\n4 - Sort\n\n-> "
)
if op == "1":
    size, unit = input("Informe o tamanho desejado (Bytes, KB, MB ou GB)\n ->").split()
    ini = t.time()
    createBySize(path, convert_size(size, unit))
    print("Tempo de execucao: {:.4f}".format(t.time() - ini))
elif op == "2":
    instances = int(input("Informe a quantidade de instancias\n ->"))
    ini = t.time()
    createByInstances(path, instances)
    print("Tempo de execucao: {:.4f}".format(t.time() - ini))
elif op == "3":
    ini = t.time()
    data = readFile(path)
    for instance in data:
        print(instance)
    print("Tempo de execucao: {:.4f}".format(t.time() - ini))
elif op == "4":
    ini = t.time()
    data = readFile(path)
    keys = "scoreB"
    data.sort(key=operator.attrgetter(keys))
    print("Tempo de execucao: {:.4f}".format(t.time() - ini))
