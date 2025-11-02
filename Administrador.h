//
// Created by luisf on 2/11/2025.
//

#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H
#include "Personal.h"


class Administrador: public Personal {
protected:

public:
    Administrador(std::string& nombre, std::string& apellido);
    std::string resumenInventario();
    std::string stockProductosTerminados();
    void exportarReporte();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H