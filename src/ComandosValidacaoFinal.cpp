//
// Created by Pedro Freitas on 20/11/2026.
//
#include "ComandosValidacaoFinal.h"
#include "Fabrica.h"
#include <iostream>
#include <sstream>
#include <cctype>

namespace {
    bool posValidaSintaxe(const std::string& token) {
        if (token.size() != 2) return false;
        char a = static_cast<char>(std::tolower(static_cast<unsigned char>(token[0])));
        char b = static_cast<char>(std::tolower(static_cast<unsigned char>(token[1])));
        return (a >= 'a' && a <= 'z') && (b >= 'a' && b <= 'z');
    }
}

// --- melhora <pos> ---
std::string ComandoMelhora::ajuda() {
    return "melhora <pos> - Melhora uma maquina na posicao indicada. Uso: melhora aa";
}

void ComandoMelhora::executa(Fabrica&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string pos, extra;
    if (!(iss >> pos) || (iss >> extra) || !posValidaSintaxe(pos)) {
        std::cout << "Erro: parametros invalidos.\n" << ajuda() << "\n";
        return;
    }
    std::cout << "Comando 'melhora' validado para '" << pos << "' (execucao completa na entrega final).\n";
}

// --- contrata ---
std::string ComandoContrata::ajuda() {
    return "contrata - Contrata um engenheiro para a fabrica. Uso: contrata";
}

void ComandoContrata::executa(Fabrica&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string extra;
    if (iss >> extra) {
        std::cout << "Erro: parametros invalidos.\n" << ajuda() << "\n";
        return;
    }
    std::cout << "Comando 'contrata' validado (execucao completa na entrega final).\n";
}

// --- atribui <id_ou_alvo> <pos> ---
std::string ComandoAtribui::ajuda() {
    return "atribui <engenheiro> <pos> - Atribui um engenheiro a uma posicao/maquina. Uso: atribui 1 aa";
}

void ComandoAtribui::executa(Fabrica&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string eng, pos, extra;
    if (!(iss >> eng >> pos) || (iss >> extra) || !posValidaSintaxe(pos)) {
        std::cout << "Erro: parametros invalidos.\n" << ajuda() << "\n";
        return;
    }
    std::cout << "Comando 'atribui' validado para '" << eng << "' em '" << pos << "' (execucao completa na entrega final).\n";
}

// --- despede <engenheiro> ---
std::string ComandoDespede::ajuda() {
    return "despede <engenheiro> - Despede um engenheiro. Uso: despede 1";
}

void ComandoDespede::executa(Fabrica&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string eng, extra;
    if (!(iss >> eng) || (iss >> extra)) {
        std::cout << "Erro: parametros invalidos.\n" << ajuda() << "\n";
        return;
    }
    std::cout << "Comando 'despede' validado para '" << eng << "' (execucao completa na entrega final).\n";
}

// --- grava <nome> ---
std::string ComandoGrava::ajuda() {
    return "grava <nome> - Grava o estado atual da simulacao. Uso: grava estado1";
}

void ComandoGrava::executa(Fabrica&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string nome, extra;
    if (!(iss >> nome) || (iss >> extra)) {
        std::cout << "Erro: parametros invalidos.\n" << ajuda() << "\n";
        return;
    }
    std::cout << "Comando 'grava' validado para '" << nome << "' (execucao completa na entrega final).\n";
}

// --- recupera <nome> ---
std::string ComandoRecupera::ajuda() {
    return "recupera <nome> - Recupera um estado gravado. Uso: recupera estado1";
}

void ComandoRecupera::executa(Fabrica&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string nome, extra;
    if (!(iss >> nome) || (iss >> extra)) {
        std::cout << "Erro: parametros invalidos.\n" << ajuda() << "\n";
        return;
    }
    std::cout << "Comando 'recupera' validado para '" << nome << "' (execucao completa na entrega final).\n";
}
