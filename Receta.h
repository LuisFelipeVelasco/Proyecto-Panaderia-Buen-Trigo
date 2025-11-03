//
// Created by luisf on 2/11/2025.
//

#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_RECETA_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_RECETA_H

#include <string>
#include <vector>

#include "Ingrediente.h"

class Receta {
private:
    std::string Nombre;
    std::vector<Ingrediente> Ingredientes;
public:
    Receta(std::string& Nombre, std::vector<Ingrediente>& ingrediente);
    ~Receta();
    void mostrarReceta();
    void RegistrarReceta();
    std::vector<Ingrediente> getIngredientes();
    std::string getNombre();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_RECETA_H