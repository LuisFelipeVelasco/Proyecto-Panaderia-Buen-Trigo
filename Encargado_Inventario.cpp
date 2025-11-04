//
// Created by luisf on 2/11/2025.
//

#include "Encargado_Inventario.h"
#include "Receta.h"
#include <sstream>
#include <algorithm>
#include <cstdio>

Encargado_Inventario::Encargado_Inventario(std::string &nombre, std::string &apellidos): Personal(nombre,apellidos) {}

void Encargado_Inventario::RegistarNuevoIngrediente(std::vector<Ingrediente>& ingredientes ) {
    std::ofstream file(fileName , std::ios::app);
    if (file.is_open()) {
        for (auto i:ingredientes ) {
            file << i.getId() << " , " << i.getCantidad()  << " , " << i.getUnidad()<<";"<<"\n";
        }
        file.close();
        std::cout << "Datos guardados exitosamente.\n";
    } else {
        std::cerr << "Error: No se pudo abrir el archivo de datos.\n";
    }
}

// REQUERIMIENTO 1: Consultar inventario y ver cantidad de un ingrediente específico
void Encargado_Inventario::ConsultarInventario() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de ingredientes.\n";
        return;
    }

    std::cout << "\n===== INVENTARIO DE INGREDIENTES =====\n";
    std::cout << "1. Harina\n2. Azucar\n3. Sal\n4. Levadura\n";
    std::cout << "5. Huevos\n6. Canela\n7. Queso\n8. Mantequilla\n";

    std::string line;
    std::vector<std::string> lineas;
    while (std::getline(file, line)) {
        if (!line.empty() && line.find(',') != std::string::npos) {
            lineas.push_back(line);
        }
    }
    file.close();

    if (lineas.empty()) {
        std::cout << "No hay ingredientes registrados.\n";
        return;
    }

    std::cout << "\nIngredientes disponibles en el inventario:\n";
    for (const auto& l : lineas) {
        std::stringstream ss(l);
        int id, cantidad, unidad;
        char delim;
        ss >> id >> delim >> cantidad >> delim >> unidad;

        std::string nombre = obtenerNombreIngrediente(id);
        std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";
        std::cout << "  - " << nombre << ": " << cantidad << " " << unidadStr << "\n";
    }

    std::cout << "\n¿Desea consultar un ingrediente específico? (1=Si, 0=No): ";
    int opcion;
    std::cin >> opcion;

    if (opcion == 1) {
        std::cout << "Seleccione el ingrediente (1-8): ";
        int idBuscar;
        std::cin >> idBuscar;

        bool encontrado = false;
        for (const auto& l : lineas) {
            std::stringstream ss(l);
            int id, cantidad, unidad;
            char delim;
            ss >> id >> delim >> cantidad >> delim >> unidad;

            if (id == idBuscar) {
                std::string nombre = obtenerNombreIngrediente(id);
                std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";
                std::cout << "\n=== " << nombre << " ===\n";
                std::cout << "Cantidad disponible: " << cantidad << " " << unidadStr << "\n";
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            std::cout << "Ingrediente no encontrado en el inventario.\n";
        }
    }
}

// REQUERIMIENTO 2: Verificar ingredientes por debajo del tope mínimo
void Encargado_Inventario::VerificarInventarioBajo() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de ingredientes.\n";
        return;
    }

    // Topes mínimos sugeridos (en gramos o unidad correspondiente)
    const int TOPE_MINIMO = 50; // Tope general

    std::cout << "\n===== INGREDIENTES POR DEBAJO DEL TOPE =====\n";
    std::cout << "Tope mínimo establecido: " << TOPE_MINIMO << " unidades\n\n";

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
            std::cout << "⚠️  " << nombre << ": " << cantidad << " " << unidadStr
                      << " (Faltan " << (TOPE_MINIMO - cantidad) << " para el tope)\n";
            hayBajos = true;
        }
    }

    file.close();

    if (!hayBajos) {
        std::cout << "✓ Todos los ingredientes están por encima del tope mínimo.\n";
    } else {
        std::cout << "\n⚠️  Se recomienda reabastecer estos ingredientes.\n";
    }
}

