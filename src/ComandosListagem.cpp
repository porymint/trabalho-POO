#include "ComandosListagem.h"
#include "Contexto.h"
#include "Fabrica.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

bool ComandoLPosicao::executa(Contexto& contexto, const std::string& argumentos) {
    Fabrica& fabrica = contexto.getFabrica();
    std::stringstream ss(argumentos);
    std::string lc;
    int n = 0;

    if (!(ss >> lc)) {
        std::cout << "Erro: Deve indicar a posicao (ex: lposicao df)." << std::endl;
        return false;
    }
    if (!(ss >> n)) {
        n = 0;
    }

    if (lc.length() != 2 ||
        !isalpha(static_cast<unsigned char>(lc[0])) || !isalpha(static_cast<unsigned char>(lc[1]))) {
        std::cout << "Erro: Formato de posicao invalido. Use duas letras (ex: aa, df)." << std::endl;
        return false;
    }
    if (n < 0) {
        std::cout << "Erro: O raio n nao pode ser negativo." << std::endl;
        return false;
    }
    int linhaCentro = tolower(static_cast<unsigned char>(lc[0])) - 'a';
    int colunaCentro = tolower(static_cast<unsigned char>(lc[1])) - 'a';

    int maxLinhas = fabrica.getLinhas();
    int maxColunas = fabrica.getColunas();

    if (maxLinhas == 0 || maxColunas == 0) {
        std::cout << "Erro: A fabrica ainda nao foi criada." << std::endl;
        return false;
    }

    if (!fabrica.posicaoValida(linhaCentro, colunaCentro)) {
        std::cout << "Erro: Posicao fora dos limites da fabrica." << std::endl;
        return false;
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
    return false;   // so consulta: nao altera o estado
}

std::string ComandoLPosicao::ajudaResumida() const {
    return "lposicao <lc> [n]      mostra a informacao de uma posicao (ou do quadrado de raio n)";
}

std::string ComandoLPosicao::ajudaDetalhada() const {
    return "lposicao <lc> [n]\n"
           "  lc : posicao da fabrica, duas letras (linha e coluna), ex.: df.\n"
           "  n  : (opcional) raio inteiro >= 0; mostra todas as posicoes do quadrado\n"
           "       de raio n centrado em lc.\n"
           "  Mostra o tipo de terreno (e a quantidade de materia-prima, se for deposito).\n"
           "  Falha se faltar a posicao, se o formato for invalido, se estiver fora da\n"
           "  fabrica ou se n for negativo.\n"
           "  Exemplo: lposicao df 2\n";
}
