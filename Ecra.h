//
// Created by Pedro Freitas on 03/11/2026.
//

#ifndef TP_ECRA_H
#define TP_ECRA_H
#include <string>
class Ecra{
private:
    //Dimensões ecra
    static const int Max_Linhas = 40;
    static const int Max_Colunas = 80;
    char buffer[Max_Linhas][Max_Colunas];//buffer = array bidimensional

    //Variaveis para verificar o cursor atual
    int cursorLinha;
    int cursorColuna;

public:
     Ecra();
     void limpa();
     void posicionaCursor(int linha, int coluna);
     void escreve(char c);
     void escreve(const std::string& texto);
     void desenhaEcra(int linha, int coluna, int altura, int largura);
     void mostra() const;
 };
#endif //TP_ECRA_H
