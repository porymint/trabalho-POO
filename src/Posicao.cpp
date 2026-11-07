//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Posicao.h"

Posicao::Posicao() : terreno(VAZIO), quantidade(0) {}

Posicao::Posicao(TipoTerreno t, int qtd) : terreno(t), quantidade(qtd) {}

Posicao::TipoTerreno Posicao::getTerreno() const {
    return terreno;
}

void Posicao::setTerreno(TipoTerreno t, int qtd) {
    terreno = t;
    quantidade = qtd;
}

int Posicao::getQuantidade() const {
    return quantidade;
}

char Posicao::getSimbolo() const {
    switch (terreno) {
        case VAZIO: return ' ';
        case CRATERA: return '#';
        case FERRO: return '%';
        case SILICIO: return '$';
        case GELO: return '~';
    }
    return ' ';
}

std::string Posicao::getDescricao() const {
    switch (terreno) {
        case VAZIO: return "Solo vazio";
        case CRATERA: return "Cratera (#)";
        case FERRO: return "Deposito de ferro (%%) - Quantidade: " + std::to_string(quantidade);
        case SILICIO: return "Deposito de silicio ($) - Quantidade: " + std::to_string(quantidade);
        case GELO: return "Deposito de gelo (~) - Quantidade: " + std::to_string(quantidade);
    }
    sainfo: return "Desconhecido";
}