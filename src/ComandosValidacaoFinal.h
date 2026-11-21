//
// Created by Pedro Freitas on 20/11/2026.
//
#ifndef TP_COMANDOSENTREGAFINALVALIDACAO_H
#define TP_COMANDOSENTREGAFINALVALIDACAO_H

#include "Comandos.h"
#include <string>

class Contexto;

class ComandoMelhora : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "melhora"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

class ComandoContrata : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "contrata"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

class ComandoAtribui : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "atribui"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

class ComandoDespede : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "despede"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

class ComandoGrava : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "grava"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

class ComandoRecupera : public Comando {
public:
    bool executa(Contexto& contexto, const std::string& argumentos) override;
    std::string getNome() const override { return "recupera"; }
    std::string ajudaResumida() const override;
    std::string ajudaDetalhada() const override;
};

#endif //TP_COMANDOSENTREGAFINALVALIDACAO_H