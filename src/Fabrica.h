//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_FABRICA_H
#define TP_FABRICA_H

#include <string>
#include "Maquina.h"
#include "Settings.h"

class Terreno {
private:
    char tipo = '.';
    int quantidade = 0;
    Maquina* maquina = nullptr;

public:
    char getTipo() const { return tipo; }
    int getQuantidade() const { return quantidade; }
    Maquina* getMaquina() const { return maquina; }

    void setTipo(char t) { tipo = t; }
    void setQuantidade(int q) { quantidade = q; }
    void setMaquina(Maquina* m) { maquina = m; }
};

class Fabrica {
private:
    int linhas;
    int colunas;
    int creditos;
    Terreno* grelha;

    void alocaMemoria(int nl, int nc);
    void libertaMemoria();
    Terreno* getTerrenoMutavel(int l, int c);

public:
    Fabrica(int nl = 0, int nc = 0);
    ~Fabrica();

    Fabrica(const Fabrica& outra) = delete;
    Fabrica& operator=(const Fabrica& outra) = delete;

    bool criarAleatoria(int nl, int nc);
    bool carregarFicheiro(const std::string& nomeFicheiro);

    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
    int getCreditos() const { return creditos; }

    const Terreno* getTerreno(int l, int c) const;
    bool posicaoValida(int l, int c) const;

    bool comprarMaquina(char tipo, int l, int c, char dir);
    bool venderMaquina(int l, int c);
    bool rodarMaquina(int l, int c, char dir);
};

#endif //TP_FABRICA_H