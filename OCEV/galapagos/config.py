from ast import literal_eval
import re
import os
import sys


def get_dimention() -> dict:
    dim_regex = r"(?i)DIM\ *=\ *([0-9]*)\ *\n"

    dim_parsed = re.findall(dim_regex, file)
    if not dim_parsed:
        raise Exception("Parser", "Dimention not found")

    os.environ["DIM"] = dim_parsed[0]

    return dict(chromosome_size=int(dim_parsed[0]))


def get_number_generations() -> dict:
    gen_regex = r"(?i)GEN\ *=\ *([0-9]*)\ *\n"

    gen_parsed = re.findall(gen_regex, file)
    if not gen_parsed:
        raise Exception("Parser", "Number of generations not found")

    os.environ["GEN"] = gen_parsed[0]

    return dict(chromosome_size=int(gen_parsed[0]))


def get_population() -> dict:
    pop_regex = r"(?i)POP\ *=\ *([0-9]*)\ *\n"

    pop_parsed = re.findall(pop_regex, file)
    if not pop_parsed:
        raise Exception("Parser", "Population not found")

    os.environ["POP"] = pop_parsed[0]

    return dict(population_size=int(pop_parsed[0]))


def get_cicles() -> dict:
    run_regex = r"(?i)RUN\ *=\ *([0-9]*)\ *\n"

    run_parsed = re.findall(run_regex, file)
    if not run_parsed:
        raise Exception("Parser", "RUN not found")

    os.environ["RUN"] = run_parsed[0]

    return dict(cicles=int(run_parsed[0]))


def get_codification() -> dict:
    cod_regex = r"(?i)COD\ *=\ *([A-Za-z\_]+)(?:\ *(?:\ *-\ *bounds\ *)?\ *=?\ *\[(\ *-?[0-9]+\.?[0-9]*)\ *\,\ *-?([0-9]+\.?[0-9]*)\ *\])?\ *\n"

    cod_parsed = re.findall(cod_regex, file)
    if not cod_parsed:
        raise Exception("Parser", "Codification not found")

    key = str(cod_parsed[0][0])
    low, high = None, None
    if cod_parsed[0][1]:
        low = int(cod_parsed[0][1])
        high = int(cod_parsed[0][2])

    os.environ["COD"] = cod_parsed[0][0]
    os.environ["LOW"] = cod_parsed[0][1] if cod_parsed[0][1] != "" else "0"
    os.environ["HIGH"] = cod_parsed[0][2] if cod_parsed[0][2] != "" else "10"

    return dict(key=key, low=low, high=high)


def get_operator_probability() -> dict:
    pc = re.findall(r"(?i)(PC)\ *=\ *([0-9]+\.?[0-9]*)\ *", file)
    pm = re.findall(r"(?i)(PM)\ *=\ *([0-9]+\.?[0-9]*)\ *", file)

    if not pc:
        raise Exception("Parser", "PC not found")
    if not pm:
        raise Exception("Parser", "PM not found")

    os.environ["PC"] = pc[0][1]
    os.environ["PM"] = pm[0][1]


def get_elitism() -> dict:
    el = re.findall(r"(?i)(EL)\ *=\ *(true|false)\ *", file)

    if not el:
        raise Exception("Parser", "Elitism not found")

    os.environ["EL"] = el[0][1]


def parse(path: str) -> dict:
    global file
    os.environ["GA_TITLE"] = sys.argv[0][:-3:]
    os.environ["OUT_PATH"] = "out/"

    file = open(path, "r").read()
    get_dimention()
    get_population()
    get_cicles()
    get_codification()
    get_number_generations()
    get_operator_probability()
    get_elitism()
