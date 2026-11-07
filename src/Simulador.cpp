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

    // Só desenha a grelha e as réguas se já houver dimensões válidas
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

    // O painel de estado à direita continua sempre visível
    int colPainel = colInicio + (colunasFabrica > 0 ? colunasFabrica : 0) + 5;
    ecra.desenhaEcra(linhaInicio - 2, colPainel, 12, 35);

    ecra.posicionaCursor(linhaInicio, colPainel + 6);
    ecra.escreve("=== MARTE: ESTADO ===");
    ecra.posicionaCursor(linhaInicio + 2, colPainel + 2);
    ecra.escreve("Instante: 0");
    ecra.posicionaCursor(linhaInicio + 3, colPainel + 2);
    ecra.escreve("Creditos: 0");

    ecra.posicionaCursor(linhaInicio + 8, colPainel + 2);
    ecra.escreve("Comandos: fabrica, carrega,");
    ecra.posicionaCursor(linhaInicio + 9, colPainel + 2);
    ecra.escreve("          lposicao, fim");
}

int main() {
    Ecra ecra;
    Fabrica fabrica(0, 0); // Arranca vazio, sem dimensões pré-definidas
    string linha;

    while (true) {
        ecra.limpa();

        // Desenha a interface e os elementos dinâmicos com base no estado atual da fábrica
        desenhaInterfaceBase(ecra, fabrica);

        // Só desenha o conteúdo da fábrica se ela já tiver sido inicializada
        if (fabrica.getLinhas() > 0 && fabrica.getColunas() > 0) {
            ecra.desenhaFabrica(fabrica, 3, 5);
        }

        ecra.posicionaCursor(38, 0);
        ecra.mostra(); // Despeja o buffer atualizado para o ecrã

        cout << "\nComando> ";

        if (!getline(cin, linha)) break;
        if (linha.empty()) continue;

        string argumentos;
        Comando* cmd = Interpretador::processaLinha(linha, argumentos);

        if (cmd != nullptr) {
            cmd->executa(fabrica, argumentos);
            delete cmd;

            if (linha.rfind("fim", 0) == 0) break;
        } else {
            cout << "Erro: Comando nao reconhecido." << endl;
        }
    }

    return 0;
}