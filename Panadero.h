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

    // Función auxiliar privada
    std::string obtenerNombreIngrediente(int id);

public:
    Panadero(std::string& nombre, std::string& apellido);
    void RegistrarReceta(Receta receta);
    void modificarReceta(std::string nombreReceta);
    void eliminarReceta(std::string NombreReceta);
    void registrarNuevaProduccion(Receta receta);
    std::string consultarStock();
    std::vector<Receta> GetRecetas();

};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_PANADERO_H