//
// Created by Pedro Freitas on 03/11/2026.
//
#include "Fabrica.h"
#include "Settings.h"
#include "Maquina.h"
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

Fabrica::Fabrica(int nl, int nc)
    : linhas(0), colunas(0), grelha(nullptr),
      instante(0), creditos(Settings::CREDITS_INICIAIS),
      maquinas(nullptr), numMaquinas(0), capacidadeMaquinas(0),
      eventos(nullptr), numEventos(0), capacidadeEventos(0) {
    alocaMemoria(nl, nc);
    srand(time(NULL));
}

Fabrica::~Fabrica() {
    for (int i = 0; i < numMaquinas; ++i) {
        delete maquinas[i];
    }
    delete[] maquinas;
    delete[] eventos;
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

Maquina* Fabrica::getMaquinaPorIndice(int i) const {
    if (i < 0 || i >= numMaquinas) return nullptr;
    return maquinas[i];
}

Maquina* Fabrica::getMaquina(int l, int c) const {
    for (int i = 0; i < numMaquinas; ++i) {
        if (maquinas[i]->getLinha() == l && maquinas[i]->getColuna() == c) {
            return maquinas[i];
        }
    }
    return nullptr;
}

bool Fabrica::adicionaMaquina(Maquina* m) {
    if (m == nullptr) return false;

    const Terreno* t = getTerreno(m->getLinha(), m->getColuna());
    if (t == nullptr || t->getTipo() == '#') return false;
    if (getMaquina(m->getLinha(), m->getColuna()) != nullptr) return false;

    if (numMaquinas == capacidadeMaquinas) aumentaMaquinas();
    maquinas[numMaquinas++] = m;
    return true;
}

void Fabrica::aumentaMaquinas() {
    int novaCapacidade = (capacidadeMaquinas == 0) ? 8 : capacidadeMaquinas * 2;
    Maquina** novo = new Maquina*[novaCapacidade];
    for (int i = 0; i < numMaquinas; ++i) {
        novo[i] = maquinas[i];
    }
    delete[] maquinas;
    maquinas = novo;
    capacidadeMaquinas = novaCapacidade;
}

void Fabrica::aumentaEventos() {
    int novaCapacidade = (capacidadeEventos == 0) ? 8 : capacidadeEventos * 2;
    std::string* novo = new std::string[novaCapacidade];
    for (int i = 0; i < numEventos; ++i) {
        novo[i] = eventos[i];
    }
    delete[] eventos;
    eventos = novo;
    capacidadeEventos = novaCapacidade;
}

void Fabrica::registaEvento(const std::string& texto) {
    if (numEventos == capacidadeEventos) aumentaEventos();
    eventos[numEventos++] = texto;
}

const std::string& Fabrica::getEvento(int i) const {
    return eventos[i];
}

void Fabrica::avancaInstante() {
    ++instante;
    numEventos = 0;   // os strings ficam no array e sao reutilizados

    // Mecanismo de atuacao: cada maquina atua uma vez por instante. A regra
    // "um item so avanca uma posicao por instante" e garantida pelas proprias
    // maquinas (ver Maquina.h), nao pela ordem desta iteracao.
    for (int i = 0; i < numMaquinas; ++i) {
        maquinas[i]->atua(*this);
    }

    // Entrega final: pagamento dos salarios dos engenheiros e regra dos
    // creditos <= 0 entram aqui.
}
