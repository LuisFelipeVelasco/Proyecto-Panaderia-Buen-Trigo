/* 
================================================================================
TARJETA CRC
================================================================================
Nombre de la clase: Panadero
Responsabilidades:
- Registrar y modificar recetas con ingredientes y cantidades
- Registrar producciones descontando insumos del inventario
- Consultar el stock de panes para planear producciones
Colaboradores:
- Receta
- Ingrediente
- Visual
================================================================================
*/
#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_PANADERO_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_PANADERO_H
#include "Personal.h"
#include "Receta.h"
#include "Encargado_Inventario.h"

class Panadero: public Personal {
protected:
    const std::string fileName = "Recetas.txt";
    const std::string fileProduccion = "STOCK.txt";

    // Función auxiliar privada
    std::string obtenerNombreIngrediente(int id);

public:
    Panadero(const std::string& nombre,const std::string& apellido);
    bool RegistrarReceta(Receta receta);
    bool modificarReceta(const std::string& nombreOriginal, const Receta& recetaActualizada, std::string& mensaje);
    bool eliminarReceta(std::string NombreReceta, std::string& mensaje);
    void registrarNuevaProduccion(const Receta& receta, int cantidad);
    bool RegistrarProduccion(const std::string& nombreReceta, int cantidad, Encargado_Inventario &encargado);

    std::string consultarStock();
    std::vector<Receta> GetRecetas();

};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_PANADERO_H