// REQUERIMIENTO 3: Eliminar ingrediente
void Encargado_Inventario::EliminarIngrediente() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de ingredientes.\n";
        return;
    }

    std::vector<std::string> lineas;
    std::string line;

    std::cout << "\n===== ELIMINAR INGREDIENTE =====\n";
    std::cout << "Ingredientes actuales:\n";

    while (std::getline(file, line)) {
        if (!line.empty() && line.find(',') != std::string::npos) {
            lineas.push_back(line);
            std::stringstream ss(line);
            int id, cantidad, unidad;
            char delim;
            ss >> id >> delim >> cantidad >> delim >> unidad;

            std::string nombre = obtenerNombreIngrediente(id);
            std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";
            std::cout << id << ". " << nombre << ": " << cantidad << " " << unidadStr << "\n";
        }
    }
    file.close();

    if (lineas.empty()) {
        std::cout << "No hay ingredientes para eliminar.\n";
        return;
    }

    std::cout << "\nSeleccione el ID del ingrediente a eliminar (1-8): ";
    int idEliminar;
    std::cin >> idEliminar;

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
        std::cout << "No se encontró el ingrediente con ID " << idEliminar << ".\n";
        return;
    }

    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Error al crear archivo temporal.\n";
        return;
    }

    for (const auto& l : lineas) {
        out << l << "\n";
    }
    out.close();

    std::remove(fileName.c_str());
    if (std::rename(tmp.c_str(), fileName.c_str()) != 0) {
        std::cerr << "Error al reemplazar el archivo.\n";
        return;
    }

    std::cout << "Ingrediente eliminado correctamente.\n";
}

// REQUERIMIENTO 4: Editar ingrediente (cantidad o unidad)
void Encargado_Inventario::EditarIngrediente() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de ingredientes.\n";
        return;
    }

    std::vector<std::string> lineas;
    std::string line;

    std::cout << "\n===== EDITAR INGREDIENTE =====\n";
    std::cout << "Ingredientes actuales:\n";

    while (std::getline(file, line)) {
        if (!line.empty() && line.find(',') != std::string::npos) {
            lineas.push_back(line);
            std::stringstream ss(line);
            int id, cantidad, unidad;
            char delim;
            ss >> id >> delim >> cantidad >> delim >> unidad;

            std::string nombre = obtenerNombreIngrediente(id);
            std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";
            std::cout << id << ". " << nombre << ": " << cantidad << " " << unidadStr << "\n";
        }
    }
    file.close();

    if (lineas.empty()) {
        std::cout << "No hay ingredientes para editar.\n";
        return;
    }

    std::cout << "\nSeleccione el ID del ingrediente a editar (1-8): ";
    int idEditar;
    std::cin >> idEditar;

    bool encontrado = false;
    for (auto& l : lineas) {
        std::stringstream ss(l);
        int id, cantidad, unidad;
        char delim;
        ss >> id >> delim >> cantidad >> delim >> unidad;

        if (id == idEditar) {
            encontrado = true;
            std::string nombre = obtenerNombreIngrediente(id);
            std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";

            std::cout << "\nIngrediente seleccionado: " << nombre << "\n";
            std::cout << "Cantidad actual: " << cantidad << " " << unidadStr << "\n";
            std::cout << "\n¿Qué desea modificar?\n";
            std::cout << "1. Cantidad\n2. Unidad\n3. Ambos\nOpción: ";
            int opcion;
            std::cin >> opcion;

            int nuevaCantidad = cantidad;
            int nuevaUnidad = unidad;

            if (opcion == 1 || opcion == 3) {
                std::cout << "Nueva cantidad: ";
                std::cin >> nuevaCantidad;
            }

            if (opcion == 2 || opcion == 3) {
                std::cout << "Nueva unidad (1=Libras, 2=Gramos): ";
                std::cin >> nuevaUnidad;
            }

            std::stringstream nueva;
            nueva << id << " , " << nuevaCantidad << " , " << nuevaUnidad << ";";
            l = nueva.str();

            std::cout << "✓ Ingrediente actualizado correctamente.\n";
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró el ingrediente con ID " << idEditar << ".\n";
        return;
    }

    std::string tmp = fileName + ".tmp";
    std::ofstream out(tmp, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Error al crear archivo temporal.\n";
        return;
    }

    for (const auto& l : lineas) {
        out << l << "\n";
    }
    out.close();

    std::remove(fileName.c_str());
    if (std::rename(tmp.c_str(), fileName.c_str()) != 0) {
        std::cerr << "Error al reemplazar el archivo.\n";
        return;
    }
}

// Función auxiliar para obtener nombre del ingrediente por ID
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