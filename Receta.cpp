//
// Created by luisf on 2/11/2025.
//

#include "Receta.h"

#include <iostream>
#include <ostream>
#include <Ingrediente.h>
Receta::Receta(std::string& Nombre, std::vector<Ingrediente>& ingredientes): Nombre(Nombre), Ingredientes(ingredientes){}
Receta::~Receta() {}

void Receta::mostrarReceta() {

    std::cout<<"Receta registrada:"<<std::endl<<std::endl;
    std::cout<<"======= "<<Nombre<<" ======"<<std::endl;
     for (Ingrediente i : Ingredientes) {
         std::cout<<"Ingrediente:"<<i.getNombre()<<std::endl;
         std::cout<<"Cantidad:"<<i.getCantidad()<<std::endl;
    }

}
