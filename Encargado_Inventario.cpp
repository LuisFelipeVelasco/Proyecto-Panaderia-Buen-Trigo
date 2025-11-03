//
// Created by luisf on 2/11/2025.
//

#include "Encargado_Inventario.h"
#include "Receta.h"


Encargado_Inventario::Encargado_Inventario(std::string &nombre, std::string &apellidos): Personal(nombre,apellidos) {}
void Encargado_Inventario::RegistarNuevoIngrediente(std::vector<Ingrediente>& ingredientes ) {
    std::ofstream file(fileName , std::ios::app);
    if (file.is_open()) {

        for (auto i:ingredientes ) { // receta es un objeto de tipo receta con un nombre y un
            file << i.getId() << " , " << i.getCantidad()  << " , " << i.getUnidad()<<";"<<"\n";
        }
        file.close();
        std::cout << "Datos guardados exitosamente.\n";
    } else {
        std::cerr << "Error: No se pudo abrir el archivo de datos.\n";
    }
}
