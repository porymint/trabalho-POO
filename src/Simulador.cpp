#include <iostream>
#include <string>
#include "Ecra.h"
#include "Fabrica.h"
#include "Interpretador.h"

using namespace std;

void desenhaInterfaceBase(Ecra& ecra, const Fabrica& fabrica) {
    int linhasFabrica = fabrica.getLinhas();
    int colunasFabrica = fabrica.getColunas();

    int linhaInicio = 3;
    int colInicio = 5;

    if (linhasFabrica > 0 && colunasFabrica > 0) {
        ecra.desenhaEcra(linhaInicio - 2, colInicio - 3, linhasFabrica + 3, colunasFabrica + 5);

        for (int i = 0; i < colunasFabrica; ++i) {
            ecra.posicionaCursor(linhaInicio - 1, colInicio + i);
            ecra.escreve(static_cast<char>('A' + i));
        }

        for (int i = 0; i < linhasFabrica; ++i) {
            ecra.posicionaCursor(linhaInicio + i, colInicio - 2);
            ecra.escreve(static_cast<char>('A' + i));
        }
    }

    int colPainel = colInicio + (colunasFabrica > 0 ? colunasFabrica : 0) + 5;
    ecra.desenhaEcra(linhaInicio - 2, colPainel, 12, 35);

    ecra.posicionaCursor(linhaInicio, colPainel + 6);
    ecra.escreve("MARTE: ESTADO");
    ecra.posicionaCursor(linhaInicio + 2, colPainel + 2);
    ecra.escreve("Instante: 0");
    ecra.posicionaCursor(linhaInicio + 3, colPainel + 2);
    ecra.escreve("Creditos: 0");

}

int main() {
    Ecra ecra;
    Fabrica fabrica(0, 0);
    string linha;

    while (true) {
        ecra.limpa();

        desenhaInterfaceBase(ecra, fabrica);

        if (fabrica.getLinhas() > 0 && fabrica.getColunas() > 0) {
            ecra.desenhaFabrica(fabrica, 3, 5);
        }

        ecra.posicionaCursor(38, 0);
        ecra.mostra();

        cout << "\nComando> ";

        if (!getline(cin, linha)) break;
        if (linha.empty()) continue;

        string argumentos;
        Comando* cmd = Interpretador::processaLinha(linha, argumentos);

        if (cmd != nullptr) {
            cmd->executa(fabrica, argumentos);
            delete cmd;

            if (linha.rfind("fim", 0) == 0)
                break;
        } else {
            cout << "Erro: Comando nao reconhecido." << endl;
        }
    }

    return 0;
}