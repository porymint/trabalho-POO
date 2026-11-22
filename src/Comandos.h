//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_COMANDOS_H
#define TP_COMANDOS_H
#include <string>

class Contexto;


class Comando {
public:
    virtual ~Comando() = default;

    virtual bool executa(Contexto& contexto, const std::string& argumentos) = 0;

    virtual std::string getNome() const = 0;
    virtual std::string ajudaResumida() const = 0;
    virtual std::string ajudaDetalhada() const = 0;


    virtual bool requerFabrica() const { return true; }
    virtual bool criaFabrica() const { return false; }

    static bool semArgumentos(const std::string& argumentos);
};

#endif //TP_COMANDOS_H
