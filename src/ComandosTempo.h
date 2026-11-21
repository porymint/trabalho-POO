//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSTEMPO_H
#define TP_COMANDOSTEMPO_H

#include "Comandos.h"

class ComandoAvanca : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "avanca"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

#endif //TP_COMANDOSTEMPO_H
