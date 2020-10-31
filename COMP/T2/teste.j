string max(int v1, int v2){
    string r1, r2;
    string texto;
    texto = "\n\n-- Funcao max --\n";
    r1 = "Variavel 1 eh maior";
    r2 = "Variavel 2 eh maior";
    print(texto);
    if(v1>v2){
        return r1;
    } else {
        return r2;
    }
}
{
    int a,b,c;
    string resposta;
    string texto;
    texto = "-- Funcao main --\n";
    print(texto);
    print("Digite o valor de a"); read(a);
    print("Digite o valor de b"); read(b);
    resposta = max(a,b); print(resposta);
    print("Realizando a expressao: a-b*10");
    print(a-b*10);
    print("-- Teste de repeticao --");
    print("Digite o valor de c"); read(c);
    while(c>0){
        print(c);
        c = c-1;
    }
}   