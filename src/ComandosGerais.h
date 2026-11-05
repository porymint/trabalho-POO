//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSGERAIS_H
#define TP_COMANDOSGERAIS_H
#include "Comandos.h"
#include <iostream>

class ComandoFim : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override {
        std::cout << "A encerrar o simulador de Marte..." << std::endl;
    }
};

class ComandoFabrica : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override {
        std::cout << "Comando fabrica invocado com os dados: " << argumentos << std::endl;
    }
};

#endif //TP_COMANDOSGERAIS_H
