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

namespace {
    class MaquinaBaseSimples : public Maquina {
    private:
        char tipoSimbolo;
        int custoMaquina;

    public:
        MaquinaBaseSimples(char tipo, int l, int c, char dir, int custo)
                : Maquina(l, c, dir), tipoSimbolo(tipo), custoMaquina(custo) {}

        char getSimbolo() const override { return tipoSimbolo; }
        std::string getNome() const override { return std::string("Maquina ") + tipoSimbolo; }
        std::string getDescricao() const override { return "Maquina do tipo " + std::string(1, tipoSimbolo); }
        bool aceita(const Item&) const override { return false; }
        void recebe(const Item&, int) override {}
        void atua(Fabrica&) override {}
        int getCusto() const { return custoMaquina; }
    };

    int custoPorTipo(char tipo) {
        switch (tipo) {
            case 'S': return Settings::CUSTO_SILO;
            case 'P':
            case 'T':
            case 'R':
            case 'O':
            case 'L': return 50;
            default:  return -1;
        }
    }
}

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
    linhas = 0;
    colunas = 0;
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

Fabrica::Fabrica(int nl, int nc)
        : linhas(0), colunas(0), grelha(nullptr),
          instante(0), creditos(Settings::CREDITS_INICIAIS),
          maquinas(nullptr), numMaquinas(0), capacidadeMaquinas(0),
          eventos(nullptr), numEventos(0), capacidadeEventos(0) {
    alocaMemoria(nl, nc);
    srand(static_cast<unsigned int>(time(nullptr)));
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
    if (posicaoValida(l, c) && grelha != nullptr) {
        int indice = (l * colunas) + c;
        return &grelha[indice];
    }
    return nullptr;
}

bool Fabrica::criarAleatoria(int nl, int nc) {
    if (nl > Settings::MAX_LINHAS || nc > Settings::MAX_COLUNAS || nl <= 0 || nc <= 0) {
        return false;
    }

    for (int i = 0; i < numMaquinas; ++i) {
        delete maquinas[i];
    }
    numMaquinas = 0;
    numEventos = 0;
    instante = 0;
    creditos = Settings::CREDITS_INICIAIS;

    libertaMemoria();
    alocaMemoria(nl, nc);

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int indice = (i * colunas) + j;
            int chance = rand() % 100;

            if (chance < 5) {
                grelha[indice].setTipo('#');
                grelha[indice].setQuantidade(0);
            } else if (chance < 15) {
                grelha[indice].setTipo('%');
                int quantidade = Settings::MIN_MATERIA_DEPOSITO +
                                 rand() % (Settings::MAX_MATERIA_DEPOSITO - Settings::MIN_MATERIA_DEPOSITO + 1);
                grelha[indice].setQuantidade(quantidade);
            } else {
                grelha[indice].setTipo('.');
                grelha[indice].setQuantidade(0);
            }
        }
    }
    return true;
}

bool Fabrica::carregarDeFicheiro(const std::string& nomeFicheiro) {
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

    std::string linha;
    std::getline(ficheiro, linha);

    Terreno* novaGrelha = new Terreno[nl * nc];

    for (int i = 0; i < nl; ++i) {
        if (!std::getline(ficheiro, linha)) {
            delete[] novaGrelha;
            return false;
        }

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

            if (ch == ' ' || ch == '.') {
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

    for (int i = 0; i < numMaquinas; ++i) {
        delete maquinas[i];
    }
    numMaquinas = 0;
    numEventos = 0;
    instante = 0;
    creditos = Settings::CREDITS_INICIAIS;

    libertaMemoria();
    linhas = nl;
    colunas = nc;
    grelha = novaGrelha;

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

bool Fabrica::comprarMaquina(char tipo, int l, int c, char dir) {
    if (!posicaoValida(l, c)) {
        return false;
    }

    const Terreno* t = getTerreno(l, c);
    if (t == nullptr || t->getTipo() == '#' || getMaquina(l, c) != nullptr) {
        return false;
    }

    if (dir != 'c' && dir != 'b' && dir != 'e' && dir != 'd') {
        return false;
    }

    int custo = custoPorTipo(tipo);
    if (custo < 0 || creditos < custo) {
        return false;
    }

    Maquina* nova = new MaquinaBaseSimples(tipo, l, c, dir, custo);
    creditos -= custo;
    if (!adicionaMaquina(nova)) {
        creditos += custo;
        delete nova;
        return false;
    }

    return true;
}

bool Fabrica::venderMaquina(int l, int c) {
    Maquina* m = getMaquina(l, c);
    if (m == nullptr) {
        return false;
    }

    int custo = 0;
    if (auto* mSimples = dynamic_cast<MaquinaBaseSimples*>(m)) {
        custo = mSimples->getCusto();
    } else {
        int cTipo = custoPorTipo(m->getSimbolo());
        if (cTipo > 0) custo = cTipo;
    }

    creditos += custo / 2;

    // Retira do array, deslocando os seguintes uma posicao para tras.
    for (int i = 0; i < numMaquinas; ++i) {
        if (maquinas[i] == m) {
            for (int j = i; j < numMaquinas - 1; ++j) {
                maquinas[j] = maquinas[j + 1];
            }
            --numMaquinas;
            break;
        }
    }

    delete m;
    return true;
}

bool Fabrica::rodarMaquina(int l, int c, char dir) {
    Maquina* m = getMaquina(l, c);
    if (m == nullptr) {
        return false;
    }
    m->setDirecao(dir);
    return true;
}

void Fabrica::registaEvento(const std::string& texto) {
    if (numEventos == capacidadeEventos) aumentaEventos();
    eventos[numEventos++] = texto;
}

void Fabrica::avancaInstante() {
    ++instante;
    numEventos = 0;   // os strings ficam no array e sao reutilizados

    // Cada maquina atua uma vez por instante.
    for (int i = 0; i < numMaquinas; ++i) {
        maquinas[i]->atua(*this);
    }

    // Entrega final: salarios dos engenheiros e regra dos creditos <= 0.
}
