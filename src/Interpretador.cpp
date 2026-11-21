//
// Created by Pedro Freitas on 05/11/2026.
//

#include "Interpretador.h"
#include "ComandosGerais.h"
#include "ComandosListagem.h"
#include "ComandosCriacao.h"
#include "ComandosMaquinas.h"
#include "Ecra.h"
#include <sstream>

using namespace std;

Comando* Interpretador::processaLinha(const string& linha, string& argumentosRestantes) {
    istringstream iss(linha);
    string comandoBase;

    iss >> comandoBase;

    getline(iss, argumentosRestantes);

    if (comandoBase == "fim") {
        return new ComandoFim();
    } else if (comandoBase == "fabrica") {
        return new ComandoFabrica();
    } else if (comandoBase == "lposicao") {
        return new ComandoLPosicao();
    }else if (comandoBase == "carrega") {
        return new ComandoCarrega();
    }else if (comandoBase == "carrega") {
        return new ComandoCarrega();
    } else if (comandoBase == "compra") {
        return new ComandoCompra();
    } else if (comandoBase == "vende") {
        return new ComandoVende();
    } else if (comandoBase == "roda") {
        return new ComandoRoda();
    }

    return nullptr; // Devolve nulo se a palavra não existir
}

