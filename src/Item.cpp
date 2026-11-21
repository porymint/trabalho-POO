//
// Created by Pedro Freitas on 03/11/2026.
//

#include "Item.h"

Item::Item(char simbolo, const std::string& nome, int valor)
    : simbolo(simbolo), nome(nome), valor(valor) {}

char Item::getSimbolo() const { return simbolo; }

const std::string& Item::getNome() const { return nome; }

int Item::getValor() const { return valor; }
