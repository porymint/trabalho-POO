//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_FABRICA_H
#define TP_FABRICA_H

#include <vector>
#include <string>

struct Terreno {
    char tipo = '.';      // '.' (solo), '#' (cratera), '%' (ferro), '$' (silício), '~' (gelo)
    int quantidade = 0;
};

class Fabrica {
private:
    int linhas;
    int colunas;
    std::vector<std::vector<Terreno>> grelha;

public:
    Fabrica(int nl, int nc);
    bool carregarDeFicheiro(const std::string& nomeFicheiro);
    void gerarAleatorio();

    
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
    const Terreno& getTerreno(int l, int c) const;
    bool posicaoValida(int l, int c) const;
};


#endif //TP_FABRICA_H
