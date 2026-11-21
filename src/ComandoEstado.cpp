//
// Created by Pedro Freitas on 20/11/2026.
//
#include "ComandoEstado.h"
#include "Fabrica.h"
#include <iostream>
#include <sstream>
#include <string>

std::string ComandoEstado::ajuda() {
    return "estado - Apresenta o estado atual da fabrica (instante, creditos, maquinas, engenheiros e totais enviados para a Terra). Uso: estado";
}

void ComandoEstado::executa(Fabrica& fabrica, const std::string& argumentos) {
    std::istringstream iss(argumentos);
    std::string extra;

    if (iss >> extra) {
        std::cout << "Erro: argumentos invalidos.\n" << ajuda() << "\n";
        return;
    }

    std::cout << "=== ESTADO DA FABRICA ===\n";
    std::cout << "Creditos: " << fabrica.getCreditos() << "\n";
    // Nota: liga aqui os getters da Fabrica quando existirem (ex.: instante, contagem de maquinas, engenheiros, totais enviados)
    std::cout << "Instante: 0\n";
    std::cout << "Maquinas ativas: 0\n";
    std::cout << "Engenheiros: 0\n";
    std::cout << "Enviados para a Terra: 0\n";
}