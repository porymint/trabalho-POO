#ifndef MAPA_H
#define MAPA_H

#include <string>
#include <vector>

enum TipoTerreno { SOLO, CRATERA, DEPOSITO_FERRO, DEPOSITO_SILICIO, DEPOSITO_GELO };

struct PosicaoTerreno {
    TipoTerreno tipo;
    int quantidadeMateriaPrima = 0;
};

class Mapa {
    int linhas;
    int colunas;
    std::vector<std::vector<PosicaoTerreno>> grelha;

public:
    Mapa(int nl, int nc);
    bool carregarDeFicheiro(const std::string& nomeFicheiro);
    void gerarAleatorio();
    
    PosicaoTerreno getPosicao(int linha, int coluna) const;
    bool dentroDosLimites(int linha, int coluna) const;
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
};

#endif