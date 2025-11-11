#include <fstream>
#include <iostream>
#include <ostream>
#include "Receta.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
Receta::Receta(std::string& Nombre, std::vector<Ingrediente>& ingredientes): Nombre(Nombre), Ingredientes(ingredientes){}
Receta::~Receta() {}

std::string Receta::getNombre () const{
    return Nombre;
}

void Receta::mostrarReceta() {

    std::cout<<"Receta registrada:"<<std::endl<<std::endl;
    std::cout<<"======= "<<Nombre<<" ======"<<std::endl;
     for (Ingrediente i : Ingredientes) {
         std::cout<<"Ingrediente:"<<i.getId()<<std::endl;
         std::cout<<"Cantidad:"<<i.getCantidad()<<std::endl;
    }

}

std::vector<Ingrediente> Receta::getRecetas() const{
    return Ingredientes;
}

std::string Receta::trim(std::string s) {
    size_t i = 0, j = s.size();
    while (i < j && std::isspace((unsigned char)s[i])) ++i;
    while (j > i && std::isspace((unsigned char)s[j-1])) --j;
    return s.substr(i, j - i);
}

Receta Receta::parseLine(std::string line) {
    size_t pos = line.find(':');
    if (pos == std::string::npos) throw std::runtime_error("linea invalida");

    std::string nombre = trim(line.substr(0, pos));
    std::string resto  = line.substr(pos + 1);

    std::stringstream ss(resto);
    std::string item;
    std::vector<Ingrediente> ings;

    while (std::getline(ss, item, ';')) {
        item = trim(item);
        if (item.empty()) continue;
        size_t coma = item.find(',');
        if (coma == std::string::npos) continue;
        int id = std::stoi(trim(item.substr(0, coma)));
        int cant = std::stoi(trim(item.substr(coma + 1)));
        ings.push_back(Ingrediente(id, cant));
    }
    return Receta(nombre, ings);
}
const std::vector<Ingrediente>& Receta::getIngredientes() const {
    return Ingredientes;
}
