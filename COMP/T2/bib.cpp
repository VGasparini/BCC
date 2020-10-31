#include "bib.hpp"

vector<Symb>            tabelaSimbolos;
deque<Instruction>     listaInstrucoes;
vector<Function>        listaFuncoes;

int pos_count = 0;
int label_count = 0;
int inst_count = 0;
int func_count = 0;
int arg_count = 0;

int contStackSize = 0;
int maiorStackSize = 0; 

int MAX_STACK = 15;
int MAX_LOCALS = 15;

string nomeClasse;
ofstream outputFile;

void init_boollist(vector<Instruction> *v, vector<Instruction> *f){
    int next_pos = inst_count + 1;
    struct Instruction iv;
    struct Instruction iff;
    iv.label = inst_count;
    iff.label = next_pos;
    v->push_back(iv);
    f->push_back(iff);
}

void add_symTable(vector<string> *l, int tipo){
    
    string info;
    reverse(l->begin(),l->end());
    while(!l->empty()){
        struct Symb s;
        s.id   = l->back();
        s.tipo = tipo;
        l->pop_back();

        for(auto i:tabelaSimbolos){
            if(i.id == s.id){
                cout << "ID " << info << " ja existe na tabela de simbolos!" << endl;
                exit(-1);
            }
        }
        
        s.pos = pos_count++;

        tabelaSimbolos.push_back(s);
    }
}


void add_argfunc(vector<struct Arg> *lParam, int tipoRetorno, string id){
    struct Function f;
    f.id = id;
    f.tipoRetorno = tipoRetorno;
    f.pos = func_count;
    f.nParametros = arg_count;
    for( auto i:*lParam){
        f.listaParametros.push_back(i);
    }
    listaFuncoes.push_back(f);
    arg_count = 0;
    func_count++;
}

void add_emptyfunc(int tipoRetorno, string id){
    struct Function f;
    f.id = id;
    f.tipoRetorno = tipoRetorno;
    f.pos = func_count;
    f.nParametros = arg_count;
    f.nStack = maiorStackSize;
    listaFuncoes.push_back(f);
    arg_count = 0;
    func_count++;
}

void add_arglist(vector<Arg> *l, int tipo, string id){
    struct Arg p;
    p.tipo = tipo;
    p.pos = arg_count;
    p.id = id;
    l->push_back(p);
    arg_count++;

    struct Symb s;
    s.id = id;
    s.tipo = tipo;
    s.pos = pos_count;
    tabelaSimbolos.push_back(s);
    pos_count++;
}

void add_arg(vector<Arg> *l, int tipo){
    struct Arg p;
    p.tipo = tipo;
    l->push_back(p);
}

void add_delimiter(){
    gen_inst(NULO, INST_DELIMITADORFUNC, NULO, NULO, NULO_STR);
    tabelaSimbolos.clear();
}

void gen_inst(int label, int inst, int p1, int p2, string str){
    struct Instruction i;
    i.label = label;
    i.inst = inst;
    i.p1 = p1;
    i.p2 = p2;
    i.literal = str;

    listaInstrucoes.push_back(i);

    inst_count++;
}

void gen_atrib(string var, int tipo1, int tipo2){
    decrementaStack(1);

    if (tipo1 == tipo2){
        if (tipo1 == TIPO_INT)
            gen_inst(NULO, INST_ISTORE, get_pos(var), NULO, NULO_STR);
        // else if (tipo1 == TIPO_INT)
        //     gen_inst(NULO, INST_FSTORE, get_pos(var), NULO, NULO_STR); arrumar
        else
            gen_inst(NULO, INST_ASTORE, get_pos(var), NULO, NULO_STR);
    }
    else
    {
        cout << "Erro na atribuicao da variavel " << var << endl;
        exit(-1);
    }
}

