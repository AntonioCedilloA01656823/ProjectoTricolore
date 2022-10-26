class Pizza {
private:
  string pizza, tamanho, extra;
  int id, precio;

public:
  // id,pizza,size,extra,precio
  Pizza(int id = 0, string pizza = "N/A", string tamanho = "N/A",
        string extra = "N/A", int precio = 0) {
    this->id = id;
    this->pizza = pizza;
    this->tamanho = tamanho;
    this->extra = extra;
    this->precio = precio;
  }
  string getPizza() { return this->pizza; }
  int getPrecio() { return this->precio; }
  int getID() { return this->id; }

  bool operator==(const Pizza &pizza) { return (this->id == pizza.id); }
  bool operator==(const string &pizza) {
    return (this->pizza.compare(pizza) == 0);
  }
  bool operator>(Pizza &pizza) { return (this->id > pizza.id); }
  bool operator<(Pizza &pizza) { return (this->id < pizza.id); }

  friend ostream &operator<<(ostream &, const Pizza &);
};

ostream &operator<<(ostream &salida, const Pizza &pizza) {
  salida << pizza.id << " || " << pizza.pizza << " " << pizza.tamanho << ": $"
         << pizza.precio << " con " << pizza.extra;
  return salida;
};