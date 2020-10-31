#ifndef BIB_HPP
#define BIB_HPP

#include "symb.hpp"

#include <bits/stdc++.h>
using namespace std;

struct Symb {
    string id;
    int    tipo, pos;
};

struct Instruction {
    int label;
    int inst;
    int p1, p2;
    string literal;
};

struct Function {
    string id;
    int tipoRetorno;
    int pos;
    int nParametros;
    int nStack;
    int nLocals;
    vector<struct Arg> listaParametros;
};

struct Arg {
    string id;
    int tipo;
    int pos;
};

struct Attr {
    int     tipo;
    int     label;
    string  id;
    string  literal;
    int     constante;
    double  fconstante;
    int     nParametros;
    vector<string>   listaIDs;
    vector<struct Arg>   listaParametros;
    vector<struct Instruction>   listav;
    vector<struct Instruction> listaf;
};

void init_boollist(vector<Instruction> *v, vector<Instruction> *f);
void swap_boollist(vector<Instruction> *v, vector<Instruction> *f, vector<Instruction> *v_old, vector<Instruction> *f_old);

void add_symTable(vector<string> *l, int tipo);
void show_symTable();

void add_argfunc(vector<Arg> *lParam, int tipoRetorno, string id);
void add_emptyfunc(int tipoRetorno, string id);

void add_arglist(vector<Arg> *l, int tipo, string id);
void add_arg(vector<Arg> *l, int tipo);

void add_delimiter();
void update_func_id();

void gen_inst(int label, int inst, int p1, int p2, string str);
void gen_atrib(string var, int tipo1, int tipo2);
void gen_comp(int comp, int t1, int t2, int label);
void gen_goto();
void gen_gotoLabel(int label);
void gen_op(int comp);
void gen_read(int tipo, int pos);
void gen_func_call(string id);
void gen_func_callarg(string id, vector<Arg> *l);
void gen_return(int tipo);
void stack_int(int num);
// void stack_float(float num);
void stack_string(string str);
void corrigir_label(vector<Instruction> *l, int label);
void corrigirStack_e_Local();
void merge(vector<Instruction> *l_dest, vector<Instruction> *l1, vector<Instruction> *l2);
void merge2(vector<Instruction> *l_dest, vector<Instruction> *l1);
int new_label();
void stack_intvar(string id);
// void stack_floatvar(string id);
void stack_stringvar(string id);
void gen_print();
void invokeStatic(int TIPO);
int get_type(string id);
int get_pos(string id);
int get_func_type(string id);
void gen_file();
void error();
void incrementaStack(int i);
void decrementaStack(int i);

void dump_inst();
void dump_func();

#endif
