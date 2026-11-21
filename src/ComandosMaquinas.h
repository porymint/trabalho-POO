//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSMAQUINAS_H
#define TP_COMANDOSMAQUINAS_H

#include "Comandos.h"
#include <string>

class ComandoCompra : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
};

class ComandoVende : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
};

class ComandoRoda : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
};

#endif //TP_COMANDOSMAQUINAS_H