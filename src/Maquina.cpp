//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Maquina.h"
#include "Fabrica.h"

Maquina::Maquina(int linha, int coluna, char direcao)
    : linha(linha), coluna(coluna), direcao(direcao) {}

std::string Maquina::getPosicao() const {
    std::string pos;
    pos += static_cast<char>('a' + linha);
    pos += static_cast<char>('a' + coluna);
    return pos;
}

Maquina* Maquina::getVizinha(const Fabrica& fabrica) const {
    int l = linha;
    int c = coluna;

    switch (direcao) {
        case 'c': --l; break;
        case 'b': ++l; break;
        case 'e': --c; break;
        case 'd': ++c; break;
        default: return nullptr;
    }
    return fabrica.getMaquina(l, c);
}
