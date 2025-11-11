#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H
#include "Personal.h"
#include <fstream>


class Administrador: public Personal {
protected:
std::string nombre;
std::string apellido;
    const std::string fileName = "Inventario.txt";

    // Función auxiliar privada
    std::string obtenerNombreIngrediente(int id);

public:
    Administrador(std::string& nombre, std::string& apellido);
    std::string resumenInventario();
    std::string stockProductosTerminados();
    void exportarReporte();
    void ResumenInventarioYStock();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_ADMINISTRADOR_H