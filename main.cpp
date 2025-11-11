#include <iostream>
#include "Encargado_Inventario.h"
#include "Panadero.h"
#include <limits>
#include "Ingrediente.h"
#include "Receta.h"
#include "Administrador.h"
#include "Visual.h"

int main() {
    Encargado_Inventario Encargado1("sin asignar", "sin asignar");
    Visual visual;
    int opcion1=0;
    do {
        opcion1=visual.DesplegarMenuDeUsuario();

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
                opcion=visual.DesplegarMenuDePanadero();

                if (opcion==1) {
                    std::vector<Ingrediente> receta ={};
                    std::string nombre;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita El nombre de la receta: \n";
                    getline(std::cin, nombre);

                    int Id{};
                    int Cantidad{};

                    do {
                        Id=visual.DesplegarInventario();
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
                    // Modificar receta
                    std::string nombreReceta{};
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita el nombre de la receta a modificar: ";
                    std::getline(std::cin, nombreReceta);
                    Panadero1.modificarReceta(nombreReceta);
                }
                else if (opcion==3) {
                    std::string nombreReceta{};
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita el nombre de la receta a eliminar: ";
                    std::getline(std::cin, nombreReceta);
                    Panadero1.eliminarReceta(nombreReceta);
                }
                else if (opcion == 4) {
                    std::string nombreReceta;
                    int cantidad;

                    std::cin.ignore();
                    std::cout<<"Nombre de la receta: ";
                    getline(std::cin, nombreReceta);

                    std::cout << "Cantidad a producir: ";
                    std::cin >> cantidad;

                    // Buscar receta en archivo
                    auto recetas = Panadero1.GetRecetas();
                    Receta* r = nullptr;

                    for (auto &rc : recetas) {
                        if (rc.getNombre() == nombreReceta) {
                            r = &rc;
                            break;
                        }
                    }
                    if (!r) {
                        std::cout << "❌ La receta no existe.\n";
                        continue;
                    }
                    // Primero intenta producir (descontar inventario)
                    Panadero1.RegistrarProduccion(nombreReceta, cantidad, Encargado1);
                    // Registrar producción en archivo
                    Panadero1.registrarNuevaProduccion(*r, cantidad);
                }
                else if (opcion == 5) {
                    std::cout << "\n=== STOCK ACTUAL ===\n";
                    std::string stock = Panadero1.consultarStock();
                    std::cout << stock << std::endl;
                }
                else if (opcion==6) {
                    Panadero1.CerrarSesion();
                    opcion1=4;
                }
            }while (opcion!=6);
        }
        else if (opcion1==2) {
            std::string nombre{};
            std::string apellido{};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // std::cout<<"Digita tu nombre: ";
            // getline(std::cin, nombre);
            // std::cout<<"Digita tu apellido: ";
            // getline(std::cin, apellido);
            // Actualiza el encargado existente (NO lo vuelvas a declarar)
            nombre="Luis";
            apellido="Velasco";
            Encargado_Inventario Encargado1(nombre, apellido);
            Encargado1.IniciarSesion();
            int opcion2{};
            do {
                opcion2=visual.DesplegarMenuDeGestorDeInventario();

                if (opcion2==1) {
                    std::vector<Ingrediente> ingredientes{};
                    std::string unidad{};
                    int Id{}, Cantidad{}, Unidad{};
                    do {
                        Id=visual.DesplegarInventario();
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
                else if (opcion2==2) {
                    Encargado1.ConsultarInventario();
                }
                else if (opcion2==3) {
                    Encargado1.VerificarInventarioBajo();
                }
                else if (opcion2==4) {
                    Encargado1.EditarIngrediente();
                }
                else if (opcion2==5) {
                    Encargado1.EliminarIngrediente();
                }
                else if (opcion2==6) {
                    Encargado1.ResumenInventarioYStock();

                }
                else if (opcion2==7) {
                    Encargado1.CerrarSesion();
                    opcion1=4;
                }

            }while (opcion2!=7);
        }
        else if (opcion1==3) {
            std::string nombre{};
            std::string apellido{};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Digita tu nombre: ";
            getline(std::cin, nombre);
            std::cout<<"Digita tu apellido: ";
            getline(std::cin, apellido);
            Administrador Administrador1(nombre, apellido);
            Administrador1.IniciarSesion();
            int opcion3{};
            do {
                opcion3=visual.DesplegarMenuDeAdministrador();
                if (opcion3==1) {
                    Administrador1.ResumenInventarioYStock();
                }
                else if (opcion3==2) {
                    // imprimir reporte
                    Administrador1.exportarReporte();
                }
                else if (opcion3==3) {
                    Administrador1.CerrarSesion();
                    opcion1=4;
                }
            }while (opcion3!=3);
        }

    }while (opcion1!=4);
}