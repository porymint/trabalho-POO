//
// Created by Pedro Freitas on 05/11/2026.
//

#ifndef TP_INTERPRETADOR_H
#define TP_INTERPRETADOR_H

#include <string>
#include "Comandos.h"

class Contexto;

class Interpretador {
public:
    // Cria (com new) o comando com este nome; nullptr se nao existir.
    // Quem chama e responsavel pelo delete.
    static Comando* criaComando(const std::string& nome);

    // Acesso a lista de comandos registados (usado pelo comando ajuda).
    // Cada comando devolvido tem de ser libertado por quem chama.
    static int numComandos();
    static Comando* criaComandoPorIndice(int indice);

    // Separa a primeira palavra (comando) do resto (argumentos) e cria o comando.
    static Comando* processaLinha(const std::string& linha, std::string& argumentosRestantes);

    // Ponto unico de execucao de uma linha de comando, venha do teclado ou de
    // um ficheiro: interpreta, aplica as regras de fluxo, executa, redesenha o
    // ecra se for preciso e liberta o comando.
    static void executaLinha(Contexto& contexto, const std::string& linha);
};

#endif //TP_INTERPRETADOR_H
