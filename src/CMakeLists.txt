cmake_minimum_required(VERSION 3.27)
project(TP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP
        Fabrica.cpp
        Posicao.cpp
        Comandos.cpp
        Contexto.cpp
        Engenheiro.cpp
        Item.cpp
        Maquina.cpp
        MaquinasDerivadas.cpp
        Simulador.cpp
        ComandosCriacao.cpp
        ComandosEngenheiros.cpp
        ComandosGerais.cpp
        ComandosListagem.cpp
        ComandosMaquinas.cpp
        ComandosTempo.cpp
        Ecra.cpp
        Interpretador.cpp)
