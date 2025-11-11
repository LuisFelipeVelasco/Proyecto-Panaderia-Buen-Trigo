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
#include <iostream>
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

void Panadero::RegistrarReceta(Receta receta) {
    std::ofstream file(fileName , std::ios::app);
    if (file.is_open()) {

        file <<receta.getNombre()<<":";
        for (Ingrediente i : receta.getRecetas()) {
            file << i.getId() << "," << i.getCantidad()  << "; ";
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

// NUEVO: Modificar receta (cambiar cantidad de ingredientes)
void Panadero::modificarReceta(std::string nombreReceta) {
    std::vector<Receta> recetas = GetRecetas();
    std::string objetivo = Receta::trim(nombreReceta);

    bool encontrada = false;
    int indice = -1;

    // Buscar la receta
    for (size_t i = 0; i < recetas.size(); i++) {
        if (Receta::trim(recetas[i].getNombre()) == objetivo) {
            encontrada = true;
            indice = i;
            break;
        }
    }

    if (!encontrada) {
        std::cout << "No se encontró la receta: " << objetivo << "\n";
        return;
    }

    // Mostrar ingredientes de la receta
    std::cout << "\n===== Modificar Receta: " << objetivo << " =====\n";
    std::cout << "Ingredientes actuales:\n";

    auto ingredientes = recetas[indice].getRecetas();
    for (size_t i = 0; i < ingredientes.size(); i++) {
        std::cout << (i+1) << ". " << obtenerNombreIngrediente(ingredientes[i].getId())
                  << " - Cantidad: " << ingredientes[i].getCantidad() << " gramos\n";
    }

    std::cout << "\n¿Desea modificar la cantidad de algún ingrediente? (1=Sí, 0=No): ";
    int opcion;
    std::cin >> opcion;

    if (opcion != 1) {
        std::cout << "Modificación cancelada.\n";
        return;
    }

    std::cout << "Seleccione el número del ingrediente a modificar (1-" << ingredientes.size() << "): ";
    int numIngrediente;
    std::cin >> numIngrediente;

    if (numIngrediente < 1 || numIngrediente > (int)ingredientes.size()) {
        std::cout << "Número de ingrediente inválido.\n";
        return;
    }

    std::cout << "Ingrediente seleccionado: "
              << obtenerNombreIngrediente(ingredientes[numIngrediente-1].getId()) << "\n";
    std::cout << "Cantidad actual: " << ingredientes[numIngrediente-1].getCantidad() << " gramos\n";
    std::cout << "Nueva cantidad (en gramos): ";
    int nuevaCantidad;
    std::cin >> nuevaCantidad;

    // Crear nuevo vector de ingredientes con la modificación
    std::vector<Ingrediente> nuevosIngredientes;
    for (size_t i = 0; i < ingredientes.size(); i++) {
        if ((int)i == numIngrediente - 1) {
            nuevosIngredientes.push_back(Ingrediente(ingredientes[i].getId(), nuevaCantidad));
        } else {
            nuevosIngredientes.push_back(ingredientes[i]);
        }
    }

    // Actualizar la receta en el vector
    std::string nombre = recetas[indice].getNombre();
    recetas[indice] = Receta(nombre, nuevosIngredientes);

    // Escribir todas las recetas de nuevo al archivo
    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Error al crear archivo temporal.\n";
        return;
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
    if (std::rename(tmp.c_str(), fileName.c_str()) != 0) {
        std::cerr << "Error al reemplazar el archivo original.\n";
        return;
    }

    std::cout << "✓ Receta '" << objetivo << "' modificada correctamente.\n";
}

// Función auxiliar para obtener nombre del ingrediente
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

    // Buscar receta
    for(auto &rc : recetas){
        if(rc.getNombre() == nombreReceta){
            r = &rc;
            break;
        }
    }

    if(!r){
        std::cout << "❌ La receta no existe.\n";
        return false;
    }

    // Obtener ingredientes
    auto lista = r->Receta::getIngredientes();
    std::vector<Ingrediente> totalNecesario;

    // Multiplicar ingredientes
    for(const auto &i : lista){
        totalNecesario.emplace_back(i.getId(), i.getCantidad() * cantidad);
    }

    // Descontar ingredientes
    if(!encargado.descontarIngredientes(totalNecesario, cantidad)){
        std::cout << "🚨 No hay suficientes ingredientes.\n";
        return false;
    }


    else {
        std::cout << "✅ Se produjeron " << cantidad
                      << " unidades de " << nombreReceta << "\n";
          return true;
    }

}


void Panadero::registrarNuevaProduccion(const Receta& receta, int cantidad) {
    std::ofstream file(fileProduccion, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir STOCK.txt\n";
        return;
    }

    file << receta.getNombre() << " , " << cantidad << " unidades\n";
    file.close();

    std::cout << "Producción registrada exitosamente ✅\n";
}
std::string Panadero::consultarStock() {
    std::ifstream file(fileProduccion);
    if (!file.is_open()) {
        return "🚨 No se pudo abrir el archivo de stock.";
    }

    std::string linea;
    std::string contenido;

    while (getline(file, linea)) {
        contenido += linea + "\n";
    }

    file.close();

    if (contenido.empty()) {
        return "📦 Stock vacío. Aún no hay producciones registradas.";
    }

    return contenido;
}
