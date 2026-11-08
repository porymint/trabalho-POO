//
// Created by Pedro Freitas on 03/11/2026.
//
#include "Fabrica.h"
#include "Settings.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Fabrica::alocaMemoria(int nl, int nc) {
    linhas = nl;
    colunas = nc;
    if (linhas > 0 && colunas > 0) {
        grelha = new Terreno[linhas * colunas];
    } else {
        grelha = nullptr;
    }
}

void Fabrica::libertaMemoria() {
    if (grelha != nullptr) {
        delete[] grelha;
        grelha = nullptr;
    }
}

Fabrica::Fabrica(int nl, int nc) {
    alocaMemoria(nl, nc);
    srand(time(NULL));
}

Fabrica::~Fabrica() {
    libertaMemoria();
}

bool Fabrica::posicaoValida(int l, int c) const {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

const Terreno* Fabrica::getTerreno(int l, int c) const {
    if (posicaoValida(l, c)) {
        int indice = (l * colunas) + c;
        return &grelha[indice];
    }
    return nullptr;
}

bool Fabrica::criarAleatoria(int nl, int nc) {
    if (nl > Settings::MAX_LINHAS || nc > Settings::MAX_COLUNAS || nl <= 0 || nc <= 0) {
        return false;
    }

    libertaMemoria();
    alocaMemoria(nl, nc);

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int indice = (i * colunas) + j;
            int chance = rand() % 100;

            if (chance < 5) {
                grelha[indice].setTipo('#');
            } else if (chance < 15) {
                grelha[indice].setTipo('%');


                int quantidade = Settings::MIN_MATERIA_DEPOSITO +
                                 rand() % (Settings::MAX_MATERIA_DEPOSITO - Settings::MIN_MATERIA_DEPOSITO + 1);
                grelha[indice].setQuantidade(quantidade);
            } else {
                grelha[indice].setTipo('.');
            }
        }
    }
    return true;
}