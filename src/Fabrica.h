//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_FABRICA_H
#define TP_FABRICA_H

#include <string>

class Terreno {
private:
    char tipo = '.';
    int quantidade = 0;

public:
    char getTipo() const { return tipo; }
    int getQuantidade() const { return quantidade; }

    void setTipo(char t) { tipo = t; }
    void setQuantidade(int q) { quantidade = q; }
};

class Fabrica {
private:
    int linhas;
    int colunas;

    // Um ponteiro para o array dinâmico contínuo
    Terreno* grelha;

    void alocaMemoria(int nl, int nc);
    void libertaMemoria();

public:
    Fabrica(int nl = 0, int nc = 0);
    ~Fabrica();

    Fabrica(const Fabrica& outra) = delete;
    Fabrica& operator=(const Fabrica& outra) = delete;

    bool carregarDeFicheiro(const std::string& nomeFicheiro);
    bool criarAleatoria(int nl, int nc);

    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }

    const Terreno* getTerreno(int l, int c) const;
    bool posicaoValida(int l, int c) const;
};

#endif //TP_FABRICA_H