
#ifndef TP_MAQUINA_H
#define TP_MAQUINA_H

#include <string>
class Terreno;

class Maquina {
private:
    char tipo;      // 'P', 'T', 'R', 'O', 'S', 'L'
    int linha;
    int coluna;
    char direcao;   // 'c', 'b', 'e', 'd'
    int custo;

public:
    Maquina(char tipo, int linha, int coluna, char direcao, int custo);
    virtual ~Maquina() = default;

    char getTipo() const;
    int getLinha() const;
    int getColuna() const;
    char getDirecao() const;
    int getCusto() const;

    bool setDirecao(char novaDirecao);

    virtual char getSimbolo() const;
    virtual std::string getDescricao() const;
    virtual bool aceitaItem(char item) const;
    virtual bool recebeItem(char item);
    virtual bool temItemParaEntregar() const;
    virtual char verItemParaEntrega() const;
    virtual bool retirarItemParaEntrega(char& itemEntregue);

    virtual void avancarInstante(int instanteAtual, const Terreno& terrenoLocal, int& creditosFabrica);
};

#endif //TP_MAQUINA_H