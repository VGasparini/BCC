#include "includes.h"

automato read_quintuple_from_data(){
    string l, aux, aux2, start_state;
    char c;
    vs alphabet, states, final_states;
    delta_function delta;
    ifstream f ("in");
    l = "\0";
    getline(f,l);
    string name = l;
    l = "\0";
    getline(f,l);
    for (int i = 0; i < l.size(); i++){
        aux = "";
        while (l[i] != ' ' && l[i] != '\n' && l[i] != '\000'){
            aux+=l[i];
            i++;
        }
        alphabet.pb(aux);
    }
    l = "\0";
    getline(f,l);
    for (int i = 0; i < l.size(); i++){
        aux = "";
        while (l[i] != ' ' && l[i] != '\n' && l[i] != '\000'){
            aux+=l[i];
            i++;
        }
        states.pb(aux);
    }
    int number_transitions;
    f>>number_transitions;
    getline(f,l);
    for (int i = 0; i < number_transitions; i++){
        l = "\0";
        getline(f,l);
        aux = "";
        int j = 0;
        while (l[j] != '-'){
            aux+=l[j];
            j++;
        }
        j += 2;
        aux2 = "";
        while (l[j] != ':'){
            aux2+=l[j];
            j++;
        }
        c = l[j+1];
        delta.add_delta_function(aux,aux2,c);
    }
    l = "\0";
    getline(f,l);
    start_state = l;
    l = "\0";
    getline(f,l);
    for (int i = 0; i < l.size(); i++){
        aux = "";
        while (l[i] != ' ' && l[i] != '\n' && l[i] != '\000'){
            aux+=l[i];
            i++;
        }
        final_states.pb(aux);
    }
    return automato(name,states,alphabet,final_states,delta,start_state);
}

void printa(){
    cout << "teste" << endl;
}
