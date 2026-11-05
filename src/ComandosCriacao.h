//
// Created by Pedro Freitas on 04/11/2026.
//

#ifndef TP_COMANDOSCRIACAO_H
#define TP_COMANDOSCRIACAO_H
#include "Comandos.h"

class fabrica : public Comando {
public:
	static Comando* fabrica(int linhas, int colunas);
};

#endif //TP_COMANDOSCRIACAO_H
