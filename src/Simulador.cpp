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

        Interpretador::executaLinha(contexto, linha);
    }

    return 0;
}
