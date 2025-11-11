#include "Visual.h"
#include <iostream>

Visual::Visual(){}

int Visual::DesplegarMenuDeUsuario() {
    int opcion1{};
    std::cout << "\n===== Sistema de Gestion : Panaderia =====\n";
    std::cout << "1. Panadero\n";
    std::cout << "2. Encargado del inventario\n";
    std::cout << "3. Administrador\n";
    std::cout << "4. Salir\n";
    std::cout << "Escoge tu rol  o Salir: ";
    std::cin >> opcion1;
    return opcion1;

}

int Visual::DesplegarInventario() {
    int Id{};
    std::cout << "1. Harina\n";
    std::cout << "2. Azucar\n";
    std::cout << "3. Sal\n";
    std::cout << "4. Levadura\n";
    std::cout << "5. Huevos\n";
    std::cout << "6. Canela\n";
    std::cout << "7. Queso\n";
    std::cout << "8. Mantequilla\n";
    std::cout << "9. No mas ingredientes\n";
    std::cout << "Escoge el ingrediente : ";
    std::cin >> Id;
    return Id;
}

int Visual::DesplegarMenuDePanadero() {
    int opcion{};
    std::cout<<"\n";
    std::cout << "1. Registrar Receta\n";
    std::cout << "2. Modificar Receta\n";
    std::cout << "3. Eliminar Receta\n ";
    std::cout << "4. Registrar Nueva Produccion\n";
    std::cout << "5. Consultar STOCK\n";
    std::cout << "6. Salir\n";
    std::cout << "Panadero , escoge que quieres hacer: ";
    std::cin >> opcion;
    return opcion;
}

int Visual::DesplegarMenuDeGestorDeInventario() {
    int opcion2{};
    std::cout<<"\n===== MENU ENCARGADO DE INVENTARIO =====\n";
    std::cout<<"1. Registrar Ingredientes Disponibles\n";
    std::cout<<"2. Consultar Inventario\n";
    std::cout<<"3. Ver ingredientes por debajo del tope\n";
    std::cout<<"4. Editar Ingredientes\n";
    std::cout<<"5. Eliminar Ingredientes\n";
    std::cout<<"6. Ver Resumen del inventario y del Stock\n";
    std::cout<<"7. Salir\n";
    std::cout<<"Seleccione una opcion: ";
    std::cin>>opcion2;
    return opcion2;
}

int Visual::DesplegarMenuDeAdministrador() {
    int opcion3{};
    std::cout<<"\n===== MENU ADMINISTRADOR =====\n";
    std::cout<<"1. Ver resumen inventario / stock\n";
    std::cout<<"2. Generar Reporte\n";
    std::cout<<"3. Salir\n";
    std::cout<<"Seleccione una opcion: ";
    std::cin>>opcion3;
    return opcion3;
}