#include <iostream>
#include <string>
#include "Ecra.h"
#include "Interpretador.h"

using namespace std;

// Mock (simulacro) da Fábrica apenas para o teu código compilar
// enquanto o Membro B não te entrega a classe dele.
class Fabrica {};

void desenhaInterfaceBase(Ecra& ecra) {
    // Dimensões máximas exigidas pelo enunciado para a fábrica
    int linhasFabrica = 26;
    int colunasFabrica = 26;

    // Coordenadas de onde a matriz da fábrica vai começar a ser desenhada no ecrã
    int linhaInicio = 3;
    int colInicio = 5;

    // 1. Moldura principal da Fábrica (envolve a área 26x26 e as réguas)
    ecra.desenhaEcra(linhaInicio - 2, colInicio - 3, linhasFabrica + 3, colunasFabrica + 5);

    // 2. Régua Horizontal (Topo) - Letras de A a Z
    for (int i = 0; i < colunasFabrica; ++i) {
        ecra.posicionaCursor(linhaInicio - 1, colInicio + i);
        // A magia do ASCII: 'A' + 0 = 'A', 'A' + 1 = 'B', etc.
        ecra.escreve(static_cast<char>('A' + i));
    }

    // 3. Régua Vertical (Esquerda) - Letras de A a Z
    for (int i = 0; i < linhasFabrica; ++i) {
        ecra.posicionaCursor(linhaInicio + i, colInicio - 2);
        ecra.escreve(static_cast<char>('A' + i));
    }

    // 4. Painel de Estado (posicionado à direita da fábrica)
    int colPainel = colInicio + colunasFabrica + 5;
    ecra.desenhaEcra(linhaInicio - 2, colPainel, 12, 35); // Moldura do painel

    // Textos informativos do Checkpoint 1
    ecra.posicionaCursor(linhaInicio, colPainel + 6);
    ecra.escreve("=== MARTE: ESTADO ===");

    ecra.posicionaCursor(linhaInicio + 2, colPainel + 2);
    ecra.escreve("Instante: 0"); // Fixo por agora

    ecra.posicionaCursor(linhaInicio + 3, colPainel + 2);
    ecra.escreve("Creditos: 0"); // Fixo por agora

    // Uma pequena ajuda visual para os comandos
    ecra.posicionaCursor(linhaInicio + 8, colPainel + 2);
    ecra.escreve("Comandos: fabrica, carrega,");
    ecra.posicionaCursor(linhaInicio + 9, colPainel + 2);
    ecra.escreve("          lposicao, fim");
}
int main() {
    Ecra ecra;
    Fabrica fabrica; // O simulacro que criámos há pouco
    string linha;

    // --- PREPARAÇÃO DO ECRÃ INICIAL ---
    ecra.limpa();
    desenhaInterfaceBase(ecra);

    // --- CICLO DO INTERPRETADOR ---
    while (true) {
        ecra.posicionaCursor(38, 0); // Puxa o cursor cá para baixo (linha 38)
        ecra.escreve("                                        "); // Limpa mensagens de erro antigas

        ecra.mostra(); // Despeja o buffer

        cout << "\nComando> ";

        if (!getline(cin, linha)) break;
        if (linha.empty()) continue;

        string argumentos;
        // O interpretador trata de ler a string e criar o objeto
        Comando* cmd = Interpretador::processaLinha(linha, argumentos);

        if (cmd != nullptr) {
            // POLIMORFISMO: Executa a ação do comando instanciado
            cmd->executa(fabrica, argumentos);

            // Regra de ouro da memória dinâmica: limpar o que o 'new' criou
            delete cmd;

            // Se o comando foi o fim, paramos o ciclo
            if (linha == "fim") break;
        } else {
            cout << "Erro: Comando nao reconhecido." << endl;
        }
    }

    return 0;
}