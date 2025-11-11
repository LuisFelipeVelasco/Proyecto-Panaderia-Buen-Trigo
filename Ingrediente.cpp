#include "Ingrediente.h"

class Inventario;

Ingrediente::Ingrediente(int id,  int Cantidad): Id(id), Cantidad(Cantidad) {}
Ingrediente::Ingrediente(int id,  int unidad ,int Cantidad): Id(id), Cantidad(Cantidad), Unidad(unidad)  {}
//void Ingrediente::SubirInventario(Inventario inv) {
//}

int Ingrediente::getId() const {
    return Id;
}
int Ingrediente::getCantidad() const {
    return Cantidad;
}
int Ingrediente::getUnidad() const {
    return Unidad;
}







