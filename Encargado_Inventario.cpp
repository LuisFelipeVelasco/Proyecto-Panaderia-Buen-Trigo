/*
===============================================================================
                 IMPLEMENTACIÓN DE LA CLASE Encargado_Inventario
===============================================================================
Rol en el dominio:
- Gestionar ingredientes; ver alertas de reposición; resúmenes (HU04-HU07)
- Registrar/actualizar/eliminar ingredientes del inventario
- Consultar existencias y emitir alertas de bajo stock

Se demuestra:
- Encapsulación y uso de getters/setters
- Paso de objetos por referencia
- Validaciones ligadas a: HU04, HU05, HU06, HU07
===============================================================================
*/
#include "Encargado_Inventario.h"
#include "Receta.h"
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <iomanip>

Encargado_Inventario::Encargado_Inventario(const std::string &nombre, const std::string &apellido)
    : Personal(nombre, apellido) {}



bool Encargado_Inventario::RegistarNuevoIngrediente(std::vector<Ingrediente>& ingredientes) {
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        return false;
    }
    
    for (auto i : ingredientes) {
        file << i.getId() << " , " << i.getCantidad() << " , " << i.getUnidad() << ";" << "\n";
    }
    file.close();
    return true;
}

std::string Encargado_Inventario::ConsultarInventario() {
    std::ostringstream out;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return "Error: No se pudo abrir el archivo de ingredientes.";
    }

    out << "\n===== INVENTARIO DE INGREDIENTES =====\n";
    out << "1. Harina\n2. Azucar\n3. Sal\n4. Levadura\n";
    out << "5. Huevos\n6. Canela\n7. Queso\n8. Mantequilla\n\n";

    out << "Ingredientes disponibles:\n";
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line.find(',') == std::string::npos) continue;
        
        std::stringstream ss(line);
        int id, cantidad, unidad;
        char delim;
        ss >> id >> delim >> cantidad >> delim >> unidad;

        std::string nombre = obtenerNombreIngrediente(id);
        std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";
        out << "  - " << nombre << ": " << cantidad << " " << unidadStr << "\n";
    }
    file.close();
    return out.str();
}

std::string Encargado_Inventario::VerificarInventarioBajo() {
    std::ostringstream out;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return "Error: No se pudo abrir el archivo de ingredientes.";
    }

    const int TOPE_MINIMO = 50;
    out << "\n===== INGREDIENTES POR DEBAJO DEL TOPE =====\n";
    out << "Tope mínimo establecido: " << TOPE_MINIMO << " unidades\n\n";

    std::string line;
    bool hayBajos = false;

    while (std::getline(file, line)) {
        if (line.empty() || line.find(',') == std::string::npos) continue;

        std::stringstream ss(line);
        int id, cantidad, unidad;
        char delim;
        ss >> id >> delim >> cantidad >> delim >> unidad;

        if (cantidad < TOPE_MINIMO) {
            std::string nombre = obtenerNombreIngrediente(id);
            std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";
            out << "⚠️  " << nombre << ": " << cantidad << " " << unidadStr
                      << " (Faltan " << (TOPE_MINIMO - cantidad) << " para el tope)\n";
            hayBajos = true;
        }
    }

    file.close();

    if (!hayBajos) {
        out << "✓ Todos los ingredientes están por encima del tope mínimo.\n";
    } else {
        out << "\n⚠️  Se recomienda reabastecer estos ingredientes.\n";
    }
    
    return out.str();
}

bool Encargado_Inventario::EliminarIngrediente(int idEliminar, std::string& mensaje) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        mensaje = "Error: No se pudo abrir el archivo de ingredientes.";
        return false;
    }

    std::vector<std::string> lineas;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty() && line.find(',') != std::string::npos) {
            lineas.push_back(line);
        }
    }
    file.close();

    if (lineas.empty()) {
        mensaje = "No hay ingredientes para eliminar.";
        return false;
    }

    size_t tamañoAntes = lineas.size();
    lineas.erase(
        std::remove_if(lineas.begin(), lineas.end(),
            [idEliminar](const std::string& l) {
                std::stringstream ss(l);
                int id;
                char delim;
                ss >> id;
                return id == idEliminar;
            }),
        lineas.end()
    );

    if (lineas.size() == tamañoAntes) {
        mensaje = "No se encontró el ingrediente con ID " + std::to_string(idEliminar);
        return false;
    }

    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) {
        mensaje = "Error al crear archivo temporal.";
        return false;
    }

    for (const auto& l : lineas) {
        out << l << "\n";
    }
    out.close();

    std::remove(fileName.c_str());
    if (std::rename(tmp.c_str(), fileName.c_str()) != 0) {
        mensaje = "Error al reemplazar el archivo.";
        return false;
    }

    mensaje = "✓ Ingrediente eliminado correctamente.";
    return true;
}

