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

#include "Encargado_Inventario.h"
#include "Panadero.h"
#include <limits>
#include "Ingrediente.h"
#include "Receta.h"
#include "Administrador.h"

class Visual {

    public:

    Visual();
    void IniciarSesion(Personal usuario);
    void CerrarSesion(Personal usuario);
    void IniciarPrograma(Encargado_Inventario& ControlEncargado);
    int DesplegarInventario();
    int DesplegarMenuDeUsuario();
    int DesplegarMenuDePanadero();
    int DesplegarMenuDeGestorDeInventario();
    int DesplegarMenuDeAdministrador();
    void MostrarReceta(const Receta& receta);
    void RegistrarReceta(Panadero& panadero1 , Receta& receta);

};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_VISUAL_H
