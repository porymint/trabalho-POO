//
// Created by Pedro Freitas on 20/11/2026.
//
#ifndef TP_COMANDOSENTREGAFINALVALIDACAO_H
#define TP_COMANDOSENTREGAFINALVALIDACAO_H

#include "Comandos.h"
#include <string>

class ComandoMelhora : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
    static std::string ajuda();
};

class ComandoContrata : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
    static std::string ajuda();
};

class ComandoAtribui : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
    static std::string ajuda();
};

class ComandoDespede : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
    static std::string ajuda();
};

class ComandoGrava : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
    static std::string ajuda();
};

class ComandoRecupera : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
    static std::string ajuda();
};

#endif //TP_COMANDOSENTREGAFINALVALIDACAO_H