bool Encargado_Inventario::EditarIngrediente(int idEditar, int nuevaCantidad, int nuevaUnidad, std::string& mensaje) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        mensaje = "Error: No se pudo abrir el archivo de ingredientes.";
        return false;
    }

    std::vector<std::string> lineas;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty() && line.find(',') != std::string::npos) {
            lineas.push_back(line);
        }
    }
    file.close();

    if (lineas.empty()) {
        mensaje = "No hay ingredientes para editar.";
        return false;
    }

    bool encontrado = false;
    for (auto& l : lineas) {
        std::stringstream ss(l);
        int id, cantidad, unidad;
        char delim;
        ss >> id >> delim >> cantidad >> delim >> unidad;

        if (id == idEditar) {
            encontrado = true;
            std::stringstream nueva;
            nueva << id << " , " << nuevaCantidad << " , " << nuevaUnidad << ";";
            l = nueva.str();
            break;
        }
    }

    if (!encontrado) {
        mensaje = "No se encontró el ingrediente con ID " + std::to_string(idEditar);
        return false;
    }

    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) {
        mensaje = "Error al crear archivo temporal.";
        return false;
    }

    for (const auto& l : lineas) {
        out << l << "\n";
    }
    out.close();

    std::remove(fileName.c_str());
    if (std::rename(tmp.c_str(), fileName.c_str()) != 0) {
        mensaje = "Error al reemplazar el archivo.";
        return false;
    }

    mensaje = "✓ Ingrediente actualizado correctamente.";
    return true;
}

std::string Encargado_Inventario::obtenerNombreIngrediente(int id) {
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

bool Encargado_Inventario::descontarIngredientes(
        const std::vector<Ingrediente> &ingredientesNecesarios,
        int cantidadProduccion)
{
    std::ifstream in(fileName);
    if (!in.is_open()) {
        return false;
    }

    std::vector<std::string> lineas;
    std::string line;
    while (std::getline(in, line))
        if (!line.empty())
            lineas.push_back(line);
    in.close();

    std::vector<Ingrediente> inventario;
    for (auto &l : lineas) {
        std::stringstream ss(l);
        int id, cant, uni;
        char d;
        ss >> id >> d >> cant >> d >> uni;
        inventario.emplace_back(id, uni, cant);
    }

    for (auto &ingReceta : ingredientesNecesarios) {
        int totalNecesario = ingReceta.getCantidad() * cantidadProduccion;
        bool encontrado = false;

        for (auto &ingInv : inventario) {
            if (ingInv.getId() == ingReceta.getId()) {
                encontrado = true;
                if (ingInv.getCantidad() < totalNecesario) {
                    return false;
                }
                break;
            }
        }
        if (!encontrado) return false;
    }

    for (auto &ingReceta : ingredientesNecesarios) {
        int totalNecesario = ingReceta.getCantidad() * cantidadProduccion;
        for (auto &ingInv : inventario) {
            if (ingInv.getId() == ingReceta.getId()) {
                ingInv.setCantidad(ingInv.getCantidad() - totalNecesario);
                break;
            }
        }
    }

    std::ofstream out(fileName, std::ios::trunc);
    for (auto &i : inventario) {
        out << i.getId() << " , "
            << i.getCantidad() << " , "
            << i.getUnidad()
            << ";\n";
    }
    out.close();

    return true;
}

std::string Encargado_Inventario::resumenInventario() {
    std::ostringstream out;
    std::ifstream fileIng(fileName);
    if (!fileIng.is_open()) {
        return "⚠ No se pudo abrir " + fileName;
    }

    out << "=== INVENTARIO DE INGREDIENTES ===\n";
    std::string line;
    while (std::getline(fileIng, line)) {
        if (line.empty()) continue;
        if (line.find(',') == std::string::npos) continue;

        std::stringstream ss(line);
        int id = 0, cantidad = 0, unidad = 0;
        char delim;

        if (!(ss >> id >> delim >> cantidad >> delim >> unidad)) {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::stringstream ss2(line);
            if (!(ss2 >> id >> cantidad >> unidad)) continue;
        }

        std::string nombre = obtenerNombreIngrediente(id);
        std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";

        out << nombre << ": " << cantidad << " " << unidadStr << "\n";
    }

    fileIng.close();
    return out.str();
}

std::string Encargado_Inventario::stockProductosTerminados() {
    std::ostringstream out;
    const std::string stockFileName = "STOCK.txt";
    std::ifstream fileStock(stockFileName);
    if (!fileStock.is_open()) {
        return "⚠ No se pudo abrir " + stockFileName;
    }

    out << "=== STOCK PRODUCTOS TERMINADOS ===\n";
    std::string line;
    while (std::getline(fileStock, line)) {
        if (line.empty()) continue;
        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        std::string nombre = line.substr(0, comma);
        std::string cantidadStr = line.substr(comma + 1);

        while (!nombre.empty() && (nombre.front() == ' ' || nombre.front() == '\t')) nombre.erase(0,1);
        while (!cantidadStr.empty() && (cantidadStr.front() == ' ' || cantidadStr.front() == '\t')) cantidadStr.erase(0,1);

        out << nombre << ": " << cantidadStr << "\n";
    }

    fileStock.close();
    return out.str();
}
