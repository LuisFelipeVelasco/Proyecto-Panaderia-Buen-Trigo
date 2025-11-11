/* 
================================================================================
TARJETA CRC
================================================================================
Nombre de la clase: Visual
Responsabilidades:
- Mostrar menús por rol de usuario y recibir entradas (patrón MVC: vista)
Colaboradores:
- Administrador
- Encargado_Inventario
- Panadero
- Receta
================================================================================
*/
#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_VISUAL_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_VISUAL_H

class Visual {

    public:

    Visual();
    int DesplegarInventario();
    int DesplegarMenuDeUsuario();
    int DesplegarMenuDePanadero();
    int DesplegarMenuDeGestorDeInventario();
    int DesplegarMenuDeAdministrador();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_VISUAL_H
