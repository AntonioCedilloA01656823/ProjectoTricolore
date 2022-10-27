template <typename T> class Carrito {
private:
  LinkedList<T> pedidos;
  int total;

public:
  Carrito() { total = 0; }
  int pagar(string usuario) {
    cout << "Estos son sus pedidos: " << endl;
    for (int i = 0; i < pedidos.size(); i++) {
      T p = pedidos.get(i);
      cout << p << endl;
    }
    cout << "El total de su compra es de:  $" << total << endl;
    return total;
  }

  void addProducto(T pizzaSelect) {
    cout << "Usted ha seleccionado: " << endl;
    cout << pizzaSelect << endl;
    pedidos.addLast(pizzaSelect);
    total += pizzaSelect.getPrecio();
  }

  LinkedList<T> getProducts(){
    return pedidos;
  }
};
