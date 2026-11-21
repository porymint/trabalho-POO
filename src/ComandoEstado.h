//
// Created by Pedro Freitas on 20/11/2026.
//
#ifndef TP_COMANDOSESTADO_H
#define TP_COMANDOSESTADO_H

#include "Comandos.h"
#include <string>

class ComandoEstado : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
    static std::string ajuda();
};

#endif //TP_COMANDOSESTADO_H