#ifndef TP_SETTINGS_H
#define TP_SETTINGS_H

namespace Settings {
    constexpr int MAX_LINHAS = 26;
    constexpr int MAX_COLUNAS = 26;
    constexpr int MIN_MATERIA_DEPOSITO = 40;
    constexpr int MAX_MATERIA_DEPOSITO = 60;

    constexpr int CREDITS_INICIAIS = 1000;

    // Custos de compra das maquinas
    constexpr int CUSTO_PERFURADORA = 100;
    constexpr int CUSTO_TRANSPORTADOR = 5;
    constexpr int CUSTO_REFINARIA = 150;
    constexpr int CUSTO_OFICINA = 200;
    constexpr int CUSTO_SILO = 120;
    constexpr int CUSTO_LANCADOR = 80;

    // Parametros de comportamento
    constexpr int PERFURADORA_CICLO_INSTANTES = 3;
    constexpr int PERFURADORA_PROB_PERDA_INICIAL = 40;
    constexpr int REFINARIA_TEMPO_TRANSFORMACAO = 4;
    constexpr int OFICINA_TEMPO_PRODUCAO = 5;
    constexpr int SILO_PROB_PERDA_INICIAL = 20;
    constexpr int LANCADOR_CICLO_INSTANTES = 4;
    constexpr int LANCADOR_PROB_PERDA_INICIAL = 30;

    // Caracteres dos itens
    constexpr char ITEM_MINERIO_FERRO = 'f';
    constexpr char ITEM_SILICIO_BRUTO = 's';
    constexpr char ITEM_GELO = 'g';
    constexpr char ITEM_PLACA_FERRO = 'p';
    constexpr char ITEM_SILICIO_PURO = 'i';
    constexpr char ITEM_AGUA = 'a';
    constexpr char ITEM_KIT_HABITAT = 'k';

    // Valores de venda (Lançador)
    constexpr int VALOR_MINERIO_FERRO = 2;
    constexpr int VALOR_SILICIO_BRUTO = 3;
    constexpr int VALOR_GELO = 1;
    constexpr int VALOR_PLACA_FERRO = 8;
    constexpr int VALOR_SILICIO_PURO = 10;
    constexpr int VALOR_AGUA = 4;
    constexpr int VALOR_KIT_HABITAT = 120;
}

#endif