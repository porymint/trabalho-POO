//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_MAQUINA_H
#define TP_MAQUINA_H

#include <string>
#include "Item.h"

class Fabrica;

// Classe base abstrata de todas as maquinas.
//
// Regra "um item avanca no maximo uma posicao por instante": quando uma maquina
// recebe um item guarda o instante da rececao (parametro de recebe()) e so o
// entrega a partir do instante seguinte. Assim o resultado nao depende da ordem
// pela qual a Fabrica processa as maquinas.
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

    // Posicao em texto, ex.: "ce".
    std::string getPosicao() const;

    // Maquina vizinha na direcao de saida (nullptr se nao existir).
    Maquina* getVizinha(const Fabrica& fabrica) const;

    virtual char getSimbolo() const = 0;
    virtual std::string getNome() const = 0;
    virtual std::string getDescricao() const = 0;

    // Aceita este item neste momento?
    virtual bool aceita(const Item& item) const = 0;
    // Recebe o item (so chamar depois de aceita() devolver true).
    virtual void recebe(const Item& item, int instante) = 0;
    // Comportamento da maquina num instante.
    virtual void atua(Fabrica& fabrica) = 0;
};

#endif //TP_MAQUINA_H
