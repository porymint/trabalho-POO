//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_MAQUINA_H
#define TP_MAQUINA_H

#include <string>
#include "Item.h"

class Fabrica;
class Maquina {
private:
    int linha;
    int coluna;
    char direcao;   // 'c', 'b', 'e' ou 'd'

public:
    Maquina(int linha, int coluna, char direcao);
    Maquina(const Maquina&) = default;
    Maquina& operator=(const Maquina&) = default;
    virtual ~Maquina() = default;

    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    char getDirecao() const { return direcao; }
    void setDirecao(char d) { direcao = d; }

    std::string getPosicao() const;
    Maquina* getVizinha(const Fabrica& fabrica) const;

    virtual char getSimbolo() const = 0;
    virtual std::string getNome() const = 0;
    virtual std::string getDescricao() const = 0;

    virtual bool aceita(const Item& item) const = 0;
    virtual void recebe(const Item& item, int instante) = 0;
    virtual void atua(Fabrica& fabrica) = 0;
};

#endif //TP_MAQUINA_H
