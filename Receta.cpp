//
// Created by luisf on 2/11/2025.
//

#include "Receta.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <Ingrediente.h>
Receta::Receta(std::string& Nombre, std::vector<Ingrediente>& ingredientes): Nombre(Nombre), Ingredientes(ingredientes){}
Receta::~Receta() {}

std::string Receta::getNombre() {
    return Nombre;
}

void Receta::mostrarReceta() {

    std::cout<<"Receta registrada:"<<std::endl<<std::endl;
    std::cout<<"======= "<<Nombre<<" ======"<<std::endl;
     for (Ingrediente i : Ingredientes) {
         std::cout<<"Ingrediente:"<<i.getNombre()<<std::endl;
         std::cout<<"Cantidad:"<<i.getCantidad()<<std::endl;
    }

}
// void Receta::RegistrarReceta() {
//     std::ofstream file(fileName , std::ios::app);
//     if (file.is_open()) {
//         file<<"\n";
//         file <<Nombre<<":";
//         for (Ingrediente i : Ingredientes) {
//             file << i.getNombre() << "," << i.getCantidad()  << "; ";// pan blanco : azucar , 10 ; mantequilla , 20 ;
//         }
//         file.close();
//         std::cout << "Datos guardados exitosamente.\n";
//     } else {
//         std::cerr << "Error: No se pudo abrir el archivo de datos.\n";
//     }
// }

std::vector<Ingrediente> Receta::getIngredientes() {
    return Ingredientes;
}