//
// Created by Pedro Freitas on 04/11/2026.
//

#include "ComandosMaquinas.h"
#include "Fabrica.h"
#include <iostream>
#include <sstream>
#include <cctype>

namespace {
    bool parsePosicao(const std::string& token, int& linha, int& coluna) {
        if (token.size() != 2) {
            return false;
        }
        char lChar = static_cast<char>(std::tolower(static_cast<unsigned char>(token[0])));
        char cChar = static_cast<char>(std::tolower(static_cast<unsigned char>(token[1])));

        if (lChar < 'a' || lChar > 'z' || cChar < 'a' || cChar > 'z') {
            return false;
        }

        linha = lChar - 'a';
        coluna = cChar - 'a';
        return true;
    }

    char normalizaTipoMaquina(const std::string& token) {
        if (token.size() != 1) {
            return '\0';
        }
        char t = static_cast<char>(std::toupper(static_cast<unsigned char>(token[0])));
        if (t == 'P' || t == 'T' || t == 'R' || t == 'O' || t == 'S' || t == 'L') {
            return t;
        }
        return '\0';
    }

    char normalizaDirecao(const std::string& token) {
        if (token.size() != 1) {
            return '\0';
        }
        char d = static_cast<char>(std::tolower(static_cast<unsigned char>(token[0])));
        if (d == 'c' || d == 'b' || d == 'e' || d == 'd') {
            return d;
        }
        return '\0';
    }
}

void ComandoCompra::executa(Fabrica& fabrica, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string tipoStr, posStr, dirStr, extra;

    if (!(iss >> tipoStr >> posStr >> dirStr) || (iss >> extra)) {
        std::cout << "Uso: compra <tipo: P|T|R|O|S|L> <posicao: aa> <direcao: c|b|e|d>\n";
        return;
    }

    char tipo = normalizaTipoMaquina(tipoStr);
    char dir = normalizaDirecao(dirStr);
    int linha = -1, coluna = -1;

    if (tipo == '\0' || dir == '\0' || !parsePosicao(posStr, linha, coluna)) {
        std::cout << "Erro: argumentos invalidos no comando 'compra'.\n";
        return;
    }

    if (!fabrica.comprarMaquina(tipo, linha, coluna, dir)) {
        std::cout << "Erro: nao foi possivel comprar a maquina '" << tipo
                  << "' em '" << posStr << "' (posicao invalida, cratera, ocupada ou creditos insuficientes).\n";
        return;
    }

    std::cout << "Maquina '" << tipo << "' comprada em '" << posStr
              << "' (creditos restantes: " << fabrica.getCreditos() << ").\n";
}

void ComandoVende::executa(Fabrica& fabrica, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string posStr, extra;

    if (!(iss >> posStr) || (iss >> extra)) {
        std::cout << "Uso: vende <posicao: aa>\n";
        return;
    }

    int linha = -1, coluna = -1;
    if (!parsePosicao(posStr, linha, coluna)) {
        std::cout << "Erro: posicao invalida no comando 'vende'.\n";
        return;
    }

    if (!fabrica.venderMaquina(linha, coluna)) {
        std::cout << "Erro: nao existe nenhuma maquina em '" << posStr << "' para vender.\n";
        return;
    }

    std::cout << "Maquina em '" << posStr << "' vendida (creditos atuais: "
              << fabrica.getCreditos() << ").\n";
}

void ComandoRoda::executa(Fabrica& fabrica, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string posStr, dirStr, extra;

    if (!(iss >> posStr >> dirStr) || (iss >> extra)) {
        std::cout << "Uso: roda <posicao: aa> <direcao: c|b|e|d>\n";
        return;
    }

    int linha = -1, coluna = -1;
    char dir = normalizaDirecao(dirStr);
    if (!parsePosicao(posStr, linha, coluna) || dir == '\0') {
        std::cout << "Erro: argumentos invalidos no comando 'roda'.\n";
        return;
    }

    if (!fabrica.rodarMaquina(linha, coluna, dir)) {
        std::cout << "Erro: nao foi possivel rodar a maquina em '" << posStr << "'.\n";
        return;
    }

    std::cout << "Maquina em '" << posStr << "' rodada para '" << dir << "'.\n";
}