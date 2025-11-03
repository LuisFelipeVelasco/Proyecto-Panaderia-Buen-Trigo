//
// Created by luisf on 2/11/2025.
//

#include "Panadero.h"
#include <iostream>
#include <fstream>
#include "Ingrediente.h"
#include "Receta.h"
Panadero::Panadero(std::string& nombre, std::string& apellido): Personal(nombre,apellido) {}

void Panadero::RegistrarReceta(Receta receta) {
    std::ofstream file(fileName , std::ios::app);
    if (file.is_open()) {
        file<<"\n";
        file <<receta.getNombre()<<":";
        for (Ingrediente i : receta.getIngredientes()) { // receta es un objeto de tipo receta con un nombre y un
            file << i.getNombre() << "," << i.getCantidad()  << "; ";// pan blanco : azucar , 10 ; mantequilla , 20 ;
        }
        file.close();
        std::cout << "Datos guardados exitosamente.\n";
    } else {
        std::cerr << "Error: No se pudo abrir el archivo de datos.\n";
    }
}