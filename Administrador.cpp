/*
===============================================================================
                 IMPLEMENTACIÓN DE LA CLASE Administrador
===============================================================================
Rol en el dominio:
- Consultar resúmenes globales de inventario y stock para supervisión (HU07, HU08)
- Exportar reportes a .txt para control y seguimiento (HU08)
- Supervisar la disponibilidad de productos para la venta

Se demuestra:
- Encapsulación y uso de getters/setters
- Paso de objetos por referencia
- Integración con Visual para interacción/alertas/reportes
- Validaciones ligadas a: HU07, HU08
===============================================================================
*/
#include "Administrador.h"
#include <fstream>
#include <sstream>
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
// Lee Inventario.txt y retorna string formateado
// -----------------------------
std::string Administrador::resumenInventario() {
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

// -----------------------------
// stockProductosTerminados
// Lee STOCK.txt y retorna string formateado
// -----------------------------
std::string Administrador::stockProductosTerminados() {
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

        // limpiar espacios iniciales
        while (!nombre.empty() && (nombre.front() == ' ' || nombre.front() == '\t')) nombre.erase(0,1);
        while (!cantidadStr.empty() && (cantidadStr.front() == ' ' || cantidadStr.front() == '\t')) cantidadStr.erase(0,1);

        out << nombre << ": " << cantidadStr << "\n";
    }

    fileStock.close();
    return out.str();
}


// -----------------------------
// exportarReporte -> escribe Reporte_Inventario.txt
// -----------------------------
bool Administrador::exportarReporte(std::string& mensaje) {
    const std::string outFile = "Reporte_Inventario.txt";
    std::ofstream out(outFile);
    if (!out.is_open()) {
        mensaje = "Error: no se pudo crear " + outFile;
        return false;
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

    mensaje = "✅ Reporte generado: " + outFile;
    return true;
}
