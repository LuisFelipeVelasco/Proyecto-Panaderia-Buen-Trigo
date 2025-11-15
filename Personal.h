/* 
================================================================================
TARJETA CRC
================================================================================
Nombre de la clase: Personal
Responsabilidades:
- Definir datos base del personal (id, nombre, rol)
- Servir como superclase de usuarios del sistema
- Proveer identificación/autenticación básica
Colaboradores:
- Administrador
- Panadero
- Encargado_Inventario
- Visual
================================================================================
*/
#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_PERSONAL_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_PERSONAL_H
#include <string>

class Personal {
    protected:
    std::string Nombre;
    std::string Apellido;
    public:
    Personal(const std::string& nombre,const  std::string& apellido);
    Personal()=default;
    std::string getNombre();
    std::string getApellido();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_PERSONAL_H
