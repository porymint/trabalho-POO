//
// Created by Pedro Freitas on 20/11/2026.
//
#include "ComandosValidacaoFinal.h"
#include "Contexto.h"
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
std::string ComandoMelhora::ajudaResumida() const {
    return "melhora <pos>        melhora uma maquina na posicao indicada";
}

std::string ComandoMelhora::ajudaDetalhada() const {
    return "melhora <pos>\n"
           "  pos : posicao em duas letras (ex.: aa).\n"
           "  Valida parametros (execucao completa na entrega final).\n";
}

bool ComandoMelhora::executa(Contexto&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string pos, extra;
    if (!(iss >> pos) || (iss >> extra) || !posValidaSintaxe(pos)) {
        std::cout << "Erro: parametros invalidos.\n" << ajudaResumida() << "\n";
        return false;
    }
    std::cout << "Comando 'melhora' validado para '" << pos << "' (execucao completa na entrega final).\n";
    return false;
}

// --- contrata ---
std::string ComandoContrata::ajudaResumida() const {
    return "contrata             contrata um engenheiro para a fabrica";
}

std::string ComandoContrata::ajudaDetalhada() const {
    return "contrata\n"
           "  Valida parametros (execucao completa na entrega final).\n";
}

bool ComandoContrata::executa(Contexto&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string extra;
    if (iss >> extra) {
        std::cout << "Erro: parametros invalidos.\n" << ajudaResumida() << "\n";
        return false;
    }
    std::cout << "Comando 'contrata' validado (execucao completa na entrega final).\n";
    return false;
}

// --- atribui <engenheiro> <pos> ---
std::string ComandoAtribui::ajudaResumida() const {
    return "atribui <eng> <pos>  atribui um engenheiro a uma posicao/maquina";
}

std::string ComandoAtribui::ajudaDetalhada() const {
    return "atribui <engenheiro> <pos>\n"
           "  engenheiro : identificador do engenheiro.\n"
           "  pos        : posicao em duas letras (ex.: aa).\n"
           "  Valida parametros (execucao completa na entrega final).\n";
}

bool ComandoAtribui::executa(Contexto&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string eng, pos, extra;
    if (!(iss >> eng >> pos) || (iss >> extra) || !posValidaSintaxe(pos)) {
        std::cout << "Erro: parametros invalidos.\n" << ajudaResumida() << "\n";
        return false;
    }
    std::cout << "Comando 'atribui' validado para '" << eng << "' em '" << pos << "' (execucao completa na entrega final).\n";
    return false;
}

// --- despede <engenheiro> ---
std::string ComandoDespede::ajudaResumida() const {
    return "despede <eng>        despede um engenheiro";
}

std::string ComandoDespede::ajudaDetalhada() const {
    return "despede <engenheiro>\n"
           "  engenheiro : identificador do engenheiro.\n"
           "  Valida parametros (execucao completa na entrega final).\n";
}

bool ComandoDespede::executa(Contexto&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string eng, extra;
    if (!(iss >> eng) || (iss >> extra)) {
        std::cout << "Erro: parametros invalidos.\n" << ajudaResumida() << "\n";
        return false;
    }
    std::cout << "Comando 'despede' validado para '" << eng << "' (execucao completa na entrega final).\n";
    return false;
}

// --- grava <nome> ---
std::string ComandoGrava::ajudaResumida() const {
    return "grava <nome>         grava o estado atual da simulacao";
}

std::string ComandoGrava::ajudaDetalhada() const {
    return "grava <nome>\n"
           "  nome : etiqueta do estado a gravar.\n"
           "  Valida parametros (execucao completa na entrega final).\n";
}

bool ComandoGrava::executa(Contexto&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string nome, extra;
    if (!(iss >> nome) || (iss >> extra)) {
        std::cout << "Erro: parametros invalidos.\n" << ajudaResumida() << "\n";
        return false;
    }
    std::cout << "Comando 'grava' validado para '" << nome << "' (execucao completa na entrega final).\n";
    return false;
}

// --- recupera <nome> ---
std::string ComandoRecupera::ajudaResumida() const {
    return "recupera <nome>      recupera um estado gravado";
}

std::string ComandoRecupera::ajudaDetalhada() const {
    return "recupera <nome>\n"
           "  nome : etiqueta do estado gravado.\n"
           "  Valida parametros (execucao completa na entrega final).\n";
}

bool ComandoRecupera::executa(Contexto&, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string nome, extra;
    if (!(iss >> nome) || (iss >> extra)) {
        std::cout << "Erro: parametros invalidos.\n" << ajudaResumida() << "\n";
        return false;
    }
    std::cout << "Comando 'recupera' validado para '" << nome << "' (execucao completa na entrega final).\n";
    return false;
}