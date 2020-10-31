#include "includes.h"

automato::automato(string n, vs s, vs a, vs fs, delta_function df, string sts){
	name = n;
	states = s;
	alphabet = a;
	for (int i = 0; i < fs.size(); i++){
		final_states.insert(fs[i]);
	}
	delta = df;
	start_state = sts;
	current_state = sts;
	valid = true;
	current_letter = '\0';
}

void automato::transition_to_state_with_input(char l){
	if (valid){
		if (delta.get_transitions().find(psc (current_state, l)) == delta.get_transitions().end()){
			valid = false;
			return;
		}
		current_state = delta.get_transitions().at(psc (current_state,l));
		current_letter = l;
	}
}

bool automato::in_accept_state(){
	if (valid && final_states.find(current_state) != final_states.end()) return true;
	return false;
}

void automato::go_to_initial_state(){
	current_state = start_state;
	valid = true;
}

bool automato::run_with_word(string w){
	go_to_initial_state();
	for (int i = 0; i < w.size(); i++){
		transition_to_state_with_input(w[i]);
	}
	return in_accept_state();
}

void automato::run_with_letters(string w){
	go_to_initial_state();
	for (int i = 0; i < w.size(); i++){
		transition_to_state_with_input(w[i]);
	}
}

int automato::len(){
	return states.size();
}
