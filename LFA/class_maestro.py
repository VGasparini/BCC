from utils import header, nickname


class Maestro:

    nicks = nickname("nickname")
    time = 0

    def __init__(self, factory_list):
        self.factory_list = factory_list
        self.list_words = [[] for factory_type in self.factory_list]

    def set_words(self, words):
        for word in words:
            index = self.find_factory(word)
            self.list_words[index].append(word)

    def pooling(self, stop):
        controller, show = self.controller(True, True)
        while self.remaing_words():
            index = 0
            for words in self.list_words:
                for word in words:
                    factory = self.factory_list[index]
                    available = factory.find_available()
                    if available >= 0:
                        factory.set_busy(available)
                        line = factory.lines[factory.find_available()]
                        factory.run(line, word, stop)
                        self.update_factories()
                        words.pop(0)
                        if show:
                            print("Mandando o carro {}".format(word))
                        if controller:
                            controller, show = self.controller(False, show)
                        break
                    else:
                        self.update_factories()
                        break
                index += 1
                self.time += 1
        for factory in self.factory_list:
            while factory.count_busy():
                self.update_factories()
                self.time += 1

    def find_factory(self, word):
        index = 0
        for factory in self.factory_list:
            if word.startswith(factory.name):
                return index
            index += 1

    def update_factories(self):
        for factory in self.factory_list:
            factory.update_status()

    def remaing_words(self):
        for words in self.list_words:
            if len(words) > 0:
                return True
        return False

    def controller(self, menu, show):
        if menu:
            stop = (
                ord(
                    input(
                        "Deseja (a)vançar passo a passo as entradas nas linhas ou acelerar ao (f)inal?\n(a ou f)->"
                    )
                )
                % 2
            )
            show = (
                ord(input("Deseja acompanhar as entradas na linha? (s ou n)\n ->")) % 2
            )
        else:
            stop = ord(input("(a ou f) ->")) % 2
        return stop, show

    def statistics(self):
        header("Estatisticas")
        print("Tempo de execução {} ticks".format(self.time))
        ans = ""
        for factory in self.factory_list:
            count, errors = factory.count_produced()
            ans += "Linha {}\n  Carros produzidos = {}\n  Erros = {}\n".format(
                self.nicks[factory.name], count, errors
            )
            if factory.closed:
                ans += "Linha parou devido excesso de falhas\n\n"
        print(ans)
        op = ord(input("\nDeseja olhar as fitas?\n(s ou n) ->")) % 2
        if op:
            header("Fitas")
            for factory in self.factory_list:
                print("\nLinha", self.nicks[factory.name])
                print("  Produzidos")
                index = 1
                for produced in factory.produced:
                    print(" " * 3, index, "->", produced)
                    index += 1
                index = 1
                print("  Falhas fatais ({})".format(len(factory.fails)))
                for fails in factory.fails:
                    print(" " * 3, index, "->", fails)
                    index += 1
