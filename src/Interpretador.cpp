//
// Created by Pedro Freitas on 05/11/2026.
//

#include "Interpretador.h"
#include "Contexto.h"
#include "Fabrica.h"
#include "ComandosCriacao.h"
#include "ComandosMaquinas.h"
#include "ComandoEstado.h"
#include "ComandosValidacaoFinal.h"
#include "ComandosGerais.h"
#include "ComandosListagem.h"
#include "ComandosTempo.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace {
    template <class T>
    Comando* cria() { return new T(); }

    typedef Comando* (*Criador)();

    // Registo dos comandos. Para acrescentar um comando novo basta incluir aqui
    // uma linha (e o #include do respetivo header): processaLinha e ajuda passam
    // a conhece-lo automaticamente.
    const Criador CRIADORES[] = {
            &cria<ComandoFabrica>,
            &cria<ComandoCarrega>,
            &cria<ComandoCompra>,
            &cria<ComandoVende>,
            &cria<ComandoRoda>,
            &cria<ComandoEstado>,
            &cria<ComandoMelhora>,
            &cria<ComandoContrata>,
            &cria<ComandoAtribui>,
            &cria<ComandoDespede>,
            &cria<ComandoGrava>,
            &cria<ComandoRecupera>,
            &cria<ComandoAvanca>,
            &cria<ComandoLPosicao>,
            &cria<ComandoExecuta>,
            &cria<ComandoAjuda>,
            &cria<ComandoFim>
    };

    const int NUM_COMANDOS = static_cast<int>(sizeof(CRIADORES) / sizeof(CRIADORES[0]));

    bool linhaEmBranco(const string& linha) {
        return linha.find_first_not_of(" \t\r\n") == string::npos;
    }
}

int Interpretador::numComandos() {
    return NUM_COMANDOS;
}

Comando* Interpretador::criaComandoPorIndice(int indice) {
    if (indice < 0 || indice >= NUM_COMANDOS) return nullptr;
    return CRIADORES[indice]();
}

Comando* Interpretador::criaComando(const string& nome) {
    for (int i = 0; i < NUM_COMANDOS; ++i) {
        Comando* cmd = CRIADORES[i]();
        if (cmd->getNome() == nome) {
            return cmd;
        }
        delete cmd;
    }
    return nullptr;
}

Comando* Interpretador::processaLinha(const string& linha, string& argumentosRestantes) {
    istringstream iss(linha);
    string comandoBase;

    argumentosRestantes.clear();
    if (!(iss >> comandoBase)) {
        return nullptr;
    }
    getline(iss, argumentosRestantes);

    return criaComando(comandoBase);   // nullptr se a palavra nao existir
}

void Interpretador::executaLinha(Contexto& contexto, const string& linha) {
    if (linhaEmBranco(linha)) return;

    string argumentos;
    Comando* cmd = processaLinha(linha, argumentos);

    if (cmd == nullptr) {
        cout << "Erro: Comando nao reconhecido. Use 'ajuda' para ver os comandos." << endl;
        return;
    }

    const Fabrica& fabrica = contexto.getFabrica();
    const bool fabricaCriada = fabrica.getLinhas() > 0 && fabrica.getColunas() > 0;

    if (cmd->requerFabrica() && !fabricaCriada) {
        cout << "Erro: A fabrica ainda nao foi criada. Use 'fabrica <nl> <nc>' primeiro." << endl;
    } else if (cmd->criaFabrica() && fabricaCriada) {
        cout << "Erro: A fabrica ja foi criada; este comando nao pode ser usado novamente." << endl;
    } else if (cmd->executa(contexto, argumentos)) {
        contexto.apresenta();
    }

    delete cmd;   // todos os comandos criados com new terminam aqui
}