//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Comandos.h"

bool Comando::semArgumentos(const std::string& argumentos) {
    return argumentos.find_first_not_of(" \t\r\n") == std::string::npos;
}
