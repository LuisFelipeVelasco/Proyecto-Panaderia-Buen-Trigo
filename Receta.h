/* 
================================================================================
TARJETA CRC
================================================================================
Nombre de la clase: Receta
Responsabilidades:
- Mantener ingredientes y proporciones por tipo de pan
- Validar disponibilidad de insumos antes de producir
- Calcular consumos para descontar del inventario
Colaboradores:
- Ingrediente
- Panadero
- Administrador
================================================================================
*/
#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_RECETA_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_RECETA_H

#include <string>
#include <vector>

#include "Ingrediente.h"

class Receta {
private:
    std::string Nombre;
    std::vector<Ingrediente> Ingredientes;
public:
    Receta(std::string& Nombre, std::vector<Ingrediente>& ingrediente);
    ~Receta();
    void mostrarReceta();
    std::string getNombre() const;
    std::vector<Ingrediente> getRecetas() const;
    const std::vector<Ingrediente>& getIngredientes() const;


    // helpers sin referencias
    static Receta parseLine(std::string line);
    static std::string trim(std::string s);
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_RECETA_H
