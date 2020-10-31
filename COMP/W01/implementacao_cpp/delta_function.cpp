#include "includes.h"

delta_function::delta_function(){
    transitions = mpscs ();
}

void delta_function::add_delta_function(string s1, string s2, char k){
    transitions.insert(pscs (psc (s1,k), s2));
}

mpscs delta_function::get_transitions(){
    return transitions;
}
