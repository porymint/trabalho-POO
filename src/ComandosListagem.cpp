#include "ComandosListagem.h"
#include "Fabrica.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

void ComandoLPosicao::executa(Fabrica& fabrica, const std::string& argumentos) {
    std::stringstream ss(argumentos);
    std::string lc;
    int n = 0;

    if (!(ss >> lc)) {
        std::cout << "Erro: Deve indicar a posicao (ex: lposicao df)." << std::endl;
        return;
    }
    if (!(ss >> n)) {
        n = 0;
    }

    if (lc.length() < 2 || !isalpha(lc[0]) || !isalpha(lc[1])) {
        std::cout << "Erro: Formato de posicao invalido. Use duas letras (ex: aa, df)." << std::endl;
        return;
    }
    int linhaCentro = tolower(lc[0]) - 'a';
    int colunaCentro = tolower(lc[1]) - 'a';

    int maxLinhas = fabrica.getLinhas();
    int maxColunas = fabrica.getColunas();

    if (maxLinhas == 0 || maxColunas == 0) {
        std::cout << "Erro: A fabrica ainda nao foi criada." << std::endl;
        return;
    }

    if (!fabrica.posicaoValida(linhaCentro, colunaCentro)) {
        std::cout << "Erro: Posicao fora dos limites da fabrica." << std::endl;
        return;
    }
    int lInicio = std::max(0, linhaCentro - n);
    int lFim = std::min(maxLinhas - 1, linhaCentro + n);
    int cInicio = std::max(0, colunaCentro - n);
    int cFim = std::min(maxColunas - 1, colunaCentro + n);

    std::cout << "\n--- Informacao da(s) Posicao(oes) ---" << std::endl;
    for (int l = lInicio; l <= lFim; ++l) {
        for (int c = cInicio; c <= cFim; ++c) {
            char nomeL = 'A' + l;
            char nomeC = 'A' + c;
            const Terreno* terreno = fabrica.getTerreno(l, c);
            
            if (terreno != nullptr) {
                char tipo = terreno->getTipo();
                std::string desc;

                if (tipo == '.') {
                    desc = "Solo vazio";
                } else if (tipo == '#') {
                    desc = "Cratera (#)";
                } else if (tipo == '%') {
                    desc = "Deposito de ferro (%) - Quantidade: " + std::to_string(terreno->getQuantidade());
                } else if (tipo == '$') {
                    desc = "Deposito de silicio ($) - Quantidade: " + std::to_string(terreno->getQuantidade());
                } else if (tipo == '~') {
                    desc = "Deposito de gelo (~) - Quantidade: " + std::to_string(terreno->getQuantidade());
                } else {
                    desc = "Desconhecido";
                }

                std::cout << "[" << nomeL << nomeC << "] " << desc << std::endl;
            }
        }
    }
}