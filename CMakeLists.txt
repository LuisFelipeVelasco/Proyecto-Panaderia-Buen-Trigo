cmake_minimum_required(VERSION 3.0)
project(BuenTrigo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BuenTrigo
        Administrador.cpp
        Administrador.h
        Encargado_Inventario.cpp
        Encargado_Inventario.h
        Ingrediente.cpp
        Ingrediente.h
        main.cpp
        Panadero.cpp
        Panadero.h
        Personal.cpp
        Personal.h
        Receta.cpp
        Receta.h
        Visual.cpp
        Visual.h)
