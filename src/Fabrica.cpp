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
        // Aloca a grelha toda num único bloco contínuo de memória
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
        // MATEMÁTICA DO PONTEIRO SIMPLES: (linha * total_colunas) + coluna
        int indice = (l * colunas) + c;
        return &grelha[indice];
    }
    return nullptr;
}

bool Fabrica::criarAleatoria(int nl, int nc) {
    // Valida os limites usando o ficheiro Settings.h
    if (nl > Settings::MAX_LINHAS || nc > Settings::MAX_COLUNAS || nl <= 0 || nc <= 0) {
        return false;
    }

    libertaMemoria(); // Apaga a fábrica antiga
    alocaMemoria(nl, nc); // Cria a nova

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int indice = (i * colunas) + j; // A fórmula matemática
            int chance = rand() % 100; // Gera probabilidade de 0 a 99

            if (chance < 5) {
                grelha[indice].setTipo('#'); // 5% chance de Cratera
            } else if (chance < 15) {
                grelha[indice].setTipo('%'); // 10% chance de Ferro

                // Calcula quantidade aleatória entre o MIN e MAX
                int quantidade = Settings::MIN_MATERIA_DEPOSITO +
                                 rand() % (Settings::MAX_MATERIA_DEPOSITO - Settings::MIN_MATERIA_DEPOSITO + 1);
                grelha[indice].setQuantidade(quantidade);
            } else {
                grelha[indice].setTipo('.'); // 85% de ser solo normal
            }
        }
    }
    return true;
}

bool Fabrica::carregarDeFicheiro(const string& nomeFicheiro) {
    ifstream file(nomeFicheiro);
    if (!file.is_open()) {
        return false;
    }

    int nl, nc;
    if (!(file >> nl >> nc)) {
        return false; // Falhou a ler as dimensões na primeira linha
    }

    // Valida as dimensões
    if (nl > Settings::MAX_LINHAS || nc > Settings::MAX_COLUNAS || nl <= 0 || nc <= 0) {
        return false;
    }

    libertaMemoria();
    alocaMemoria(nl, nc);

    string linhaTexto;
    getline(file, linhaTexto);

    for (int i = 0; i < linhas; ++i) {
        if (!getline(file, linhaTexto)) {
            return false;
        }

        for (int j = 0; j < colunas && j < linhaTexto.size(); ++j) {
            int indice = (i * colunas) + j;
            char c = linhaTexto[j];

            if (c == '.' || c == '#' || c == '%' || c == '$' || c == '~') {
                grelha[indice].setTipo(c);

                if (c == '%' || c == '$' || c == '~') {
                    grelha[indice].setQuantidade(50);
                }
            } else {
                return false;
            }
        }
    }
    return true;
}