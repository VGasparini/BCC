#include "bib.hpp"
#include "syntax.tab.hpp"
/* ********************************** MAIN *****************************/
extern int yyparse(void);
extern FILE *yyin;
extern string nomeClasse;
extern ofstream outputFile;
int main(int argc, char *argv[]){
    string inputName;
    cout << "Digite o nome do arquivo de entrada\n-> ";
    cin >> inputName;
    FILE *inputFile = fopen(inputName.c_str(), "r");
    cout << "Digite o nome da classe de saida\n-> ";
    cin >> nomeClasse;
    outputFile.open(nomeClasse + ".jout");
    yyin = inputFile;
    yyparse();
    fclose(inputFile);
    outputFile.close();
    cout << "Deseja ver a tabela de simbolos? (0 | 1)\n-> ";
    int op; cin >> op;
    if(op) show_symTable();
    cout << "Deseja ver a lista de funcoes? (0 | 1)\n-> ";
    cin >> op;
    if(op) dump_func();
    return 0;
}