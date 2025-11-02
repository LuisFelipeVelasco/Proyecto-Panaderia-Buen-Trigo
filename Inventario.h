//
// Created by luisf on 2/11/2025.
//

#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_INVENTARIO_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_INVENTARIO_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Ingrediente.h"
class Inventario {

private:
    const std::string fileName = "data.txt";
    std::vector<Ingrediente> ingredientes;

public:
    Inventario();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_INVENTARIO_H