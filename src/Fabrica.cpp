//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Fabrica.h"
#include "Comandos.h"
#include "Settings.h"
#include <fstream>
#include <iostream>
#include <random>

Fabrica::Fabrica(int nl, int nc) : linhas(nl), colunas(nc) {
    grelha.resize(linhas, std::vector<Terreno>(colunas));
}

bool Fabrica::posicaoValida(int l, int c) const {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

const Terreno& Fabrica::getTerreno(int l, int c) const {
    return grelha[l][c];
}

void Fabrica::gerarAleatorio() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disQtd(40, 60);
}

bool Fabrica::carregarDeFicheiro(const std::string& nomeFicheiro) {
    std::ifstream file(nomeFicheiro);
    if (!file.is_open()) {
        return false;
    }

    int nl, nc;
    if (!(file >> nl >> nc)) return false;

    if (nl > 26 || nc > 26 || nl <= 0 || nc <= 0) {
        return false;
    }

    linhas = nl;
    colunas = nc;
    grelha.resize(linhas, std::vector<Terreno>(colunas));

    std::string linhaTexto;
    std::getline(file, linhaTexto);

    for (int i = 0; i < linhas; ++i) {
        if (!std::getline(file, linhaTexto)) return false;
        for (int j = 0; j < colunas && j < linhaTexto.size(); ++j) {
            char c = linhaTexto[j];
            if (c == '.' || c == '#' || c == '%' || c == '$' || c == '~') {
                grelha[i][j].tipo = c;
                if (c == '%' || c == '$' || c == '~') {
                    grelha[i][j].quantidade = 50;
                }
            } else {
                return false;
            }
        }
    }
    return true;
}
