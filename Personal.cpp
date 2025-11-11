#include "Personal.h"

#include <iostream>


Personal::Personal(const std::string& nombre, const std::string& apellido): Nombre(nombre), Apellido(apellido) {}

std::string Personal::getNombre() {return Nombre;}
std::string Personal::getApellido() {return Apellido;}
void Personal::IniciarSesion() {std::cout<<"Bienvenido "<<getNombre()<<" "<<getApellido()<<" has iniciado sesion"<<std::endl;}

void Personal::CerrarSesion() {std::cout<<"Adios "<<getNombre()<<" "<<getApellido()<<" has cerrado sesion"<<std::endl;}