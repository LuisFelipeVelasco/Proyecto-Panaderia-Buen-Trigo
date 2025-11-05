//
// Created by luisf on 2/11/2025.
//

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
    void IniciarSesion();
    void CerrarSesion();
};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_PERSONAL_H