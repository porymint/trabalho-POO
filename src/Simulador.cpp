#include <iostream>
#include <string>
#include "Contexto.h"
#include "Ecra.h"
#include "Fabrica.h"
#include "Interpretador.h"

using namespace std;

int main() {
    Ecra ecra;
    Fabrica fabrica(0, 0);
    Contexto contexto(fabrica, ecra);
    string linha;

    contexto.apresenta();

    while (!contexto.terminou()) {
        cout << "\nComando> ";

        if (!getline(cin, linha)) break;

        // Mesmo caminho para comandos do teclado e de ficheiros (executa).
        Interpretador::executaLinha(contexto, linha);
    }

    return 0;   // Fabrica (e as suas maquinas) sao libertadas pelos destrutores
}
