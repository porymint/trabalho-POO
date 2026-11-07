//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Fabrica.h"
#include "Comandos.h"
#include "Settings.h"
#include <fstream>
#include <iostream>

Fabrica::Fabrica(int nl, int nc) : linhas(nl), colunas(nc) {

}

bool Fabrica::posicaoValida(int l, int c) const {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

const Terreno& Fabrica::getTerreno(int l, int c) const {
    return grelha[l][c];
}

void Fabrica::gerarAleatorio() {
    srand(time(NULL));

    int linhaRand = rand() % linhas; 
    int colunaRand = rand() % colunas;
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
