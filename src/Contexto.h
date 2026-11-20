#ifndef TP_CONTEXTO_H
#define TP_CONTEXTO_H

class Fabrica;
class Ecra;

// Tudo aquilo de que os comandos precisam para atuar: a fabrica, o ecra e o
// estado de controlo do programa (terminar, nivel de aninhamento do "executa").
// Faz tambem a apresentacao do ecra (fabrica + painel de estado).
class Contexto {
private:
    Fabrica& fabrica;
    Ecra& ecra;
    bool terminar;
    int nivelExecuta;

public:
    Contexto(Fabrica& fabrica, Ecra& ecra);
    Contexto(const Contexto&) = delete;
    Contexto& operator=(const Contexto&) = delete;

    Fabrica& getFabrica() const { return fabrica; }
    Ecra& getEcra() const { return ecra; }

    // Desenha a fabrica e o painel no ecra virtual e mostra-o na consola.
    void apresenta();

    void pedeTerminar() { terminar = true; }
    bool terminou() const { return terminar; }

    int getNivelExecuta() const { return nivelExecuta; }
    void entraExecuta() { ++nivelExecuta; }
    void saiExecuta() { --nivelExecuta; }
};

#endif //TP_CONTEXTO_H
