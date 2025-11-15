/*
===============================================================================
                 IMPLEMENTACIÓN DE LA CLASE Visual
===============================================================================
Rol en el dominio:
- Menús por rol de usuario; 
- Patrón MVC: componente de Vista

Se demuestra:
- Integración con Visual para interacción
===============================================================================
*/
#include "Visual.h"
#include <iostream>

Visual::Visual(){}

void Visual::IniciarPrograma(Encargado_Inventario& ControlEncargado) {
    int opcion1;
    do {
        opcion1=DesplegarMenuDeUsuario();
        if (opcion1==1) {
            std::string nombre{};
            std::string apellido{};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Digita tu nombre: ";
            getline(std::cin, nombre);
            std::cout<<"Digita tu apellido: " ;
            getline(std::cin, apellido);
            Panadero Panadero1(nombre, apellido);
            IniciarSesion(Panadero1);
            int opcion;
            do {
                opcion=DesplegarMenuDePanadero();
                if (opcion==1) {
                    std::vector<Ingrediente> receta ={};
                    std::string nombre;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita El nombre de la receta: \n";
                    getline(std::cin, nombre);

                    int Id{};
                    int Cantidad{};

                    do {
                        Id=DesplegarInventario();
                        if (Id!=9) {
                            std::cout<<"Digita la cantidad del ingrediente (gramos): ";
                            std::cin>>Cantidad;
                            Ingrediente ingredientenuevo(Id, Cantidad);
                            receta.push_back(ingredientenuevo);
                        }
                    }while (Id!=9);

                    Receta RecetaNueva(nombre, receta);
                    MostrarReceta(RecetaNueva);
                    RegistrarReceta(Panadero1, RecetaNueva);
                }
                else if (opcion==2) {
                    // Modificar receta
                    std::string nombreOriginal{};
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita el nombre de la receta a modificar: ";
                    std::getline(std::cin, nombreOriginal);
                    
                    // Show current recipe
                    auto recetas = Panadero1.GetRecetas();
                    bool encontrada = false;
                    for (const auto& r : recetas) {
                        if (r.getNombre() == nombreOriginal) {
                            std::cout << "\n=== Receta actual ===\n";
                            MostrarReceta(r);
                            encontrada = true;
                            break;
                        }
                    }
                    
                    if (!encontrada) {
                        std::cout << "❌ Receta no encontrada: " << nombreOriginal << "\n";
                        continue;
                    }
                    
                    // Gather new recipe data
                    std::cout << "\nIngrese los nuevos datos de la receta:\n";
                    std::string nuevoNombre;
                    std::cout << "Nuevo nombre (o presione Enter para mantener '" << nombreOriginal << "'): ";
                    std::getline(std::cin, nuevoNombre);
                    if (nuevoNombre.empty()) {
                        nuevoNombre = nombreOriginal;
                    }
                    
                    std::vector<Ingrediente> nuevosIngredientes{};
                    int Id{}, Cantidad{};
                    std::cout << "\nIngrese los ingredientes:\n";
                    do {
                        Id = DesplegarInventario();
                        if (Id != 9) {
                            std::cout << "Digita la cantidad del ingrediente (gramos): ";
                            std::cin >> Cantidad;
                            Ingrediente ingredientenuevo(Id, Cantidad);
                            nuevosIngredientes.push_back(ingredientenuevo);
                        }
                    } while (Id != 9);
                    
                    Receta recetaActualizada(nuevoNombre, nuevosIngredientes);
                    std::string mensaje;
                    if (Panadero1.modificarReceta(nombreOriginal, recetaActualizada, mensaje)) {
                        std::cout << mensaje << "\n";
                    } else {
                        std::cout << "❌ " << mensaje << "\n";
                    }
                }
                else if (opcion==3) {
                    std::string nombreReceta{};
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"Digita el nombre de la receta a eliminar: ";
                    std::getline(std::cin, nombreReceta);
                    std::string mensaje;
                    if (Panadero1.eliminarReceta(nombreReceta, mensaje)) {
                        std::cout << mensaje << "\n";
                    } else {
                        std::cout << "❌ " << mensaje << "\n";
                    }
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
                    int ValidadorProduccion=Panadero1.RegistrarProduccion(nombreReceta, cantidad, ControlEncargado);
                    // Registrar producción en archivo
                    if (ValidadorProduccion) Panadero1.registrarNuevaProduccion(*r, cantidad);
                }
                else if (opcion == 5) {
                    std::cout << "\n=== STOCK ACTUAL ===\n";
                    std::string stock = Panadero1.consultarStock();
                    std::cout << stock << std::endl;
                }
                else if (opcion==6) {
                    CerrarSesion(Panadero1);
                    opcion1=4;
                }

            }while (opcion!=6);
        }

        else if (opcion1==2) {
            std::string nombre{};
            std::string apellido{};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Digita tu nombre: ";
            getline(std::cin, nombre);
            std::cout<<"Digita tu apellido: ";
            getline(std::cin, apellido);
            // Actualiza el encargado existente (NO lo vuelvas a declarar)
            Encargado_Inventario Encargado1(nombre, apellido);
            IniciarSesion(Encargado1);
            int opcion2{};
            do {
                opcion2=DesplegarMenuDeGestorDeInventario();

                if (opcion2==1) {
                    std::vector<Ingrediente> ingredientes{};
                    std::string unidad{};
                    int Id{}, Cantidad{}, Unidad{};
                    do {
                        Id=DesplegarInventario();
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
                    std::string inventario = Encargado1.ConsultarInventario();
                    std::cout << inventario;
                }
                else if (opcion2==3) {
                    std::string alertas = Encargado1.VerificarInventarioBajo();
                    std::cout << alertas;
                }
                else if (opcion2==4) {
                    std::cout << "\nEditar Ingrediente\n";
                    std::cout << "Ingrese ID del ingrediente (1-8): ";
                    int idEditar;
                    std::cin >> idEditar;
                    std::cout << "Nueva cantidad: ";
                    int nuevaCant;
                    std::cin >> nuevaCant;
                    std::cout << "Nueva unidad (1=Libras, 2=Gramos): ";
                    int nuevaUnid;
                    std::cin >> nuevaUnid;
                    std::string mensaje;
                    if (Encargado1.EditarIngrediente(idEditar, nuevaCant, nuevaUnid, mensaje)) {
                        std::cout << mensaje << "\n";
                    } else {
                        std::cout << "❌ " << mensaje << "\n";
                    }
                }
                else if (opcion2==5) {
                    std::cout << "\nEliminar Ingrediente\n";
                    std::cout << "Ingrese ID del ingrediente a eliminar (1-8): ";
                    int idEliminar;
                    std::cin >> idEliminar;
                    std::string mensaje;
                    if (Encargado1.EliminarIngrediente(idEliminar, mensaje)) {
                        std::cout << mensaje << "\n";
                    } else {
                        std::cout << "❌ " << mensaje << "\n";
                    }
                }
                else if (opcion2==6) {
                    std::cout << Encargado1.resumenInventario() << std::endl;
                    std::cout << Encargado1.stockProductosTerminados() << std::endl;

                }
                else if (opcion2==7) {
                    CerrarSesion(Encargado1);
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
            IniciarSesion(Administrador1);
            int opcion3{};
            do {
                opcion3=DesplegarMenuDeAdministrador();
                if (opcion3==1) {
                    std::cout << Administrador1.resumenInventario() << std::endl;
                    std::cout << Administrador1.stockProductosTerminados() << std::endl;
                }
                else if (opcion3==2) {
                    std::string mensaje;
                    if (Administrador1.exportarReporte(mensaje)) {
                        std::cout << mensaje << "\n";
                    } else {
                        std::cout << "❌ " << mensaje << "\n";
                    }
                }
                else if (opcion3==3) {
                    CerrarSesion(Administrador1);
                    opcion1=4;
                }
            }while (opcion3!=3);
        }
    }while (opcion1!=4);


}

void Visual::IniciarSesion(Personal usuario) {
    std::cout<<"Bienvenido "<<usuario.getNombre()<<" "<<usuario.getApellido()<<" has iniciado sesion"<<std::endl;
}
void Visual::CerrarSesion(Personal usuario) {
    std::cout<<"Adios "<<usuario.getNombre()<<" "<<usuario.getApellido()<<" has cerrado sesion"<<std::endl;
}


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

void Visual::MostrarReceta(const Receta& receta) {
    std::cout<<"Receta registrada:"<<std::endl<<std::endl;
    std::cout<<"======= "<<receta.getNombre()<<" ======"<<std::endl;
    for (Ingrediente i : receta.getIngredientes()) {
        std::cout<<"Ingrediente:"<<i.getId()<<std::endl;
        std::cout<<"Cantidad:"<<i.getCantidad()<<std::endl;
    }
}

void Visual::RegistrarReceta(Panadero& panadero1, Receta& receta) {
    bool exito=panadero1.RegistrarReceta(receta);
    if (exito) std::cout<<"Datos guardados exitosamente"<<std::endl;
    else std::cout<<"Error No se pudo abrir el archivo de datos"<<std::endl;
}