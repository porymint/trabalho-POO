cmake_minimum_required(VERSION 3.27)
project(TP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP main.cpp
        Ecra.h
        Fabrica.cpp
        Posicao.cpp
        Comandos.cpp
        ComandosConcretos.cpp
        Engenheiro.cpp
        Item.cpp
        Maquina.cpp
        MaquinasDerivadas.cpp)
