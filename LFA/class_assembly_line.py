from utils import *
from class_moore import Moore


class Assembly_Line:
    def __init__(self, assembly_type):
        self.automaton = Moore(*read_7_tuple_from_data(assembly_type))
        self.type = self.automaton.name

    def __len__(self):
        return self.automaton.capacity

    def __str__(self):
        return str(self.automaton.output)
