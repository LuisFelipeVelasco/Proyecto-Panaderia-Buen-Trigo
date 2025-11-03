//
// Created by luisf on 2/11/2025.
//

#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H

#include "Personal.h"
#include "Ingrediente.h"
#include "Inventario.h"
#include "iostream"
#include "vector"
class Encargado_Inventario:public Personal {

    protected:

    Inventario inv;
    const std::string fileName = "Ingredientes.txt";

    public:
    Encargado_Inventario(std::string& nombre, std::string& apellidos);
    void RegistarNuevoIngrediente(std::vector<Ingrediente>& ingredientes);
    void EliminarIngrediente(Ingrediente ingrediente);
    void EditarIngrediente(Ingrediente ingrediente);
    std::string ReporteExistencias();
    std::string ReporteInventarioYStock();


};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H