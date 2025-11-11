#ifndef PROYECTO_PANADERIA_BUEN_TRIGO_INGREDIENTE_H
#define PROYECTO_PANADERIA_BUEN_TRIGO_INGREDIENTE_H

class Ingrediente {

    private:

    int Id;
    int Cantidad;
    int Unidad;
//    Inventario inv;

    public:
    Ingrediente();
    Ingrediente(int id, int Cantidad);
    Ingrediente(int Id , int Unidad , int Cantidad);
  //  void SubirInventario(Inventario inv);
    int getId() const;
    int getCantidad() const;
    int getUnidad() const;
    void setCantidad(int c) { Cantidad = c; }
    void setUnidad(int u) { Unidad = u; }

};


#endif //PROYECTO_PANADERIA_BUEN_TRIGO_INGREDIENTE_H