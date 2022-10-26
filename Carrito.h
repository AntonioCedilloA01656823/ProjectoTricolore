template <typename T> class Carrito {
private:
  LinkedList<T> pedidos;
  int total;

public:
  void pagar() {
    int total;
    cout << "Estos son sus pedidos: " << endl;
    for (int i = 0; i < pedidos.size(); i++) {
      T p = pedidos.get(i);
      total += p.getPrecio();
      cout << p;
    }
    cout << "El total de su compra es de:  $" << total << endl;
  }
  void addProducto(T &pizzaSelect) {
    cout << "Usted ha seleccionado: "<<endl;
    cout<< pizzaSelect <<endl;
    pedidos.addLast(pizzaSelect);
  }
};
