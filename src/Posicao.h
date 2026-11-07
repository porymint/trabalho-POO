//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_POSICAO_H
#define TP_POSICAO_H

#include <string>

class Posicao {
public:
    enum TipoTerreno { VAZIO, CRATERA, FERRO, SILICIO, GELO };

private:
    TipoTerreno terreno;
    int quantidade;

public:
    Posicao();
    Posicao(TipoTerreno t, int qtd = 0);

    TipoTerreno getTerreno() const;
    void setTerreno(TipoTerreno t, int qtd = 0);
    int getQuantidade() const;

    char getSimbolo() const;
    std::string getDescricao() const;
};

#endif //TP_POSICAO_H
