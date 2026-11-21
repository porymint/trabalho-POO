//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSLISTAGEM_H
#define TP_COMANDOSLISTAGEM_H


#include "Comandos.h"
#include <string>

class ComandoLPosicao : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "lposicao"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

#endif //TP_COMANDOSLISTAGEM_H
