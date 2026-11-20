//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSGERAIS_H
#define TP_COMANDOSGERAIS_H
#include "Comandos.h"

class ComandoFim : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "fim"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
    bool requerFabrica() const override { return false; }
};

class ComandoAjuda : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "ajuda"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
    bool requerFabrica() const override { return false; }
};

class ComandoExecuta : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "executa"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
    bool requerFabrica() const override { return false; }
};

#endif //TP_COMANDOSGERAIS_H
