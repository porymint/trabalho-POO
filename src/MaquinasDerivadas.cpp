//
// Created by Pedro Freitas on 03/11/2026.
//

#include "MaquinasDerivadas.h"
#include "Fabrica.h"
#include "Settings.h"
#include <cstdlib>

// ---------------------------------------------------------------- Silo

Silo::Silo(int linha, int coluna, char direcao)
    : Maquina(linha, coluna, direcao),
      primeiro(nullptr), ultimo(nullptr), quantidade(0),
      probabilidadePerda(Settings::PROB_PERDA_SILO) {}

Silo::Silo(const Silo& outro)
    : Maquina(outro),
      primeiro(nullptr), ultimo(nullptr), quantidade(0),
      probabilidadePerda(outro.probabilidadePerda) {
    copiaDe(outro);
}

Silo& Silo::operator=(const Silo& outro) {
    if (this != &outro) {
        Maquina::operator=(outro);
        liberta();
        probabilidadePerda = outro.probabilidadePerda;
        copiaDe(outro);
    }
    return *this;
}

Silo::~Silo() {
    liberta();
}

void Silo::acrescenta(const Item& item, int instante) {
    No* novo = new No(item, instante);
    if (ultimo == nullptr) {
        primeiro = ultimo = novo;
    } else {
        ultimo->seguinte = novo;
        ultimo = novo;
    }
    ++quantidade;
}

void Silo::removePrimeiro() {
    if (primeiro == nullptr) return;

    No* removido = primeiro;
    primeiro = primeiro->seguinte;
    if (primeiro == nullptr) ultimo = nullptr;
    delete removido;
    --quantidade;
}

void Silo::liberta() {
    while (primeiro != nullptr) {
        removePrimeiro();
    }
}

void Silo::copiaDe(const Silo& outro) {
    for (const No* n = outro.primeiro; n != nullptr; n = n->seguinte) {
        acrescenta(n->item, n->instanteEntrada);
    }
}

char Silo::getSimbolo() const { return 'S'; }

std::string Silo::getNome() const { return "Silo"; }

std::string Silo::getDescricao() const {
    std::string conteudo;
    for (const No* n = primeiro; n != nullptr; n = n->seguinte) {
        conteudo += n->item.getSimbolo();
    }

    return "Silo (S) em " + getPosicao() + ", saida: " + getDirecao() +
           ", itens: " + std::to_string(quantidade) +
           (conteudo.empty() ? "" : " [" + conteudo + "]") +
           ", prob. perda: " + std::to_string(probabilidadePerda) + "%";
}

// Sem limite de capacidade: aceita sempre.
bool Silo::aceita(const Item&) const {
    return true;
}

void Silo::recebe(const Item& item, int instante) {
    acrescenta(item, instante);
}

void Silo::atua(Fabrica& fabrica) {
    if (primeiro == nullptr) return;

    // Item que acabou de chegar neste instante so "age" no seguinte.
    if (primeiro->instanteEntrada >= fabrica.getInstante()) return;

    // Probabilidade de se perder o item guardado ha mais tempo.
    if (std::rand() % 100 < probabilidadePerda) {
        fabrica.registaEvento("silo em " + getPosicao() + " perdeu " + primeiro->item.getNome());
        removePrimeiro();
        return;
    }

    // Tenta entregar o item mais antigo na direcao de saida.
    Maquina* destino = getVizinha(fabrica);
    if (destino != nullptr && destino->aceita(primeiro->item)) {
        destino->recebe(primeiro->item, fabrica.getInstante());
        removePrimeiro();
    }
}
