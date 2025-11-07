// Administrador.cpp
#include "Administrador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

Administrador::Administrador(std::string& nombre, std::string& apellido)
    : Personal(nombre, apellido), nombre(nombre), apellido(apellido) { }

// -----------------------------
// obtenerNombreIngrediente
// -----------------------------
std::string Administrador::obtenerNombreIngrediente(int id) {
    switch (id) {
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

// -----------------------------
// resumenInventario
// Lee Ingredientes.txt (id,cantidad,unidad)
// -----------------------------
std::string Administrador::resumenInventario() {
    std::ostringstream out;
    std::ifstream fileIng(fileName); // fileName declarado en el .h como "Ingredientes.txt"
    if (!fileIng.is_open()) {
        out << "⚠ No se pudo abrir " << fileName << "\n";
        return out.str();
    }

    out << "=== INVENTARIO DE INGREDIENTES ===\n";
    out << std::left << std::setw(20) << "Ingrediente"
        << std::setw(12) << "Cantidad"
        << std::setw(10) << "Unidad" << "\n";
    out << "---------------------------------------------\n";

    std::string line;
    while (std::getline(fileIng, line)) {
        if (line.empty()) continue;
        if (line.find(',') == std::string::npos) continue;

        std::stringstream ss(line);
        int id = 0, cantidad = 0, unidad = 0;
        char delim;

        if (!(ss >> id >> delim >> cantidad >> delim >> unidad)) {
            // Si el parseo falla, intentar parsing más tolerante:
            // por ejemplo "1, 500, 2"
            std::replace(line.begin(), line.end(), ',', ' ');
            std::stringstream ss2(line);
            if (!(ss2 >> id >> cantidad >> unidad)) continue;
        }

        std::string nombre = obtenerNombreIngrediente(id);
        std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";

        out << std::left << std::setw(20) << nombre
            << std::setw(12) << cantidad
            << std::setw(10) << unidadStr << "\n";
    }

    fileIng.close();
    return out.str();
}

// -----------------------------
// stockProductosTerminados
// Lee STOCK.txt (Nombre,Numero)
// -----------------------------
std::string Administrador::stockProductosTerminados() {
    std::ostringstream out;
    const std::string stockFileName = "STOCK.txt"; // coincide con el zip
    std::ifstream fileStock(stockFileName);
    if (!fileStock.is_open()) {
        out << "⚠ No se pudo abrir " << stockFileName << "\n";
        return out.str();
    }

    out << "=== STOCK PRODUCTOS TERMINADOS ===\n";
    out << std::left << std::setw(25) << "Producto" << std::setw(10) << "Cantidad" << "\n";
    out << "---------------------------------------------\n";

    std::string line;
    while (std::getline(fileStock, line)) {
        if (line.empty()) continue;
        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        std::string nombre = line.substr(0, comma);
        std::string cantidadStr = line.substr(comma + 1);

        // limpiar espacios iniciales en nombre
        while (!nombre.empty() && (nombre.front() == ' ' || nombre.front() == '\t')) nombre.erase(0,1);
        while (!cantidadStr.empty() && (cantidadStr.front() == ' ' || cantidadStr.front() == '\t')) cantidadStr.erase(0,1);

        out << std::left << std::setw(25) << nombre << std::setw(10) << cantidadStr << "\n";
    }

    fileStock.close();
    return out.str();
}

// -----------------------------
// ConsultarInventario -> imprime en consola
// -----------------------------
void Administrador::ConsultarInventario() {
    std::cout << resumenInventario() << std::endl;
    std::cout << stockProductosTerminados() << std::endl;

    // Pregunta adicional opcional (si deseas mantener comportamiento igual a Encargado)
    std::cout << "\n¿Desea consultar un ingrediente específico? (1=Si, 0=No): ";
    int opcion = 0;
    if (std::cin >> opcion && opcion == 1) {
        std::cout << "Seleccione el ingrediente (1-8): ";
        int idBuscar = 0;
        std::cin >> idBuscar;

        // Re-abrir archivo para buscar
        std::ifstream fileIng(fileName);
        bool encontrado = false;
        std::string line;
        while (std::getline(fileIng, line)) {
            if (line.empty() || line.find(',') == std::string::npos) continue;
            std::stringstream ss(line);
            int id = 0, cantidad = 0, unidad = 0;
            char delim;
            if (!(ss >> id >> delim >> cantidad >> delim >> unidad)) continue;

            if (id == idBuscar) {
                std::string nombre = obtenerNombreIngrediente(id);
                std::string unidadStr = (unidad == 1) ? "Libras" : "Gramos";
                std::cout << "\n=== " << nombre << " ===\n";
                std::cout << "Cantidad disponible: " << cantidad << " " << unidadStr << "\n";
                encontrado = true;
                break;
            }
        }
        fileIng.close();
        if (!encontrado) std::cout << "Ingrediente no encontrado en el inventario.\n";
    }
}

// -----------------------------
// exportarReporte -> escribe Reporte_Inventario.txt
// -----------------------------
void Administrador::exportarReporte() {
    const std::string outFile = "Reporte_Inventario.txt";
    std::ofstream out(outFile);
    if (!out.is_open()) {
        std::cerr << "❌ Error: no se pudo crear " << outFile << "\n";
        return;
    }

    // encabezado
    out << "===== REPORTE DE INVENTARIO =====\n\n";
    out << "Administrador: " << nombre << " " << apellido << "\n\n";

    // ingredientes
    out << resumenInventario() << "\n";

    // stock
    out << stockProductosTerminados() << "\n";

    out << "===== FIN DEL REPORTE =====\n";
    out.close();

    std::cout << "✅ Reporte generado: " << outFile << "\n";
}
