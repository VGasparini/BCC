#include "includes.h"
int main(int argc, char const *argv[]) {
    automato teste = read_quintuple_from_data();
    cout << teste.run_with_word("+") << endl;
    return 0;
}
