//
// Created by Pedro Freitas on 04/11/2026.
//

#include "ComandosCriacao.h"
#include "Fabrica.h"
#include <sstream>
#include <iostream>
#include <string>

void ComandoFabrica::executa(Fabrica& fabricaJogo, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    int nl, nc;

    if (iss >> nl >> nc) {
        bool sucesso = fabricaJogo.criarAleatoria(nl, nc);
        if (sucesso) {
            std::cout << "Fabrica criada com sucesso (" << nl << "x" << nc << ")!\n";
        } else {
            std::cout << "Erro: Dimensoes invalidas.\n";
        }
    } else {
        std::cout << "Erro: Sintaxe incorreta. Uso: fabrica <linhas> <colunas>\n";
    }
}