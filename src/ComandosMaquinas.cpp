//
// Created by Pedro Freitas on 04/11/2026.
//

#include "ComandosMaquinas.h"
#include "Contexto.h"
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

bool ComandoCompra::executa(Contexto& contexto, const std::string& argumentos) {
    Fabrica& fabrica = contexto.getFabrica();
    std::istringstream iss(argumentos);
    std::string tipoStr, posStr, dirStr, extra;

    if (!(iss >> tipoStr >> posStr >> dirStr) || (iss >> extra)) {
        std::cout << "Erro: sintaxe incorreta.\n" << ajudaResumida() << "\n";
        return false;
    }

    char tipo = normalizaTipoMaquina(tipoStr);
    char dir = normalizaDirecao(dirStr);
    int linha = -1, coluna = -1;

    if (tipo == '\0' || dir == '\0' || !parsePosicao(posStr, linha, coluna)) {
        std::cout << "Erro: argumentos invalidos no comando 'compra'.\n";
        return false;
    }

    if (!fabrica.comprarMaquina(tipo, linha, coluna, dir)) {
        std::cout << "Erro: nao foi possivel comprar a maquina '" << tipo
                  << "' em '" << posStr << "' (posicao invalida, cratera, ocupada ou creditos insuficientes).\n";
        return false;
    }

    std::cout << "Maquina '" << tipo << "' comprada em '" << posStr
              << "' (creditos restantes: " << fabrica.getCreditos() << ").\n";
    return true;
}

std::string ComandoCompra::ajudaResumida() const {
    return "compra <tipo> <pos> <dir> compra uma maquina (P|T|R|O|S|L) em <pos> com direcao <c|b|e|d>";
}

std::string ComandoCompra::ajudaDetalhada() const {
    return "compra <tipo> <pos> <dir>\n"
           "  tipo : P, T, R, O, S ou L.\n"
           "  pos  : posicao em duas letras (ex.: aa).\n"
           "  dir  : direcao de saida (c, b, e, d).\n"
           "  Desconta o custo aos creditos se a posicao for valida, livre e sem cratera.\n"
           "  Exemplo: compra P ab d\n";
}

bool ComandoVende::executa(Contexto& contexto, const std::string& argumentos) {
    Fabrica& fabrica = contexto.getFabrica();
    std::istringstream iss(argumentos);
    std::string posStr, extra;

    if (!(iss >> posStr) || (iss >> extra)) {
        std::cout << "Erro: sintaxe incorreta.\n" << ajudaResumida() << "\n";
        return false;
    }

    int linha = -1, coluna = -1;
    if (!parsePosicao(posStr, linha, coluna)) {
        std::cout << "Erro: posicao invalida no comando 'vende'.\n";
        return false;
    }

    if (!fabrica.venderMaquina(linha, coluna)) {
        std::cout << "Erro: nao existe nenhuma maquina em '" << posStr << "' para vender.\n";
        return false;
    }

    std::cout << "Maquina em '" << posStr << "' vendida (creditos atuais: "
              << fabrica.getCreditos() << ").\n";
    return true;
}

std::string ComandoVende::ajudaResumida() const {
    return "vende <pos>          vende a maquina na posicao indicada e devolve 50% do custo";
}

std::string ComandoVende::ajudaDetalhada() const {
    return "vende <pos>\n"
           "  pos : posicao em duas letras (ex.: ab).\n"
           "  Remove a maquina da posicao e adiciona metade do custo aos creditos.\n"
           "  Exemplo: vende ab\n";
}

bool ComandoRoda::executa(Contexto& contexto, const std::string& argumentos) {
    Fabrica& fabrica = contexto.getFabrica();
    std::istringstream iss(argumentos);
    std::string posStr, dirStr, extra;

    if (!(iss >> posStr >> dirStr) || (iss >> extra)) {
        std::cout << "Erro: sintaxe incorreta.\n" << ajudaResumida() << "\n";
        return false;
    }

    int linha = -1, coluna = -1;
    char dir = normalizaDirecao(dirStr);
    if (!parsePosicao(posStr, linha, coluna) || dir == '\0') {
        std::cout << "Erro: argumentos invalidos no comando 'roda'.\n";
        return false;
    }

    if (!fabrica.rodarMaquina(linha, coluna, dir)) {
        std::cout << "Erro: nao foi possivel rodar a maquina em '" << posStr << "'.\n";
        return false;
    }

    std::cout << "Maquina em '" << posStr << "' rodada para '" << dir << "'.\n";
    return true;
}

std::string ComandoRoda::ajudaResumida() const {
    return "roda <pos> <dir>     altera a direcao (c, b, e, d) da maquina na posicao <pos>";
}

std::string ComandoRoda::ajudaDetalhada() const {
    return "roda <pos> <dir>\n"
           "  pos : posicao em duas letras (ex.: ab).\n"
           "  dir : nova direcao (c, b, e, d).\n"
           "  Exemplo: roda ab c\n";
}