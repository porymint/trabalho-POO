//
// Created by Pedro Freitas on 05/11/2026.
//

#ifndef TP_INTERPRETADOR_H
#define TP_INTERPRETADOR_H

#include <string>
#include "Comandos.h"

class Interpretador {
public:
    static Comando* processaLinha(const std::string& linha, std::string& argumentosRestantes);
};

#endif //TP_INTERPRETADOR_H
