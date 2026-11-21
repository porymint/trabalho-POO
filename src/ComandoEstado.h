//
// Created by Pedro Freitas on 20/11/2026.
//
#ifndef TP_COMANDOSESTADO_H
#define TP_COMANDOSESTADO_H

#include "Comandos.h"
#include <string>

class Contexto;

class ComandoEstado : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "estado"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

#endif //TP_COMANDOSESTADO_H