void gen_comp(int comp, int t1, int t2, int label){
    if (t1 != TIPO_INT || t2 != TIPO_INT){
        cout << "Comparacao entre variaveis com tipos distintos" << endl;
        exit(-1);
    }

    decrementaStack(2);

    switch(comp){
        case CMP_EQUAL:
            gen_inst(label, INST_IF_ICMPEQ, NULO, NULO, NULO_STR); break;
        case CMP_NEQUAL:
            gen_inst(label, INST_IF_ICMPNE, NULO, NULO, NULO_STR); break;
        case CMP_LTHAN:
            gen_inst(label, INST_IF_ICMPLT, NULO, NULO, NULO_STR); break;
        case CMP_LEQUAL:
            gen_inst(label, INST_IF_ICMPLE, NULO, NULO, NULO_STR); break;
        case CMP_GTHAN:
            gen_inst(label, INST_IF_ICMPGT, NULO, NULO, NULO_STR); break;
        case CMP_GEQUAL:
            gen_inst(label, INST_IF_ICMPGE, NULO, NULO, NULO_STR); break;
        default:
            exit(-1);
    }

}

void gen_goto(){
    gen_inst(NULO, INST_GOTO, NULO, NULO, NULO_STR);
}

void gen_gotoLabel(int label){
    gen_inst(label, INST_GOTO, NULO, NULO, NULO_STR);
}

void gen_op(int comp){
    decrementaStack(1);

    switch(comp){
        case OP_ADD:
            gen_inst(NULO, INST_IADD, NULO, NULO, NULO_STR); break;
        case OP_SUB:
            gen_inst(NULO, INST_ISUB, NULO, NULO, NULO_STR); break;
        case OP_DIV:
            gen_inst(NULO, INST_IDIV, NULO, NULO, NULO_STR); break;
        case OP_MUL:
            gen_inst(NULO, INST_IMUL, NULO, NULO, NULO_STR); break;

    }
}

void gen_read(int tipo, int pos){
    incrementaStack(3);

    gen_inst(NULO, INST_NEWSCANNER, NULO, NULO, NULO_STR);
    gen_inst(NULO, INST_DUP, NULO, NULO, NULO_STR);
    gen_inst(NULO, INST_GETINPUTSTREAM, NULO, NULO, NULO_STR);
    gen_inst(NULO, INST_INVOKEINPUTSTR, NULO, NULO, NULO_STR);
    if (tipo == TIPO_INT){
        gen_inst(NULO, INST_NEXTINT, NULO, NULO, NULO_STR);
        gen_inst(NULO, INST_ISTORE, pos, NULO, NULO_STR);
    }
    // else if (tipo == TIPO_FLOAT){
    //     gen_inst(NULO, INST_NEXTINT, NULO, NULO, NULO_STR);
    //     gen_inst(NULO, INST_ISTORE, pos, NULO, NULO_STR);    arrumar
    // } 
    else if (tipo == TIPO_STRING){
        gen_inst(NULO, INST_NEXTLINE, NULO, NULO, NULO_STR);
        gen_inst(NULO, INST_ASTORE, pos, NULO, NULO_STR);
    }

    decrementaStack(3);
}

void gen_func_call(string id){
    bool flag = false;
    for(auto i:listaFuncoes){
        if(i.id == id){
            flag = true;
            gen_inst(NULO, INST_INVOKESTATIC, i.pos, NULO, i.id);
            break;
        }
    }
    if(!flag){
        cout << "Erro na funcao '" << id << "'. Favor revisar sua declarada" << endl;
        exit(-1);
    }
}

void gen_func_callarg(string id, vector<Arg> *l){
    bool flag = false;
    for(auto i:listaFuncoes){
        if(i.id == id and i.nParametros == l->size()){
            flag = true;
            gen_inst(NULO, INST_INVOKESTATIC, i.pos, NULO, i.id);
            break;
        }
    }
    if(!flag){
        cout << "Erro na funcao '" << id << "'. Favor revisar argumentos" << endl;
        exit(-1);
    }
}

void gen_return(int tipo){
    if (tipo == TIPO_INT)
        gen_inst(NULO, INST_IRETURN, NULO, NULO, NULO_STR);
    // else if (tipo == TIPO_FLOAT)
    //     gen_inst(NULO, INST_ARETURN, NULO, NULO, NULO_STR); arrumar
    else if (tipo == TIPO_STRING)
        gen_inst(NULO, INST_ARETURN, NULO, NULO, NULO_STR);
    else
        gen_inst(NULO, INST_RETURN, NULO, NULO, NULO_STR);
}

