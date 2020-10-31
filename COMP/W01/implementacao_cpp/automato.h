#include "header.h"

class delta_function{
private:
    mpscs transitions;
public:
    delta_function();
    void add_delta_function(string s1, string s2, char k);
    mpscs get_transitions();
};

class automato{
private:
	string name;
	vs states;
	vs alphabet;
	ss final_states;
	delta_function delta;
	string start_state;
	string current_state;
	char current_letter;
	bool valid;
public:
	automato(string n, vs s, vs a, vs fs, delta_function df, string sts);
    void transition_to_state_with_input(char l);
    bool in_accept_state();
    void go_to_initial_state();
    bool run_with_word(string w);
    void run_with_letters(string w);
    int len();
};
