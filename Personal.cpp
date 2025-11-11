/*
===============================================================================
                 IMPLEMENTACIÓN DE LA CLASE Personal
===============================================================================
Rol en el dominio:
- Base para usuarios del sistema
- Provee datos comunes (nombre, apellido) y mensajes de sesión
- Superclase de Panadero, Encargado_Inventario y Administrador

Se demuestra:
- Encapsulación y uso de getters/setters
- Clase base para jerarquía de herencia
- Validaciones ligadas a: HU01, HU02, HU03, HU04, HU05, HU06, HU07, HU08
===============================================================================
*/
#include "Personal.h"

#include <iostream>


Personal::Personal(const std::string& nombre, const std::string& apellido): Nombre(nombre), Apellido(apellido) {}

std::string Personal::getNombre() {return Nombre;}
std::string Personal::getApellido() {return Apellido;}
void Personal::IniciarSesion() {std::cout<<"Bienvenido "<<getNombre()<<" "<<getApellido()<<" has iniciado sesion"<<std::endl;}

void Personal::CerrarSesion() {std::cout<<"Adios "<<getNombre()<<" "<<getApellido()<<" has cerrado sesion"<<std::endl;}
