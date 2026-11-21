//
// Created by Pedro Freitas on 04/11/2026.
//

#include "ComandosCriacao.h"
#include "Contexto.h"
#include "Fabrica.h"
#include <sstream>
#include <iostream>
#include <string>

bool ComandoFabrica::executa(Contexto& contexto, const std::string& argumentos) {
    Fabrica& fabricaJogo = contexto.getFabrica();
    std::istringstream iss(argumentos);
    int nl, nc;
    std::string extra;

    if (iss >> nl >> nc && !(iss >> extra)) {
        bool sucesso = fabricaJogo.criarAleatoria(nl, nc);
        if (sucesso) {
            std::cout << "Fabrica criada com sucesso (" << nl << "x" << nc << ")!\n";
            return true;
        }
        std::cout << "Erro: Dimensoes invalidas.\n";
    } else {
        std::cout << "Erro: Sintaxe incorreta. Uso: fabrica <linhas> <colunas>\n";
    }
    return false;
}

std::string ComandoFabrica::ajudaResumida() const {
    return "fabrica <nl> <nc>      cria a fabrica com nl linhas e nc colunas";
}

std::string ComandoFabrica::ajudaDetalhada() const {
    return "fabrica <nl> <nc>\n"
           "  nl, nc : numero de linhas e de colunas (inteiros entre 1 e 26).\n"
           "  Cria a fabrica com crateras e depositos em posicoes aleatorias.\n"
           "  Tem de ser o primeiro comando de criacao (fabrica ou carrega) e so pode\n"
           "  ser executado uma vez.\n"
           "  Falha se as dimensoes forem invalidas ou se a fabrica ja existir.\n"
           "  Exemplo: fabrica 12 20\n";
}

bool ComandoCarrega::executa(Contexto& contexto, const std::string& argumentos) {
    Fabrica& fabricaJogo = contexto.getFabrica();
    std::istringstream iss(argumentos);
    std::string nomeFicheiro;
    std::string extra;

    if (!(iss >> nomeFicheiro) || (iss >> extra)) {
        std::cout << "Erro: Sintaxe incorreta. Uso: carrega <nome-do-ficheiro>\n";
        return false;
    }

    if (!fabricaJogo.carregarDeFicheiro(nomeFicheiro)) {
        std::cout << "Erro: Nao foi possivel carregar a fabrica a partir de '" << nomeFicheiro << "'.\n";
        return false;
    }

    std::cout << "Fabrica carregada com sucesso a partir de '" << nomeFicheiro << "'.\n";
    return true;
}

std::string ComandoCarrega::ajudaResumida() const {
    return "carrega <ficheiro>     cria a fabrica a partir de um ficheiro de texto";
}

std::string ComandoCarrega::ajudaDetalhada() const {
    return "carrega <nome-do-ficheiro>\n"
           "  nome-do-ficheiro : caminho/nome do ficheiro com as dimensoes e o mapa.\n"
           "  Valida o formato do ficheiro e cria a fabrica sem deixar estado invalido\n"
           "  em caso de falha.\n"
           "  Exemplo: carrega mapa1.txt\n";
}