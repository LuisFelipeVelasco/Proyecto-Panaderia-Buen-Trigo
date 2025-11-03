//
// Created by luisf on 2/11/2025.
//

#include "Panadero.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include "Ingrediente.h"
#include "Receta.h"
#include <cstdio>

Panadero::Panadero(std::string& nombre, std::string& apellido): Personal(nombre,apellido) {}

void Panadero::RegistrarReceta(Receta receta) {
    std::ofstream file(fileName , std::ios::app);
    if (file.is_open()) {

        file <<receta.getNombre()<<":";
        for (Ingrediente i : receta.getRecetas()) { // receta es un objeto de tipo receta con un nombre y un
            file << i.getId() << "," << i.getCantidad()  << "; ";// pan blanco : azucar , 10 ; mantequilla , 20 ;
        }
        file<<"\n";
        file.close();
        std::cout << "Datos guardados exitosamente.\n";
    } else {
        std::cerr << "Error: No se pudo abrir el archivo de datos.\n";
    }
}


std::vector<Receta> Panadero::GetRecetas() {
    std::vector<Receta> recetas;
    std::ifstream in(fileName);
    if (!in.is_open()) return recetas;

    std::string line;
    while (std::getline(in, line)) {
        auto limpia = Receta::trim(line);
        if (limpia.empty()) continue;
        try {
            recetas.emplace_back(Receta::parseLine(limpia));
        } catch (const std::exception& e) {
            std::cerr << "Error al parsear linea: " << limpia
                      << " (" << e.what() << ")\n";
        }
    }
    return recetas;
}


void Panadero::eliminarReceta(std::string NombreReceta) {
    std::vector<Receta> recetas = GetRecetas();
    std::string objetivo = Receta::trim(NombreReceta);

    // borrar del vector (sin referencias en lambda)
    size_t antes = recetas.size();
    recetas.erase(
        std::remove_if(recetas.begin(), recetas.end(),
            [objetivo](Receta r) { return Receta::trim(r.getNombre()) == objetivo; }),
        recetas.end()
    );

    if (recetas.size() == antes) {
        std::cout << "No se encontró la receta: " << objetivo << "\n";
        return;
    }

    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) { std::cerr << "Error al crear archivo temporal.\n"; return; }

    // Escribir todo otra vez (copias, sin refs)
    for (auto r : recetas) {
        out << r.getNombre() << ": ";
        auto vec = r.getRecetas();
        for (auto ing : vec) {
            out << ing.getId() << "," << ing.getCantidad() << "; ";
        }
        out << "\n";
    }
    out.close();

    std::remove(fileName.c_str());
    if (std::rename(tmp.c_str(), fileName.c_str()) != 0) {
        std::cerr << "Error al reemplazar el archivo original.\n";
        return;
    }
    std::cout << "Receta '" << objetivo << "' eliminada correctamente.\n";
}


