//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_COMANDOS_H
#define TP_COMANDOS_H
#include <string>

class Contexto;

// Classe base polimorfica de todos os comandos. Cada comando valida os seus
// parametros, executa-se e gera a sua propria ajuda.
class Comando {
public:
    virtual ~Comando() = default;

    // Devolve true se o estado da simulacao foi alterado e o chamador deve
    // redesenhar o ecra. Devolve false em caso de erro/sem alteracoes, ou
    // quando o proprio comando ja apresentou o ecra (ex.: avanca).
    virtual bool executa(Contexto& contexto, const std::string& argumentos) = 0;

    virtual std::string getNome() const = 0;
    virtual std::string ajudaResumida() const = 0;    // uma linha
    virtual std::string ajudaDetalhada() const = 0;   // sintaxe, parametros, efeito, falhas, exemplo

    // Regras de fluxo, verificadas pelo Interpretador antes de executar:
    virtual bool requerFabrica() const { return true; }   // so valido depois da fabrica existir
    virtual bool criaFabrica() const { return false; }    // so valido enquanto a fabrica nao existir

protected:
    // true se nao ha nada (alem de espacos) em argumentos.
    static bool semArgumentos(const std::string& argumentos);
};

#endif //TP_COMANDOS_H