void stack_int(int num){
    incrementaStack(1);
    gen_inst(NULO, INST_LDC, num, NULO, NULO_STR);
}

// void stack_float(float num){
//     incrementaStack(1);
//     gen_inst(NULO, INST_LDC, num, NULO, NULO_STR); arrumar
// }

void stack_string(string str){
    incrementaStack(1);
    gen_inst(NULO, INST_LDCSTRING, NULO, NULO, str);

}

void corrigir_label(vector<Instruction> *l, int label){
    for(auto i:*l){
        i.label = label;
    }
}

void update_func_id(){
    pos_count++;
}

void corrigirStack_e_Local(){
    if (listaFuncoes.size() > 0){
        listaFuncoes[listaFuncoes.size() - 1].nStack = maiorStackSize;
        listaFuncoes[listaFuncoes.size() - 1].nLocals = pos_count;
    } else {
        struct Function f;
        f.nStack = maiorStackSize;
        f.nLocals = pos_count;
        listaFuncoes.push_back(f);
    }
    pos_count = 0;
    maiorStackSize = 0;
    contStackSize = 0;
}

void merge(vector<Instruction> *l_dest, vector<Instruction> *l1, vector<Instruction> *l2){
    for(auto i:*l1){
        l_dest->push_back(i);
    }
    l1->clear();

    for(auto i:*l2){
        l_dest->push_back(i);
    }
    l2->clear();
}

void merge2(vector<Instruction> *l_dest, vector<Instruction> *l1){
    for(auto i:*l1){
        l_dest->push_back(i);
    }
    l1->clear();
}


int new_label(){
    label_count++;
    gen_inst(label_count, INST_NEWLABEL, NULO, NULO, NULO_STR);
    return label_count;
}

void stack_intvar(string id){
    incrementaStack(1);

    int pos = get_pos(id);

    gen_inst(NULO, INST_ILOAD, pos, NULO, NULO_STR);
}

void stack_stringvar(string id){
    incrementaStack(1);

    int pos = get_pos(id);

    gen_inst(NULO, INST_ALOAD, pos, NULO, NULO_STR);
}

void gen_print() {
    incrementaStack(1);
    gen_inst(NULO, INST_GETPRINT, NULO, NULO, NULO_STR);
}

void invokeStatic(int TIPO){
    decrementaStack(2);

    if (TIPO == TIPO_INT) 
        gen_inst(NULO, INST_INVOKEPRINT_INT, NULO, NULO, NULO_STR);
    // if (TIPO == TIPO_FLOAT) 
    //     gen_inst(NULO, INST_INVOKEPRINT_INT, NULO, NULO, NULO_STR); arrumar
    else if (TIPO == TIPO_STRING)
        gen_inst(NULO, INST_INVOKEPRINT_STR, NULO, NULO, NULO_STR);
}

int get_type(string id){
    for(auto i:tabelaSimbolos){
        if(id == i.id){
            return i.tipo;
        }
    }
    cout << "Uso da variavel '" << id << "' antes da declaracao" << endl;
    exit(-1);
}

int get_pos(string id){
    for(auto i:tabelaSimbolos){
        if(id == i.id){
            return i.pos;
        }
    }
    cout << "Uso da variavel '" << id << "' antes da declaracao" << endl;
    exit(-1);
}

int get_func_type(string id){
    for(auto i:listaFuncoes){
        if(id == i.id){
            return i.tipoRetorno;
        }
    }
    cout << "Uso da funcao '" << id << "' antes da declaracao" << endl;
    exit(-1);
}

void dump_inst(){
    cout << "--- Lista de Instrucoes ---" << endl;
    for (auto i : listaInstrucoes)
        cout << "label = " << i.label << " | inst = " << i.inst << " | p1 = " << i.p1 << " | p2 = " << i.p2 << " | literal = " << i.literal << endl;
}

void dump_func(){
    map<int, string> type2str = {
        {TIPO_INT, "int"},
        {TIPO_FLOAT, "float"},
        {TIPO_STRING, "string"},
        {TIPO_VOID, "void"},
    };
    cout << "--- Lista de Funcoes ---" << endl;
    for (auto i : listaFuncoes){
        cout << "id = " << i.id << " | tipoRetorno = " << type2str[i.tipoRetorno] << " | pos = " << i.pos << " | nParametros = " << i.nParametros << " | listaParametros = ";
        for(auto j : i.listaParametros) cout << type2str[j.tipo] << ": " << j.id << ";";
        cout << endl;
    }
}

