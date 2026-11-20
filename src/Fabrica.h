//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_FABRICA_H
#define TP_FABRICA_H

#include <string>
#include <vector>

class Maquina;

class Terreno {
private:
    char tipo = ' ';
    int quantidade = 0;

public:
    char getTipo() const { return tipo; }
    int getQuantidade() const { return quantidade; }

    void setTipo(char t) { tipo = t; }
    void setQuantidade(int q) { quantidade = q; }
};

class Fabrica {
private:
    int linhas;
    int colunas;


    Terreno* grelha;

    int instante;
    int creditos;
    std::vector<Maquina*> maquinas;        // a Fabrica e dona das maquinas
    std::vector<std::string> eventos;      // resumo do ultimo instante

    void alocaMemoria(int nl, int nc);
    void libertaMemoria();

public:
    Fabrica(int nl = 0, int nc = 0);
    ~Fabrica();

    Fabrica(const Fabrica& outra) = delete;
    Fabrica& operator=(const Fabrica& outra) = delete;

    bool carregarDeFicheiro(const std::string& nomeFicheiro);
    bool criarAleatoria(int nl, int nc);

    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }

    const Terreno* getTerreno(int l, int c) const;
    bool posicaoValida(int l, int c) const;

    // --- Tempo e creditos ---
    int getInstante() const { return instante; }
    int getCreditos() const { return creditos; }
    void avancaInstante();

    // --- Maquinas ---
    int getNumMaquinas() const { return static_cast<int>(maquinas.size()); }
    Maquina* getMaquinaPorIndice(int i) const;
    Maquina* getMaquina(int l, int c) const;
    // Fica com a posse da maquina se devolver true. Falha (e o chamador mantem a
    // posse) se a posicao for invalida, for uma cratera ou ja estiver ocupada.
    bool adicionaMaquina(Maquina* m);

    // --- Resumo do ultimo instante (painel de estado) ---
    void registaEvento(const std::string& texto);
    const std::vector<std::string>& getEventos() const { return eventos; }
};

#endif //TP_FABRICA_H