/*
===============================================================================
                 IMPLEMENTACIÓN DE LA CLASE Panadero
===============================================================================
Rol en el dominio:
- Administrar recetas (HU01); registrar producción con verificación de inventario (HU02)
- Consultar stock (HU03)
- Orquestar flujos de producción y registro

Se demuestra:
- Encapsulación y uso de getters/setters
- Paso de objetos por referencia
- Integración con Visual para interacción/alertas/reportes
- Validaciones ligadas a: HU01, HU02, HU03
===============================================================================
*/
#include "Panadero.h"

#include <algorithm>
#include <fstream>
#include "Ingrediente.h"
#include "Receta.h"
#include <cstdio>
#include <sstream>

Panadero::Panadero(const std::string& nombre, const std::string& apellido)
: Personal(nombre, apellido) {
    std::ofstream f(fileProduccion, std::ios::app);
    f.close();
}

bool Panadero::RegistrarReceta(Receta receta) {
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        return false;
    }

    file << receta.getNombre() << ":";
    for (Ingrediente i : receta.getRecetas()) {
        file << i.getId() << "," << i.getCantidad() << "; ";
    }
    file << "\n";
    file.close();
    return true;
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
        } catch (const std::exception&) {
        }
    }
    return recetas;
}


bool Panadero::eliminarReceta(std::string NombreReceta, std::string& mensaje) {
    std::vector<Receta> recetas = GetRecetas();
    std::string objetivo = Receta::trim(NombreReceta);

    size_t antes = recetas.size();
    recetas.erase(
        std::remove_if(recetas.begin(), recetas.end(),
            [objetivo](Receta r) { return Receta::trim(r.getNombre()) == objetivo; }),
        recetas.end()
    );

    if (recetas.size() == antes) {
        mensaje = "Receta no encontrada: " + NombreReceta;
        return false;
    }

    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) {
        mensaje = "Error al abrir archivo temporal";
        return false;
    }

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
    std::rename(tmp.c_str(), fileName.c_str());
    
    mensaje = "✓ Receta eliminada: " + NombreReceta;
    return true;
}

bool Panadero::modificarReceta(const std::string& nombreOriginal, const Receta& recetaActualizada, std::string& mensaje) {
    std::vector<Receta> recetas = GetRecetas();
    std::string objetivo = Receta::trim(nombreOriginal);
    
    bool encontrada = false;
    for (auto& r : recetas) {
        if (Receta::trim(r.getNombre()) == objetivo) {
            encontrada = true;
            break;
        }
    }
    
    if (!encontrada) {
        mensaje = "Receta no encontrada: " + nombreOriginal;
        return false;
    }
    
    // Check for duplicate name (if renaming)
    std::string nuevoNombre = Receta::trim(recetaActualizada.getNombre());
    if (nuevoNombre != objetivo) {
        for (const auto& r : recetas) {
            std::string existente = Receta::trim(r.getNombre());
            if (existente == nuevoNombre) {
                mensaje = "Ya existe una receta con el nombre: " + nuevoNombre;
                return false;
            }
        }
    }
    
    // Replace the recipe
    for (auto& r : recetas) {
        if (Receta::trim(r.getNombre()) == objetivo) {
            r = recetaActualizada;
            break;
        }
    }
    
    // Write updated list to file
    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) {
        mensaje = "Error al abrir archivo temporal";
        return false;
    }
    
    for (const auto& r : recetas) {
        out << r.getNombre() << ": ";
        auto vec = r.getRecetas();
        for (const auto& ing : vec) {
            out << ing.getId() << "," << ing.getCantidad() << "; ";
        }
        out << "\n";
    }
    out.close();
    
    std::remove(fileName.c_str());
    std::rename(tmp.c_str(), fileName.c_str());
    
    mensaje = "✓ Receta modificada: " + nombreOriginal + " → " + recetaActualizada.getNombre();
    return true;
}

std::string Panadero::obtenerNombreIngrediente(int id) {
    switch(id) {
        case 1: return "Harina";
        case 2: return "Azucar";
        case 3: return "Sal";
        case 4: return "Levadura";
        case 5: return "Huevos";
        case 6: return "Canela";
        case 7: return "Queso";
        case 8: return "Mantequilla";
        default: return "Desconocido";
    }
}

bool Panadero::RegistrarProduccion(const std::string& nombreReceta, int cantidad, Encargado_Inventario &encargado){

    auto recetas = GetRecetas();
    Receta* r = nullptr;

    for(auto &rc : recetas){
        if(rc.getNombre() == nombreReceta){
            r = &rc;
            break;
        }
    }

    if(!r){
        return false;
    }

    auto lista = r->Receta::getIngredientes();
    std::vector<Ingrediente> totalNecesario;

    for(const auto &i : lista){
        totalNecesario.emplace_back(i.getId(), i.getCantidad() * cantidad);
    }

    if(!encargado.descontarIngredientes(totalNecesario, cantidad)){
        return false;
    }

    return true;
}


void Panadero::registrarNuevaProduccion(const Receta& receta, int cantidad) {
    std::ofstream file(fileProduccion, std::ios::app);

    if (!file.is_open()) {
        return;
    }

    file << receta.getNombre() << " , " << cantidad << " unidades\n";
    file.close();
}

std::string Panadero::consultarStock() {
    std::ifstream file(fileProduccion);
    if (!file.is_open()) {
        return "No se pudo abrir el archivo de stock.";
    }

    std::string linea;
    std::string contenido;

    while (getline(file, linea)) {
        contenido += linea + "\n";
    }

    file.close();

    if (contenido.empty()) {
        return "Stock vacío. Aún no hay producciones registradas.";
    }

    return contenido;
}