void show_symTable(){
    map<int, string> type2str = {
        {TIPO_INT, "int"},
        {TIPO_FLOAT, "float"},
        {TIPO_STRING, "string"},
        {TIPO_VOID, "void"},
    };
    cout << "--- Tabela de Simbolos ---" << endl;
    cout << "  POS 	 TIPO	   ID" << endl;
    for(auto i:tabelaSimbolos){
        printf("%4d\t%4s  %6s\n",i.pos,type2str[i.tipo].c_str(),i.id.c_str());
    }
    cout << endl;
}

void gen_file(){

    // Referencia https://github.com/alepmaros/Arxs_Compiler
    // Foi utilizado como referencia para controle de main

    struct Instruction i;

    // Variaveis de controle
    int estouMain = 0;
    int sairInstrucoes = 0;
    int contadorFuncao = 0;

    outputFile << ".class public " << nomeClasse << endl 
         << ".super java/lang/Object\n\n"
         << ".method public <init>()V\n"
         << "\taload_0\n\n"
         << "\tinvokenonvirtual java/lang/Object/<init>()V\n"
         << "\treturn\n"
         << ".end method\n\n";
    while(!estouMain){
        if (contadorFuncao == func_count){
            outputFile << ".method public static main([Ljava/lang/String;)V" << endl;
            estouMain = 1;
        }
        else{   
            outputFile << ".method public static " << listaFuncoes[contadorFuncao].id << "(";
            for (auto p : listaFuncoes[contadorFuncao].listaParametros){
                if (p.tipo == TIPO_INT)
                    outputFile << "I";
                else if (p.tipo == TIPO_STRING)
                    outputFile << "Ljava/lang/String;";
                else if (p.tipo == TIPO_VOID)
                    outputFile << "V";
                // else if (p.tipo == TIPO_FLOAT) 
                //     outputFile << "F"; revisar
            }
            outputFile << ")";
            if (listaFuncoes[contadorFuncao].tipoRetorno == TIPO_INT)
                outputFile << "I" << endl;
            else if (listaFuncoes[contadorFuncao].tipoRetorno == TIPO_STRING)
                outputFile << "Ljava/lang/String;" << endl;
            else if (listaFuncoes[contadorFuncao].tipoRetorno == TIPO_VOID)
                outputFile << "V" << endl;
            // else if (listaFuncoes[contadorFuncao].tipoRetorno == TIPO_FLOAT)
            //     outputFile << "F" << endl; revisar
            contadorFuncao++;
        }

        if (estouMain){
            outputFile << "\t.limit stack " << maiorStackSize << endl;
            outputFile << "\t.limit locals " << pos_count << endl;
        } else {
            outputFile << "\t.limit stack " << MAX_STACK << endl;
            outputFile << "\t.limit locals " << MAX_LOCALS << endl;
        }

        while(!listaInstrucoes.empty()){
            auto i = listaInstrucoes.front();
            listaInstrucoes.pop_front();
            switch(i.inst) {
                case INST_IDIV:
                    outputFile << "\tidiv" << endl; break;
                case INST_IMUL:
                    outputFile << "\timul" << endl; break;
                case INST_IADD:
                    outputFile << "\tiadd" << endl; break;
                case INST_ISUB:
                    outputFile << "\tisub" << endl; break;
                case INST_BIPUSH:
                    outputFile << "\tbipush " << i.p1 << endl; break;
                case INST_ILOAD:
                    outputFile << "\tiload " << i.p1 << endl; break;
                case INST_ISTORE:
                    outputFile << "\tistore " << i.p1 << endl; break;
                case INST_GETPRINT:
                    outputFile << "\tgetstatic java/lang/System/out Ljava/io/PrintStream;" << endl;
                    break;
                case INST_INVOKEPRINT_INT:
                    outputFile << "\tinvokevirtual java/io/PrintStream/println(I)V" << endl;
                    break;
                case INST_INVOKEPRINT_STR:
                    outputFile << "\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V" << endl;
                    break;
                case INST_IF_ICMPEQ:
                    outputFile << "\tif_icmpeq l" << i.label << endl; break;
                case INST_IF_ICMPNE:
                    outputFile << "\tif_icmpne l" << i.label << endl; break;
                case INST_IF_ICMPLT:
                    outputFile << "\tif_icmplt l" << i.label << endl; break;
                case INST_IF_ICMPLE:
                    outputFile << "\tif_icmple l" << i.label << endl; break;
                case INST_IF_ICMPGT:
                    outputFile << "\tif_icmpgt l" << i.label << endl; break;
                case INST_IF_ICMPGE:
                    outputFile << "\tif_icmpge l" << i.label << endl; break;
                case INST_GOTO:
                    outputFile << "\tgoto l" << i.label << endl; break;
                case INST_NEWLABEL:
                    outputFile << "l"<< i.label <<":" << endl; break;
                case INST_LDC:
                    outputFile << "\tldc " << i.p1 << endl; break;
                case INST_DUP:
                    outputFile << "\tdup\n"; break;
                case INST_NEWSCANNER:
                    outputFile << "\tnew java/util/Scanner\n"; break;
                case INST_GETINPUTSTREAM:
                    outputFile << "\tgetstatic java/lang/System/in Ljava/io/InputStream;\n"; break;
                case INST_INVOKEINPUTSTR:
                    outputFile << "\tinvokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V\n"; break;
                case INST_NEXTINT:
                    outputFile << "\tinvokevirtual java/util/Scanner/nextInt()I\n"; break;
                case INST_LDCSTRING:
                    outputFile << "\tldc " << i.literal << endl; break;
                case INST_ASTORE:
                    outputFile << "\tastore " << i.p1 << endl; break;
                case INST_ALOAD:
                    outputFile << "\taload " << i.p1 << endl; break;
                case INST_NEXTLINE:
                    outputFile << "\tinvokevirtual java/util/Scanner/nextLine()Ljava/lang/String;\n"; break;
                case INST_DELIMITADORFUNC:
                    sairInstrucoes = 1; break;
                case INST_INVOKESTATIC:
                    outputFile << "\tinvokestatic " << nomeClasse << "/" << i.literal << "(";
                    for(auto p:listaFuncoes[i.p1].listaParametros){
                        if (p.tipo == TIPO_INT)
                            outputFile << "I";
                        else if (p.tipo == TIPO_STRING)
                            outputFile << "Ljava/lang/String;"; // pode ser q seja V arrumar
                        // else if (p.tipo == TIPO_FLOAT)
                        //     outputFile << "F";
                    }
                    outputFile << ")";
                    if (listaFuncoes[i.p1].tipoRetorno == TIPO_INT)
                        outputFile << "I";
                    else if (listaFuncoes[i.p1].tipoRetorno == TIPO_STRING)
                        outputFile << "Ljava/lang/String;";
                    else if (listaFuncoes[i.p1].tipoRetorno == TIPO_VOID)
                        outputFile << "V";
                    outputFile << endl;
                    break;
                case INST_IRETURN:
                    outputFile << "\tireturn\n"; break;
                case INST_ARETURN:
                    outputFile << "\tareturn\n"; break;
                case INST_RETURN:
                    outputFile << "\treturn\n"; break;
                case INST_IINC:
                    outputFile << "\tiinc " << i.p1 << " " << i.p2 << endl; break;

                default:
                    break;
            }
            if (sairInstrucoes) {
                sairInstrucoes = 0;
                break;
            }
        }

        outputFile << "\treturn\n";
        outputFile << ".end method\n\n";
    }
}

void error(){
    cout << "ERRO!\n";
    exit(-1);
}

void incrementaStack(int i){
    contStackSize += i;
    maiorStackSize = max(maiorStackSize,contStackSize);
}

void decrementaStack(int i){
    contStackSize -= i;
    if (contStackSize < 0){
        cout << "INCONSISTENCIA NA REDUCAO DO STACK! TENTOU REDUZIR " << i << endl;
        exit(-1);
    }
}
