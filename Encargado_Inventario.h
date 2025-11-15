/* 
================================================================================
TARJETA CRC
================================================================================
Nombre de la clase: Encargado_Inventario
Responsabilidades:
- Registrar/actualizar/eliminar ingredientes del sistema
- Consultar existencias y niveles mínimos; emitir alertas de reposición
- Generar y visualizar resúmenes de inventario y stock
Colaboradores:
- Ingrediente
- Receta
- Visual
- Administrador
================================================================================
*/
#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H

#include "Personal.h"
#include "Ingrediente.h"
#include "vector"
#include <fstream>

class Encargado_Inventario:public Personal {

protected:

    const std::string fileName = "Inventario.txt";

    // Función auxiliar privada
    std::string obtenerNombreIngrediente(int id);

public:
    Encargado_Inventario(const std::string& nombre,const std::string& apellido);
    Encargado_Inventario() : Personal("", "") {}

    bool RegistarNuevoIngrediente(std::vector<Ingrediente>& ingredientes);

    // Métodos refactorizados - retornan datos en lugar de imprimir
    std::string ConsultarInventario();
    std::string VerificarInventarioBajo();
    bool EliminarIngrediente(int idEliminar, std::string& mensaje);
    bool EditarIngrediente(int idEditar, int nuevaCantidad, int nuevaUnidad, std::string& mensaje);
    bool descontarIngredientes(const std::vector<Ingrediente> &ingredientesNecesarios, int cantidad);

    std::string resumenInventario();
    std::string stockProductosTerminados();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_ENCARGADO_INVENTARIO_H
