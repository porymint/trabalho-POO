//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_MAQUINASDERIVADAS_H
#define TP_MAQUINASDERIVADAS_H

#include "Maquina.h"

// Silo: guarda itens de qualquer tipo, sem limite de capacidade.
// Armazenamento: lista ligada simples gerida a mao (fila FIFO). Cada item
// guardado ocupa exatamente um no, logo nao se gasta mais memoria do que a
// necessaria. Nao usa nenhuma colecao da biblioteca standard.
class Silo : public Maquina {
private:
    struct No {
        Item item;
        int instanteEntrada;
        No* seguinte;

        No(const Item& i, int instante) : item(i), instanteEntrada(instante), seguinte(nullptr) {}
    };

    No* primeiro;   // item guardado ha mais tempo
    No* ultimo;     // item mais recente
    int quantidade;
    int probabilidadePerda;   // percentagem

    void acrescenta(const Item& item, int instante);
    void removePrimeiro();
    void liberta();
    void copiaDe(const Silo& outro);

public:
    Silo(int linha, int coluna, char direcao);
    Silo(const Silo& outro);
    Silo& operator=(const Silo& outro);
    ~Silo() override;

    int getQuantidade() const { return quantidade; }

    char getSimbolo() const override;
    std::string getNome() const override;
    std::string getDescricao() const override;

    bool aceita(const Item& item) const override;
    void recebe(const Item& item, int instante) override;
    void atua(Fabrica& fabrica) override;
};

#endif //TP_MAQUINASDERIVADAS_H
