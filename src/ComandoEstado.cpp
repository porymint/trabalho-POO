//
// Created by Pedro Freitas on 20/11/2026.
//
#include "ComandoEstado.h"
#include "Contexto.h"
#include "Fabrica.h"
#include <iostream>
#include <sstream>
#include <string>

std::string ComandoEstado::ajudaResumida() const {
    return "estado               apresenta o estado atual da fabrica";
}

std::string ComandoEstado::ajudaDetalhada() const {
    return "estado\n"
           "  Apresenta o estado atual da fabrica (instante, creditos, dimensoes,\n"
           "  maquinas ativas e eventos recentes).\n"
           "  Nao recebe argumentos.\n"
           "  Exemplo: estado\n";
}

bool ComandoEstado::executa(Contexto& contexto, const std::string& argumentos) {
    const Fabrica& fabrica = contexto.getFabrica();
    std::istringstream iss(argumentos);
    std::string extra;

    if (iss >> extra) {
        std::cout << "Erro: argumentos invalidos.\n" << ajudaResumida() << "\n";
        return false;
    }

    std::cout << "=== ESTADO DA FABRICA ===\n";
    std::cout << "Instante: " << fabrica.getInstante() << "\n";
    std::cout << "Creditos: " << fabrica.getCreditos() << "\n";
    std::cout << "Dimensoes: " << fabrica.getLinhas() << "x" << fabrica.getColunas() << "\n";
    std::cout << "Maquinas ativas: " << fabrica.getNumMaquinas() << "\n";
    return false;
}