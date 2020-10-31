from class_assembly_line import Assembly_Line


class Factory:

    errors = 0
    closed = False

    def __init__(self, assembly_type, max_errors):
        self.line = Assembly_Line(assembly_type)
        self.name = self.line.type
        self.lines = [Assembly_Line(assembly_type) for lines in range(len(self.line))]
        self.status = [0 for lines in range(len(self.line))]
        self.produced = list()
        self.fails = list()
        self.serie_number = dict()
        self.max_errors = max_errors

    def __len__(self):
        return len(self.lines)

    def run(self, line, word, stop):
        if self.errors < self.max_errors and not self.closed:
            sucess, error = line.automaton.run_with_word(word, stop)
            if sucess:
                if error:
                    self.errors += 1
                if self.errors == self.max_errors:
                    self.closed = True
                self.serie_number[line.automaton.identifier] = 0
            else:
                self.errors += 1
                self.serie_number[line.automaton.identifier] = 1
        else:
            self.closed = True
        return

    def find_available(self):
        index = 0
        for busy in self.status:
            if busy == 0:
                return index
            index += 1
        return -1

    def set_busy(self, index):
        if index >= 0:
            self.status[index] = len(self.line.automaton)
            return
        return

    def update_status(self):
        for busy in range(len(self.status)):
            if self.status[busy]:
                self.status[busy] -= 1
            self.produced.append(self.lines[busy].automaton.output)
            self.lines[busy].automaton.output = ""

    def count_busy(self):
        count = 0
        for busy in self.status:
            if busy:
                count += 1
        return count

    def count_produced(self):
        sucess = list()
        count = 0
        for output in self.produced:
            if output:
                if "s" in output:
                    sucess.append(output)
                    count += 1
                elif output:
                    self.fails.append(output)
        self.produced = sucess
        return count, self.errors
