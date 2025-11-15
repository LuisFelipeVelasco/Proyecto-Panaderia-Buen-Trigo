/*
Proyecto: Panaderia-Buen-Trigo (Gestión de Inventario, Recetas y Producción)

Enlace Github: https://github.com/LuisFelipeVelasco/Proyecto-Panaderia-Buen-Trigo.git

Curso: Fundamentos de Programación Orientada a Objetos (FPOO)

Autores:
Felipe velasco - 2517245
Jerónimo imbachi - 2517760
Leonardo rosero - 2518313-3743
Alejandro velez - 2521169-3743
Julio Cesar Urbano Noguera - 2517931

Resumen:
Sistema para registrar recetas (HU01), registrar producción con verificación de inventario (HU02),
consultar stock de panes (HU03), administrar y consultar inventario de ingredientes (HU04, HU05),
emitir alertas de reposición (HU06) y generar resúmenes/exports de stock e inventario (HU07, HU08).
*/
#include <iostream>
#include "Encargado_Inventario.h"
#include "Panadero.h"
#include <limits>
#include "Ingrediente.h"
#include "Receta.h"
#include "Administrador.h"
#include "Visual.h"

int main() {

    Visual visual;
    Encargado_Inventario Encargado1("sin asignar", "sin asignar");
    visual.IniciarPrograma(Encargado1);

    return 0;
}