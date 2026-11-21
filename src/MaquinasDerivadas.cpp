//
// Created by Pedro Freitas on 03/11/2026.
//
#include "MaquinasDerivadas.h"

// --- Perfuradora ---
Perfuradora::Perfuradora(int linha, int coluna, char direcao)
        : Maquina('P', linha, coluna, direcao, Settings::CUSTO_PERFURADORA),
          probPerda(Settings::PERFURADORA_PROB_PERDA_INICIAL),
          temItemPendente(false),
          itemPendente('\0') {}

char Perfuradora::getSimbolo() const {
    return 'P';
}

std::string Perfuradora::getDescricao() const {
    return "Perfuradora (P) - perda: " + std::to_string(probPerda) + "%";
}

bool Perfuradora::melhorar() {
    if (probPerda <= 0) {
        return false;
    }
    probPerda -= 10;
    if (probPerda < 0) {
        probPerda = 0;
    }
    return true;
}

int Perfuradora::getProbPerda() const {
    return probPerda;
}

// --- Transportador ---
Transportador::Transportador(int linha, int coluna, char direcao)
        : Maquina('T', linha, coluna, direcao, Settings::CUSTO_TRANSPORTADOR),
          ocupado(false),
          itemAtual('\0') {}

char Transportador::getSimbolo() const {
    if (ocupado && itemAtual != '\0') {
        return itemAtual;
    }
    switch (getDirecao()) {
        case 'c': return '^';
        case 'b': return 'v';
        case 'e': return '<';
        case 'd': return '>';
        default:  return 'T';
    }
}

std::string Transportador::getDescricao() const {
    return "Transportador (T) - direcao: " + std::string(1, getDirecao());
}

bool Transportador::estaOcupado() const {
    return ocupado;
}

char Transportador::getItemAtual() const {
    return itemAtual;
}

// --- Refinaria ---
Refinaria::Refinaria(int linha, int coluna, char direcao)
        : Maquina('R', linha, coluna, direcao, Settings::CUSTO_REFINARIA),
          instantesRestantes(0),
          aTransformar(false),
          temProdutoPronto(false),
          itemEntrada('\0'),
          produtoPronto('\0') {}

std::string Refinaria::getDescricao() const {
    return "Refinaria (R) - direcao: " + std::string(1, getDirecao());
}

// --- Oficina ---
Oficina::Oficina(int linha, int coluna, char direcao)
        : Maquina('O', linha, coluna, direcao, Settings::CUSTO_OFICINA),
          ferroAcumulado(0),
          silicioAcumulado(0),
          aguaAcumulada(0),
          tempoProducao(Settings::OFICINA_TEMPO_PRODUCAO),
          instantesRestantes(0),
          aProduzir(false),
          temKitPronto(false),
          melhoriaUsada(false) {}

std::string Oficina::getDescricao() const {
    return "Oficina (O) - tempo: " + std::to_string(tempoProducao) + " instantes";
}

bool Oficina::melhorarVelocidade() {
    if (melhoriaUsada || tempoProducao <= 1) {
        return false;
    }
    tempoProducao -= 1;
    melhoriaUsada = true;
    return true;
}

// --- Silo ---
Silo::Silo(int linha, int coluna, char direcao)
        : Maquina('S', linha, coluna, direcao, Settings::CUSTO_SILO),
          probPerda(Settings::SILO_PROB_PERDA_INICIAL) {}

std::string Silo::getDescricao() const {
    return "Silo (S) - guardados: " + std::to_string(itensGuardados.size()) +
           ", perda: " + std::to_string(probPerda) + "%";
}

bool Silo::melhorar() {
    if (probPerda <= 0) {
        return false;
    }
    probPerda -= 5;
    if (probPerda < 0) {
        probPerda = 0;
    }
    return true;
}

int Silo::getProbPerda() const {
    return probPerda;
}

// --- Lancador ---
Lancador::Lancador(int linha, int coluna, char direcao)
        : Maquina('L', linha, coluna, direcao, Settings::CUSTO_LANCADOR),
          probPerda(Settings::LANCADOR_PROB_PERDA_INICIAL),
          temItemPorLancar(false),
          itemPorLancar('\0'),
          contadorInstantes(0) {}

std::string Lancador::getDescricao() const {
    return "Lancador (L) - perda: " + std::to_string(probPerda) + "%";
}

bool Lancador::melhorar() {
    if (probPerda <= 0) {
        return false;
    }
    probPerda -= 10;
    if (probPerda < 0) {
        probPerda = 0;
    }
    return true;
}

int Lancador::getProbPerda() const {
    return probPerda;
}
