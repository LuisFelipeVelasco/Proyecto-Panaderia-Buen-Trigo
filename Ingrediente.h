//
// Created by luisf on 2/11/2025.
//

#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_INGREDIENTE_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_INGREDIENTE_H

#include <string>
//#include "Inventario.h"

class Ingrediente {

    private:

    int Nombre;
    int Cantidad;
//    Inventario inv;

    public:
    Ingrediente();
    Ingrediente(int nombre, int Cantidad);
  //  void SubirInventario(Inventario inv);
    int getNombre();
    int getCantidad();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_INGREDIENTE_H