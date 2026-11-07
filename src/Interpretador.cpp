//
// Created by Pedro Freitas on 05/11/2026.
//

#include "Interpretador.h"
#include "ComandosGerais.h"
#include "ComandosListagem.h"
#include "Ecra.h"
#include <sstream>

using namespace std;

Comando* Interpretador::processaLinha(const string& linha, string& argumentosRestantes) {
    istringstream iss(linha);
    string comandoBase;

    // Extrai a primeira palavra (o comando)
    iss >> comandoBase;

    // Guarda o resto da frase (os números, letras, etc.) noutra variável
    getline(iss, argumentosRestantes);

    // Devolve o objeto correspondente usando alocação dinâmica
    if (comandoBase == "fim") {
        return new ComandoFim();
    } else if (comandoBase == "fabrica") {
        return new ComandoFabrica();
    } else if (comandoBase == "lposicao") {
        return new ComandoLPosicao();
    }

    return nullptr; // Devolve nulo se a palavra não existir
}

