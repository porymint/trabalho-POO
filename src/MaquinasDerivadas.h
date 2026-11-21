//
// Created by Pedro Freitas on 03/11/2026.
//
#ifndef TP_MAQUINASDERIVADAS_H
#define TP_MAQUINASDERIVADAS_H

#include "Maquina.h"
#include "Settings.h"
#include <vector>
#include <string>

class Perfuradora : public Maquina {
private:
    int probPerda;
    bool temItemPendente;
    char itemPendente;

public:
    Perfuradora(int linha, int coluna, char direcao);
    char getSimbolo() const override;
    std::string getDescricao() const override;
    bool melhorar();
    int getProbPerda() const;
};

class Transportador : public Maquina {
private:
    bool ocupado;
    char itemAtual;

public:
    Transportador(int linha, int coluna, char direcao);
    char getSimbolo() const override;
    std::string getDescricao() const override;
    bool estaOcupado() const;
    char getItemAtual() const;
};

class Refinaria : public Maquina {
private:
    int instantesRestantes;
    bool aTransformar;
    bool temProdutoPronto;
    char itemEntrada;
    char produtoPronto;

public:
    Refinaria(int linha, int coluna, char direcao);
    std::string getDescricao() const override;
};

class Oficina : public Maquina {
private:
    int ferroAcumulado;
    int silicioAcumulado;
    int aguaAcumulada;
    int tempoProducao;
    int instantesRestantes;
    bool aProduzir;
    bool temKitPronto;
    bool melhoriaUsada;

public:
    Oficina(int linha, int coluna, char direcao);
    std::string getDescricao() const override;
    bool melhorarVelocidade();
};

class Silo : public Maquina {
private:
    int probPerda;
    std::vector<char> itensGuardados;

public:
    Silo(int linha, int coluna, char direcao);
    std::string getDescricao() const override;
    bool melhorar();
    int getProbPerda() const;
};

class Lancador : public Maquina {
private:
    int probPerda;
    bool temItemPorLancar;
    char itemPorLancar;
    int contadorInstantes;

public:
    Lancador(int linha, int coluna, char direcao);
    std::string getDescricao() const override;
    bool melhorar();
    int getProbPerda() const;
};

#endif //TP_MAQUINASDERIVADAS_H
