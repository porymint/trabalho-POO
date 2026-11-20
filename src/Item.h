//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_ITEM_H
#define TP_ITEM_H

#include <string>

// Coisa que circula pela fabrica. Vive sempre dentro de uma maquina.
class Item {
private:
    char simbolo;
    std::string nome;
    int valor;

public:
    Item(char simbolo, const std::string& nome, int valor);

    char getSimbolo() const;
    const std::string& getNome() const;
    int getValor() const;
};

#endif //TP_ITEM_H
