from random import randint as rand
from utils import export_graph, export_error
import time as t


class Moore:

    identifier = ""
    current_state = None
    current_letter = None
    valid = True

    def __init__(
        self,
        name,
        alphabet,
        states,
        delta_function,
        start_state,
        final_states,
        output_alphabet,
        output_funtion,
        confiability,
        capacity,
    ):
        self.name = name
        self.alphabet = alphabet
        self.states = states
        self.delta_function = delta_function
        self.start_state = start_state
        self.final_states = final_states
        self.current_state = start_state
        self.output_alphabet = output_alphabet
        self.output_funtion = output_funtion
        self.confiability = confiability
        self.capacity = capacity
        self.output = ""

    def __len__(self):
        return len(self.states)

    def __str__(self):
        return self.output

    def transition_to_state_with_input(self, letter, stop):
        if self.valid:
            if (self.current_state, letter) not in self.delta_function.keys():
                self.valid = False
                return
            if rand(0, self.confiability % 100) == 1:
                if self.current_state == self.start_state:
                    self.output += "f"
                    self.current_state = self.delta_function[(self.current_state, "e")]
                    export_graph(
                        self.name + "#" + self.identifier + "-" + self.current_state,
                        self,
                    )
                else:
                    self.output += "e"
                    tmp = self.delta_function[(self.current_state, "e")]
                    export_error(
                        self.name + "#" + self.identifier + "-" + tmp, self, tmp
                    )
                return "e"
            t.sleep(stop)
            export_graph(
                self.name + "#" + self.identifier + "-" + self.current_state, self
            )
            self.current_letter = letter
            self.output += self.output_funtion[self.current_state]
            self.current_state = self.delta_function[(self.current_state, letter)]
        else:
            return

    def in_accept_state(self):
        export_graph(self.name + "#" + self.identifier + "-" + self.current_state, self)
        if self.current_state in self.final_states and self.valid:
            self.output += self.output_funtion[self.current_state]
            return True
        self.output += self.output_funtion[self.current_state]
        return False

    def go_to_initial_state(self):
        self.current_state = self.start_state

    def run_with_word(self, word, stop):
        self.identifier = str(abs(int(hash(word) / 1e15) + rand(1, 1000)))
        self.go_to_initial_state()
        for letter in word:
            e = self.transition_to_state_with_input(letter, stop)
            if e == "e":
                self.transition_to_state_with_input(letter, stop)
        return self.in_accept_state(), "e" in self.output
