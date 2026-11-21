//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Maquina.h"

Maquina::Maquina(char tipo, int linha, int coluna, char direcao, int custo)
        : tipo(tipo), linha(linha), coluna(coluna), direcao('d'), custo(custo) {
    setDirecao(direcao);
}

char Maquina::getTipo() const {
    return tipo;
}

int Maquina::getLinha() const {
    return linha;
}

int Maquina::getColuna() const {
    return coluna;
}

char Maquina::getDirecao() const {
    return direcao;
}

int Maquina::getCusto() const {
    return custo;
}

bool Maquina::setDirecao(char novaDirecao) {
    if (novaDirecao == 'c' || novaDirecao == 'b' ||
        novaDirecao == 'e' || novaDirecao == 'd') {
        direcao = novaDirecao;
        return true;
    }
    return false;
}

char Maquina::getSimbolo() const {
    return tipo;
}

std::string Maquina::getDescricao() const {
    return "Maquina tipo " + std::string(1, tipo) + " (direcao: " + std::string(1, direcao) + ")";
}
bool Maquina::aceitaItem(char) const {
    return false;
}

bool Maquina::recebeItem(char) {
    return false;
}

bool Maquina::temItemParaEntregar() const {
    return false;
}

char Maquina::verItemParaEntrega() const {
    return '\0';
}

bool Maquina::retirarItemParaEntrega(char& itemEntregue) {
    itemEntregue = '\0';
    return false;
}

void Maquina::avancarInstante(int, const Terreno&, int&) {
}