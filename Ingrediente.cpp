//
// Created by luisf on 2/11/2025.
//

#include "Ingrediente.h"
#include <string>

class Inventario;

Ingrediente::Ingrediente(int nombre, int Cantidad): Nombre(nombre), Cantidad(Cantidad) {}
//void Ingrediente::SubirInventario(Inventario inv) {
//}
int Ingrediente::getNombre() {
    return Nombre;
}
int Ingrediente::getCantidad() {
    return Cantidad;
}
