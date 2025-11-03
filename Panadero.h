//
// Created by luisf on 2/11/2025.
//

#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_PANADERO_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_PANADERO_H
#include "Personal.h"
#include "Receta.h"
#include "Ingrediente.h"


class Panadero: public Personal {
protected:
    const std::string fileName = "Recetas.txt";

public:
    Panadero(std::string& nombre, std::string& apellido);
    void RegistrarReceta(Receta receta);
    void modificarReceta(Receta receta);
    void eliminarReceta(Receta receta);
    void registrarNuevaProduccion(Receta receta);
    std::string consultarStock();

};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_PANADERO_H