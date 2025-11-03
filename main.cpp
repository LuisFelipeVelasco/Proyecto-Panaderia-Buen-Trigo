//
// Created by luisf on 2/11/2025.
//

#include <iostream>

#include "Encargado_Inventario.h"
#include "Panadero.h"
#include <limits>
#include "Ingrediente.h"
#include "Receta.h"

int main() {
    int opcion1=0;
    std::vector<Ingrediente> receta ={};
    do {

        std::cout << "\n===== Sistema de Gestion : Panaderia =====\n";
        std::cout << "1. Panadero\n";
        std::cout << "2. Encargado del inventario\n";
        std::cout << "3. Administrador\n";
        std::cout << "4. Salir\n";
        std::cout << "Escoge tu rol  o Salir: ";
        std::cin >> opcion1;


        if (opcion1==1) {

            std::string nombre{};
            std::string apellido{};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Digita tu nombre: ";
            getline(std::cin, nombre);
            std::cout<<"Digita tu apellido: " ;
            getline(std::cin, apellido);
            Panadero Panadero1(nombre, apellido);
            Panadero1.IniciarSesion();

            int opcion{};
            do {
                std::cout<<"\n";
                std::cout << "1. Registrar Receta\n";
                std::cout << "2. Modificar Receta\n";
                std::cout << "3. Eliminar Receta\n ";
                std::cout << "4. Registrar Nueva Produccion\n";
                std::cout << "5. Consultar STOCK\n";
                std::cout << "6. Salir\n";
                std::cout << "Panadero , escoge que quieres hacer";
                std::cin >> opcion;

                if (opcion==1) {
                    std::string nombre;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita El nombre de la receta: \n";
                    getline(std::cin, nombre);

                    int ingrediente{};
                    int Cantidad{};

                    do {
                        std::cout << "1. Harina\n";
                        std::cout << "2. Azucar\n";
                        std::cout << "3. Sal\n";
                        std::cout << "4. Levadura\n";
                        std::cout << "5. Huevos\n";
                        std::cout << "6. Canela\n";
                        std::cout << "7. No mas ingredientes\n";
                        std::cout << "Escoge el ingrediente de tu receta ";
                        std::cin >> ingrediente;
                        if (ingrediente!=7) {
                            std::cout<<"Digita la cantidad del ingrediente: ";
                            std::cin>>Cantidad;
                            Ingrediente ingredientenuevo(ingrediente, Cantidad);
                            receta.push_back(ingredientenuevo);

                        }
                    }while (ingrediente!=7);

                    Receta RecetaNueva(nombre, receta);
                    RecetaNueva.mostrarReceta();
                    Panadero1.RegistrarReceta(RecetaNueva);
                }
                else if (opcion==2) {





                }

                else if (opcion==4) {
                    Panadero1.CerrarSesion();
                    opcion1=4;
                }



            }while (opcion!=4);
        }
        else if (opcion1==2) {
            std::string nombre{};
            std::string apellido{};
            std::cout<<" Digita tu nombre";
            getline(std::cin, nombre);
            std::cout<<" Digita tu apellido";
            getline(std::cin, apellido);
            Encargado_Inventario Encargado1(nombre, apellido);
            Encargado1.IniciarSesion();



        }

    } while (opcion1 != 4);

    return 0;
}