/*
===============================================================================
                 IMPLEMENTACIÓN DE LA CLASE Ingrediente
===============================================================================
Rol en el dominio:
- Modelo de insumo: nombre, unidad, cantidad y mínimo (HU04, HU05, HU06)
- Operaciones de consumo/reposición
- Exponer datos para validaciones de disponibilidad/alertas

Se demuestra:
- Encapsulación y uso de getters/setters
- Paso de objetos por referencia
- Validaciones ligadas a: HU04, HU05, HU06
===============================================================================
*/
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
