//
// Created by Pedro Freitas on 04/11/2026.
//

#include "ComandosTempo.h"
#include "Contexto.h"
#include "Fabrica.h"
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

namespace {
    // Converte texto num inteiro, aceitando apenas texto totalmente numerico.
    bool lerInteiro(const string& texto, int& valor) {
        char* fim = nullptr;
        errno = 0;
        long v = strtol(texto.c_str(), &fim, 10);
        if (texto.empty() || *fim != '\0' || errno == ERANGE || v > INT_MAX || v < INT_MIN) {
            return false;
        }
        valor = static_cast<int>(v);
        return true;
    }
}

bool ComandoAvanca::executa(Contexto& contexto, const string& argumentos) {
    istringstream iss(argumentos);
    string texto, extra;
    int n = 1;

    if (iss >> texto) {
        if (!lerInteiro(texto, n)) {
            cout << "Erro: O numero de instantes tem de ser um inteiro. Uso: avanca [n]" << endl;
            return false;
        }
        if (iss >> extra) {
            cout << "Erro: Sintaxe incorreta. Uso: avanca [n]" << endl;
            return false;
        }
        if (n <= 0) {
            cout << "Erro: O numero de instantes tem de ser positivo." << endl;
            return false;
        }
    }

    Fabrica& fabrica = contexto.getFabrica();
    for (int i = 0; i < n; ++i) {
        fabrica.avancaInstante();
        contexto.apresenta();   // o ecra e apresentado no fim de cada instante
    }

    return false;   // o ecra ja foi apresentado
}

string ComandoAvanca::ajudaResumida() const {
    return "avanca [n]             avanca n instantes (por omissao 1)";
}

string ComandoAvanca::ajudaDetalhada() const {
    return "avanca [n]\n"
           "  n : (opcional) numero inteiro positivo de instantes. Por omissao, 1.\n"
           "  Avanca n instantes, um de cada vez. Em cada instante as maquinas atuam e\n"
           "  sao feitas as contas de custos e ganhos. O ecra e apresentado no fim de\n"
           "  cada instante.\n"
           "  Falha se n nao for inteiro, se for <= 0, ou se a fabrica ainda nao existir.\n"
           "  Exemplo: avanca 10\n";
}
