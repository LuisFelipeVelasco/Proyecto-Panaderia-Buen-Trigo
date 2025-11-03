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
                    std::vector<Ingrediente> receta ={};
                    std::string nombre;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita El nombre de la receta: \n";
                    getline(std::cin, nombre);

                    int Id{};
                    int Cantidad{};

                    do {
                        std::cout << "1. Harina\n";
                        std::cout << "2. Azucar\n";
                        std::cout << "3. Sal\n";
                        std::cout << "4. Levadura\n";
                        std::cout << "5. Huevos\n";
                        std::cout << "6. Canela\n";
                        std::cout << "7. Queso\n";
                        std::cout << "8. Mantequilla\n";
                        std::cout << "9. No mas ingredientes\n";
                        std::cout << "Escoge el ingrediente de tu receta ";
                        std::cin >> Id;
                        if (Id!=9) {
                            std::cout<<"Digita la cantidad del ingrediente (gramos): ";
                            std::cin>>Cantidad;
                            Ingrediente ingredientenuevo(Id, Cantidad);
                            receta.push_back(ingredientenuevo);

                        }
                    }while (Id!=9);

                    Receta RecetaNueva(nombre, receta);
                    RecetaNueva.mostrarReceta();
                    Panadero1.RegistrarReceta(RecetaNueva);
                }
                else if (opcion==2) {



                }
                else if (opcion==3) {
                    std::string nombreReceta{};
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita el nombre de la receta a eliminar";
                    std::getline(std::cin, nombreReceta);
                    Panadero1.eliminarReceta(nombreReceta);


                }

                else if (opcion==6) {
                    Panadero1.CerrarSesion();
                    opcion1=4;
                }



            }while (opcion!=6);
        }
        else if (opcion1==2) { //////
            std::string nombre{};
            std::string apellido{};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<" Digita tu nombre";
            getline(std::cin, nombre);
            std::cout<<" Digita tu apellido";
            getline(std::cin, apellido);
            Encargado_Inventario Encargado1(nombre, apellido);
            Encargado1.IniciarSesion();
            int opcion2{};
            do {
                std::cout<<"1. Registrar Ingredientes Disponibles\n";
                std::cout<<"2. Actualizar Ingredientes \n";
                std::cout<<"3. Eliminar Ingredientes \n";
                std::cout<<"4. Consultar existencias actuales\n";
                std::cout<<"5. Ver ingredientes apunto de agotarse\n";
                std::cout<<"6. Ver Resumen del inventario y del Stock\n";
                std::cout<<"7. Salir\n";
                std::cin>>opcion2;
                if (opcion2==1) {
                    std::vector<Ingrediente> ingredientes{};
                    std::string unidad{};
                    int Id{}, Cantidad{}, Unidad{};
                    do {
                        std::cout << "1. Harina\n";
                        std::cout << "2. Azucar\n";
                        std::cout << "3. Sal\n";
                        std::cout << "4. Levadura\n";
                        std::cout << "5. Huevos\n";
                        std::cout << "6. Canela\n";
                        std::cout << "7. Queso\n";
                        std::cout << "8. Mantequilla\n";
                        std::cout << "9. No mas ingredientes\n";
                        std::cout << "Escoge el ingrediente: ";
                        std::cin >> Id;
                        if (Id!=9) {
                            std::cout << "1. Libra\n";
                            std::cout << "2. Gramo\n";
                            std::cout<<"Escoga la Unidad de medida\n";
                            std::cin>>Unidad;

                            std::cout<<"Digita la cantidad del ingrediente";
                            std::cin>>Cantidad;

                            Ingrediente ingredientenuevo(Id,Unidad,Cantidad);
                            ingredientes.push_back(ingredientenuevo);


                        }
                    }while (Id!=9);

                    Encargado1.RegistarNuevoIngrediente(ingredientes);

                }
                else if (opcion2==7) {
                    Encargado1.CerrarSesion();
                    opcion1=4;
                }


            }while (opcion2!=7);




        }

    } while (opcion1 != 4);

    return 0;
}