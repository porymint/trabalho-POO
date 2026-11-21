#ifndef TP_SETTINGS_H
#define TP_SETTINGS_H

namespace Settings {
    constexpr int MAX_LINHAS = 26;
    constexpr int MAX_COLUNAS = 26;
    constexpr int MIN_MATERIA_DEPOSITO = 40;
    constexpr int MAX_MATERIA_DEPOSITO = 60;
    
    constexpr int CREDITS_INICIAIS = 1000;

    // --- Silo (acrescentado pela Pessoa B) ---
    // Se o Settings oficial dos docentes ja tiver estas constantes (com outros nomes),
    // basta ajustar os nomes usados em MaquinasDerivadas.cpp.
    constexpr int CUSTO_SILO = 120;
    constexpr int PROB_PERDA_SILO = 20;   // percentagem (0..100)
}

#endif
