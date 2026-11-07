//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSLISTAGEM_H
#define TP_COMANDOSLISTAGEM_H


#include "Comandos.h"
#include <string>

class ComandoLPosicao : public Comando {
public:
    void executa(Fabrica& fabrica, const std::string& argumentos) override;
};

#endif //TP_COMANDOSLISTAGEM_H
