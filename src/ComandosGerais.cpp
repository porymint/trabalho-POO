//
// Created by Pedro Freitas on 04/11/2026.
//

#include "ComandosGerais.h"
#include "Contexto.h"
#include "Interpretador.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace {
    const int MAX_NIVEL_EXECUTA = 4;
}

// ------------------------------------------------------------------ fim

bool ComandoFim::executa(Contexto& contexto, const string& argumentos) {
    if (!semArgumentos(argumentos)) {
        cout << "Erro: Sintaxe incorreta. Uso: fim" << endl;
        return false;
    }
    cout << "A encerrar o simulador de Marte..." << endl;
    contexto.pedeTerminar();
    return false;
}

string ComandoFim::ajudaResumida() const {
    return "fim                    encerra o programa";
}

string ComandoFim::ajudaDetalhada() const {
    return "fim\n"
           "  Sem parametros.\n"
           "  Encerra o programa, libertando todos os recursos alocados.\n"
           "  Pode ser usado antes de a fabrica ser criada.\n"
           "  Exemplo: fim\n";
}

// ---------------------------------------------------------------- ajuda

bool ComandoAjuda::executa(Contexto&, const string& argumentos) {
    istringstream iss(argumentos);
    string nome, extra;

    if (!(iss >> nome)) {
        cout << "\nComandos disponiveis:" << endl;
        for (int i = 0; i < Interpretador::numComandos(); ++i) {
            Comando* cmd = Interpretador::criaComandoPorIndice(i);
            cout << "  " << cmd->ajudaResumida() << endl;
            delete cmd;
        }
        cout << "\nUse 'ajuda <comando>' para a ajuda detalhada." << endl;
        return false;
    }

    if (iss >> extra) {
        cout << "Erro: Sintaxe incorreta. Uso: ajuda [comando]" << endl;
        return false;
    }

    Comando* cmd = Interpretador::criaComando(nome);
    if (cmd == nullptr) {
        cout << "Erro: Nao existe o comando '" << nome << "'. Use 'ajuda' para ver a lista." << endl;
        return false;
    }

    cout << "\n" << cmd->ajudaDetalhada();
    delete cmd;
    return false;
}

string ComandoAjuda::ajudaResumida() const {
    return "ajuda [comando]        lista os comandos ou explica um em detalhe";
}

string ComandoAjuda::ajudaDetalhada() const {
    return "ajuda [comando]\n"
           "  comando : (opcional) nome do comando sobre o qual se quer ajuda.\n"
           "  Sem parametro, lista todos os comandos com a sintaxe resumida.\n"
           "  Com o nome de um comando, mostra sintaxe, parametros, efeito,\n"
           "  condicoes de falha e um exemplo.\n"
           "  Falha se o comando indicado nao existir.\n"
           "  Exemplo: ajuda avanca\n";
}

// -------------------------------------------------------------- executa

bool ComandoExecuta::executa(Contexto& contexto, const string& argumentos) {
    istringstream iss(argumentos);
    string nomeFicheiro, extra;

    if (!(iss >> nomeFicheiro) || (iss >> extra)) {
        cout << "Erro: Sintaxe incorreta. Uso: executa <nome-do-ficheiro>" << endl;
        return false;
    }

    if (contexto.getNivelExecuta() >= MAX_NIVEL_EXECUTA) {
        cout << "Erro: Demasiados niveis de 'executa' encadeados." << endl;
        return false;
    }

    ifstream ficheiro(nomeFicheiro.c_str());
    if (!ficheiro) {
        cout << "Erro: Nao foi possivel abrir o ficheiro '" << nomeFicheiro << "'." << endl;
        return false;
    }

    contexto.entraExecuta();

    string linha;
    while (!contexto.terminou() && getline(ficheiro, linha)) {
        if (!linha.empty() && linha[linha.size() - 1] == '\r') {
            linha.erase(linha.size() - 1);   // ficheiros com fim de linha Windows
        }
        if (linha.find_first_not_of(" \t") == string::npos) continue;

        cout << "executa> " << linha << endl;
        // Mesmo caminho que o teclado: so muda a origem do texto.
        Interpretador::executaLinha(contexto, linha);
    }

    contexto.saiExecuta();
    return false;   // cada comando lido ja tratou de redesenhar o ecra
}

string ComandoExecuta::ajudaResumida() const {
    return "executa <ficheiro>     le e executa comandos de um ficheiro de texto";
}

string ComandoExecuta::ajudaDetalhada() const {
    return "executa <nome-do-ficheiro>\n"
           "  nome-do-ficheiro : ficheiro de texto com um comando por linha, no mesmo\n"
           "                     formato dos comandos escritos no teclado.\n"
           "  Executa os comandos pela ordem do ficheiro, como se fossem escritos.\n"
           "  Linhas em branco sao ignoradas. Um 'fim' no ficheiro termina o programa.\n"
           "  Falha se faltar o nome, se o ficheiro nao puder ser aberto ou se houver\n"
           "  demasiados 'executa' encadeados.\n"
           "  Exemplo: executa teste1.txt\n";
}
