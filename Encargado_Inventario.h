#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H

#include "Personal.h"
#include "Ingrediente.h"
#include "iostream"
#include "vector"
#include <fstream>

class Encargado_Inventario:public Personal {

protected:

    const std::string fileName = "Inventario.txt";

    // Función auxiliar privada
    std::string obtenerNombreIngrediente(int id);

public:
    Encargado_Inventario(const std::string& nombre,const std::string& apellido);
    Encargado_Inventario() : Personal("", "") {}

    void RegistarNuevoIngrediente(std::vector<Ingrediente>& ingredientes);

    // Nuevos métodos implementados
    void ConsultarInventario();           // Requerimiento 1
    void VerificarInventarioBajo();       // Requerimiento 2
    void EliminarIngrediente();           // Requerimiento 3
    void EditarIngrediente();             // Requerimiento 4
    bool descontarIngredientes(const std::vector<Ingrediente> &ingredientesNecesarios, int cantidad);

    std::string resumenInventario();
    std::string stockProductosTerminados();
    void ResumenInventarioYStock();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H