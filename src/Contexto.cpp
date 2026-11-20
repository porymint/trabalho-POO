#include "Contexto.h"
#include "Ecra.h"
#include "Fabrica.h"
#include "Maquina.h"
#include <string>
#include <vector>

Contexto::Contexto(Fabrica& fabrica, Ecra& ecra)
    : fabrica(fabrica), ecra(ecra), terminar(false), nivelExecuta(0) {}

void Contexto::apresenta() {
    const int linhaInicio = 3;
    const int colInicio = 5;
    const int linhasFabrica = fabrica.getLinhas();
    const int colunasFabrica = fabrica.getColunas();

    ecra.limpa();

    if (linhasFabrica > 0 && colunasFabrica > 0) {
        ecra.desenhaEcra(linhaInicio - 2, colInicio - 3, linhasFabrica + 3, colunasFabrica + 5);

        // Reguas
        for (int i = 0; i < colunasFabrica; ++i) {
            ecra.posicionaCursor(linhaInicio - 1, colInicio + i);
            ecra.escreve(static_cast<char>('A' + i));
        }
        for (int i = 0; i < linhasFabrica; ++i) {
            ecra.posicionaCursor(linhaInicio + i, colInicio - 2);
            ecra.escreve(static_cast<char>('A' + i));
        }

        // Terreno e, por cima, as maquinas
        ecra.desenhaFabrica(fabrica, linhaInicio, colInicio);
        for (int i = 0; i < fabrica.getNumMaquinas(); ++i) {
            const Maquina* m = fabrica.getMaquinaPorIndice(i);
            ecra.posicionaCursor(linhaInicio + m->getLinha(), colInicio + m->getColuna());
            ecra.escreve(m->getSimbolo());
        }
    }

    // Painel de estado
    const int altura = 16;
    const int largura = 35;
    const int colPainel = colInicio + (colunasFabrica > 0 ? colunasFabrica : 0) + 5;
    ecra.desenhaEcra(linhaInicio - 2, colPainel, altura, largura);

    ecra.posicionaCursor(linhaInicio, colPainel + 6);
    ecra.escreve("MARTE: ESTADO");
    ecra.posicionaCursor(linhaInicio + 2, colPainel + 2);
    ecra.escreve("Instante: " + std::to_string(fabrica.getInstante()));
    ecra.posicionaCursor(linhaInicio + 3, colPainel + 2);
    ecra.escreve("Creditos: " + std::to_string(fabrica.getCreditos()));
    ecra.posicionaCursor(linhaInicio + 4, colPainel + 2);
    ecra.escreve("Maquinas: " + std::to_string(fabrica.getNumMaquinas()));
    ecra.posicionaCursor(linhaInicio + 5, colPainel + 2);
    ecra.escreve("Engenheiros: 0");

    ecra.posicionaCursor(linhaInicio + 7, colPainel + 2);
    ecra.escreve("No ultimo instante:");

    const std::vector<std::string>& eventos = fabrica.getEventos();
    const int maxEventos = 4;
    const std::string::size_type maxChars = static_cast<std::string::size_type>(largura - 4);
    for (int i = 0; i < maxEventos && i < static_cast<int>(eventos.size()); ++i) {
        ecra.posicionaCursor(linhaInicio + 8 + i, colPainel + 2);
        ecra.escreve(eventos[i].substr(0, maxChars));
    }

    ecra.mostra();
}
