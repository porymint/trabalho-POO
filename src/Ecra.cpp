//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Ecra.h"
#include "Fabrica.h"
#include <iostream>


using namespace std;

Ecra::Ecra() : cursorLinha(0), cursorColuna(0) {
    limpa();
}

void Ecra::limpa() {
    for (int i = 0; i < Max_Linhas; ++i) {
        for (int j = 0; j < Max_Colunas; ++j) {
            buffer[i][j] = ' ';
        }
    }
    cursorLinha = 0;
    cursorColuna = 0;
}

void Ecra::mostra() const {
    for (int i = 0; i < Max_Linhas; ++i) {
        for (int j = 0; j < Max_Colunas; ++j) {
            cout << buffer[i][j];
        }
        cout << '\n';
    }
}

void Ecra::posicionaCursor(int linha, int coluna) {
    cursorLinha = linha;
    cursorColuna = coluna;
}

void Ecra::escreve(char c) {
    if (cursorLinha >= 0 && cursorLinha < Max_Linhas &&
        cursorColuna >= 0 && cursorColuna < Max_Colunas) {

        buffer[cursorLinha][cursorColuna] = c;
    }
    cursorColuna++;
}

void Ecra::escreve(const std::string& texto) {
    for (char letra : texto) {
        escreve(letra);
    }
}

void Ecra::desenhaEcra(int linha, int coluna, int altura, int largura) {
    for (int i = 0; i < largura; ++i) {
        posicionaCursor(linha, coluna + i);
        escreve('-');
        posicionaCursor(linha + altura - 1, coluna + i);
        escreve('-');
    }

    for (int i = 0; i < altura; ++i) {
        posicionaCursor(linha + i, coluna);
        escreve('|');
        posicionaCursor(linha + i, coluna + largura - 1);
        escreve('|');
    }

    posicionaCursor(linha, coluna); escreve('+');
    posicionaCursor(linha, coluna + largura - 1); escreve('+');
    posicionaCursor(linha + altura - 1, coluna); escreve('+');
    posicionaCursor(linha + altura - 1, coluna + largura - 1); escreve('+');
}

void Ecra::desenhaFabrica(const Fabrica& fabrica, int linhaInicio, int colunaInicio) {
    int linhas = fabrica.getLinhas();
    int colunas = fabrica.getColunas();

    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            const Terreno* t = fabrica.getTerreno(l, c);

            if (t != nullptr) {
                posicionaCursor(linhaInicio + l, colunaInicio + c);
                escreve(t->getTipo());
            }
        }
    }
}