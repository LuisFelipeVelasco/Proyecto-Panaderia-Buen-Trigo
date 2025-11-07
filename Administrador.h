//
// Created by luisf on 2/11/2025.
//

#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H
#include "Personal.h"
#include "vector"
#include <fstream>
#include "Inventario.h"
#include "Ingrediente.h"


class Administrador: public Personal {
protected:
std::string nombre;
std::string apellido;
    Inventario inv;
    const std::string fileName = "Ingredientes.txt";

    // Función auxiliar privada
    std::string obtenerNombreIngrediente(int id);
    std::string obtenerNombreProducto(int id);

public:
    Administrador(std::string& nombre, std::string& apellido);
    std::string resumenInventario();
    std::string stockProductosTerminados();
    void exportarReporte();
    void ConsultarInventario();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H