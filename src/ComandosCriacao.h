//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSCRIACAO_H
#define TP_COMANDOSCRIACAO_H
#include "Comandos.h"

class ComandoFabrica : public Comando {
public:
    void executa(Fabrica& fabricaJogo, const std::string& argumentos) override;
};

#endif //TP_COMANDOSCRIACAO_H
