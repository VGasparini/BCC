class DFA:

    current_state = None
    current_letter = None
    valid = True

    def __init__(
        self, name, alphabet, states, delta_function, start_state, final_states
    ):
        self.name = name
        self.alphabet = alphabet
        self.states = states
        self.delta_function = delta_function
        self.start_state = start_state
        self.final_states = final_states
        self.current_state = start_state
        self.output = ""

    def transition_to_state_with_input(self, letter):
        if self.valid:
            if (self.current_state, letter) not in self.delta_function.keys():
                self.valid = False
                return
            self.current_state = self.delta_function[(self.current_state, letter)]
            self.current_letter = letter
            self.output += letter
        else:
            return

    def in_accept_state(self):
        return self.current_state in self.final_states and self.valid

    def go_to_initial_state(self):
        self.current_state = self.start_state

    def get_output(self):
        if type(self.output) == type(""):
            self.output = self.output.split(";")[:-1]
        return self.output

    def run_with_word(self, word):
        self.go_to_initial_state()
        for letter in word:
            self.transition_to_state_with_input(letter)
            continue
        return self.in_accept_state()

    def run_with_letters(self, word):
        self.go_to_initial_state()
        for letter in word:
            if self.run_with_letter(letter):
                return
            else:
                return

    def run_with_letter(self, letter):
        self.transition_to_state_with_input(letter)
        return self.current_state

    def __len__(self):
        return len(self.states)
