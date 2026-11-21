//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSCRIACAO_H
#define TP_COMANDOSCRIACAO_H

#include "Comandos.h"
#include <string>

class ComandoFabrica : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "fabrica"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
    bool requerFabrica() const override { return false; }
    bool criaFabrica() const override { return true; }
};

class ComandoCarrega : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "carrega"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
    bool requerFabrica() const override { return false; }
    bool criaFabrica() const override { return true; }
};

#endif //TP_COMANDOSCRIACAO_H