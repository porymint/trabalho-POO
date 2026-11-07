//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_COMANDOS_H
#define TP_COMANDOS_H
#include <string>

class Fabrica;

class Comando {
public:
    virtual ~Comando() = default;
    virtual void executa(Fabrica& fabrica, const std::string& argumentos) = 0;
};


#endif //TP_COMANDOS_H
