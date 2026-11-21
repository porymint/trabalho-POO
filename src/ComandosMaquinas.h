//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSMAQUINAS_H
#define TP_COMANDOSMAQUINAS_H

#include "Comandos.h"
#include <string>

class Contexto;

class ComandoCompra : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "compra"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

class ComandoVende : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "vende"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

class ComandoRoda : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "roda"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

#endif //TP_COMANDOSMAQUINAS_H