//
// Created by Pedro Freitas on 03/11/2026.
//
#include "Fabrica.h"
#include "Settings.h"
#include "MaquinasDerivadas.h"
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
        int total = linhas * colunas;
        for (int i = 0; i < total; ++i) {
            delete grelha[i].getMaquina();
            grelha[i].setMaquina(nullptr);
        }
        delete[] grelha;
        grelha = nullptr;
    }
    linhas = 0;
    colunas = 0;
}

Fabrica::Fabrica(int nl, int nc) : creditos(Settings::CREDITS_INICIAIS) {
    alocaMemoria(nl, nc);
    srand(static_cast<unsigned int>(time(nullptr)));
}

Fabrica::~Fabrica() {
    libertaMemoria();
}

bool Fabrica::posicaoValida(int l, int c) const {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

const Terreno* Fabrica::getTerreno(int l, int c) const {
    if (posicaoValida(l, c) && grelha != nullptr) {
        int indice = (l * colunas) + c;
        return &grelha[indice];
    }
    return nullptr;
}

Terreno* Fabrica::getTerrenoMutavel(int l, int c) {
    if (posicaoValida(l, c) && grelha != nullptr) {
        return &grelha[(l * colunas) + c];
    }
    return nullptr;
}

bool Fabrica::criarAleatoria(int nl, int nc) {
    if (nl > Settings::MAX_LINHAS || nc > Settings::MAX_COLUNAS || nl <= 0 || nc <= 0) {
        return false;
    }

    libertaMemoria();
    alocaMemoria(nl, nc);
    creditos = Settings::CREDITS_INICIAIS;

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

bool Fabrica::carregarFicheiro(const std::string& nomeFicheiro) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        return false;
    }

    int nl = 0, nc = 0;
    if (!(ficheiro >> nl >> nc)) {
        return false;
    }

    if (nl <= 0 || nc <= 0 || nl > Settings::MAX_LINHAS || nc > Settings::MAX_COLUNAS) {
        return false;
    }

    // Consome o resto da primeira linha após nl e nc
    std::string linha;
    std::getline(ficheiro, linha);

    Terreno* novaGrelha = new Terreno[nl * nc];

    for (int i = 0; i < nl; ++i) {
        if (!std::getline(ficheiro, linha)) {
            delete[] novaGrelha;
            return false;
        }

        // Compatibilidade com quebras de linha CRLF (Windows)
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();
        }

        if (static_cast<int>(linha.size()) != nc) {
            delete[] novaGrelha;
            return false;
        }

        for (int j = 0; j < nc; ++j) {
            char ch = linha[j];
            int idx = (i * nc) + j;

            if (ch == ' ') {
                novaGrelha[idx].setTipo('.');
                novaGrelha[idx].setQuantidade(0);
            } else if (ch == '#') {
                novaGrelha[idx].setTipo('#');
                novaGrelha[idx].setQuantidade(0);
            } else if (ch == '%' || ch == '$' || ch == '~') {
                novaGrelha[idx].setTipo(ch);
                int qtd = Settings::MIN_MATERIA_DEPOSITO +
                          (std::rand() % (Settings::MAX_MATERIA_DEPOSITO - Settings::MIN_MATERIA_DEPOSITO + 1));
                novaGrelha[idx].setQuantidade(qtd);
            } else {
                delete[] novaGrelha;
                return false;
            }
        }
    }

    libertaMemoria();
    linhas = nl;
    colunas = nc;
    grelha = novaGrelha;
    creditos = Settings::CREDITS_INICIAIS;

    return true;
}

bool Fabrica::comprarMaquina(char tipo, int l, int c, char dir) {
    Terreno* t = getTerrenoMutavel(l, c);
    if (t == nullptr) {
        return false;
    }

    // Não pode ser colocada em cima de crateras ('#') nem onde já exista máquina
    if (t->getTipo() == '#' || t->getMaquina() != nullptr) {
        return false;
    }

    if (dir != 'c' && dir != 'b' && dir != 'e' && dir != 'd') {
        return false;
    }

    Maquina* nova = nullptr;
    switch (tipo) {
        case 'P': nova = new Perfuradora(l, c, dir); break;
        case 'T': nova = new Transportador(l, c, dir); break;
        case 'R': nova = new Refinaria(l, c, dir); break;
        case 'O': nova = new Oficina(l, c, dir); break;
        case 'S': nova = new Silo(l, c, dir); break;
        case 'L': nova = new Lancador(l, c, dir); break;
        default:  return false;
    }

    if (creditos < nova->getCusto()) {
        delete nova;
        return false;
    }

    creditos -= nova->getCusto();
    t->setMaquina(nova);
    return true;
}

bool Fabrica::venderMaquina(int l, int c) {
    Terreno* t = getTerrenoMutavel(l, c);
    if (t == nullptr || t->getMaquina() == nullptr) {
        return false;
    }

    Maquina* m = t->getMaquina();
    int reembolso = m->getCusto() / 2;
    creditos += reembolso;

    delete m;
    t->setMaquina(nullptr);
    return true;
}

bool Fabrica::rodarMaquina(int l, int c, char dir) {
    Terreno* t = getTerrenoMutavel(l, c);
    if (t == nullptr || t->getMaquina() == nullptr) {
        return false;
    }
    return t->getMaquina()->setDirecao(dir);
}