// <!> README
// Para seleccionar una base de datos particular, ingresar las siguientes
// instrucciones en terminal:
// >> g++ main.cpp -o main
// >> ./main <nombre del archivo.csv>
// Ejemplo: ./main bitacora-pico.csv
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;
#include "lista.h"
#include "hashtable.h"
#include "Pizza.h"
#include "Carrito.h"

// Archivo leídos automáticamente:
#define _ARCHIVO_ "pizzaDB.csv"
#define _USERS_ "usuarios.csv"
/* O(n) */
void makeList(LinkedList<Pizza> &pizzas, string archivo) {
  ifstream fin;
  fin.open(archivo);
  // Error en caso de no poder abrir el archivo o no encontrarlo
  // O(1)
  if (fin.fail()) { // O(n)
    cout << "ERROR: Failed to open file ";
    throw -1;
  }

  // Variables en las que se va a almacenar la info.
  // id,pizza,tamanho,extra,precio
  string linea;
  // Saltar la cabecera
  getline(fin, linea);

  // Ciclo para recuperar los datos

  while (getline(fin, linea)) { // O(n)
    // ID
    linea = linea.substr(0, linea.length());
    int id = stoi(linea.substr(0, linea.find(",")));

    // pizza
    linea = linea.substr(linea.find(",") + 1, linea.length());
    string pizza = linea.substr(0, linea.find(","));

    // tamanho
    linea = linea.substr(linea.find(",") + 1, linea.length());
    string tamanho = linea.substr(0, linea.find(","));

    // extra
    linea = linea.substr(linea.find(",") + 1, linea.length());
    string extra = linea.substr(0, linea.find(","));

    // precio
    linea = linea.substr(linea.find(",") + 1, linea.length());
    int precio = stoi(linea.substr(0, linea.find(",")));

    // Hacer una pizza temporal...
    Pizza pizzaTemp(id, pizza, tamanho, extra, precio);
    pizzas.addLast(pizzaTemp);
  }
  fin.close();
}

// Leyendo el documento de usuarios
void readUsers(string documento, LinkedList<string> &users,
               LinkedList<string> &pins) {
  ifstream fin;
  fin.open(documento);
  // Error en caso de no poder abrir el archivo o no encontrarlo
  if (fin.fail()) { // O(n)
    cout << "ERROR: Failed to open file ";
    throw -1;
  }
  // Variables en las que se va a almacenar la info.
  // user,password
  string linea;
  //getline(fin, linea);
  
  while (getline(fin, linea)) { // O(n)
    // Username
    
    linea = linea.substr(0, linea.length());
    string user = linea.substr(0, linea.find(","));
    users.addLast(user);

    // Password

    linea = linea.substr(linea.find(",") + 1, linea.length());
    string pin = linea.substr(0, linea.find(","));
    pins.addLast(pin);

  }
  fin.close();
};
string login(string documento, LinkedList<string> &users,
             LinkedList<string> &pins) {
  string usuario, password;
  bool logged = false;
  while (!logged) {
    cout << "Ingresa tu usuario y contraseña" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    int userIndex = users.index(usuario);
    cout<<"Username index: "<<userIndex<<endl;
    cout << "Password: ";
    cin >> password;

    int pwordIndex = pins.index(password);
    cout<<"Pword index: "<<pwordIndex<<endl;
    
    if (users.index(usuario)>0) {
      if (pins.index(password)>0) {
        if (userIndex == pwordIndex) {
          cout << "Benvenuto! " << endl;
          logged = true;
        } else {
          cout << "Contraseña incorrecta. Per favore intente de nuevo. "
               << endl;
        }
      } else {
        cout << "Usuario "<<usuario<< ", por favor intente de nuevo. " << endl;
      }
    } else {
      cout << "Usuario"<<usuario<< ", por favor intente de nuevo. " << endl;
    }
  }
  return usuario;
};

/* O(n^2) */
void makeHash(LinkedList<Pizza> &pizzas, Hashtable<int, Pizza> &inventario,
              string archivo) {
  for (int i = 0; i < pizzas.size(); i++) { // O(n)
    Pizza pizzaTemp = pizzas.get(i);        // O(n)
    int id = pizzaTemp.getID();
    inventario.put(id, pizzaTemp);
  }
}
void printInventory(Hashtable<int, Pizza> &inventario) {
  LinkedList<int> keys = inventario.keys(); // O(n^4)
  int identifier;
  for (int i = 0; i < keys.size(); i++) { // O(n)
    identifier = keys.get(i);             // O(n)
    cout << inventario.get(identifier);   // O(n)
    cout << endl;
  }
}

void makePedido(Carrito<Pizza> &carrito, Hashtable<int, Pizza> &inventario,
                int id) {
  Pizza pizzaSelect = inventario.get(id);
  carrito.addProducto(pizzaSelect);
  cout << "Su pedido es: " << pizzaSelect << endl;
}

void pausar() {
  string pause;
  cout << " <...> Ingrese cualquier valor para continuar. ";
  cin >> pause;
}
void makeTicket(Carrito<Pizza> &carrito, string username) {
  int total = carrito.pagar(username);
  string filename = username + '_' + to_string(time(0)) + ".txt";
  ofstream ticket(filename);

  ticket << "<<<<<<<<<<<<<<<< PIZZERIA TRICOLORE >>>>>>>>>>>>>>>>>\n";
  ticket << "~ - ~ - ~ - ~ - ~ - Grazie Mille! - ~ - ~ - ~ - ~ - ~\n";
  ticket<<"-----------------------------------------------------"<< "\n";
  ticket<<">> Usuario: "<<username<<endl;
  time_t now = time(0);
  char *dt = ctime(&now);
  ticket << "Date: " << dt;
  ticket<<"-----------------------------------------------------"<< "\n";
  LinkedList<Pizza> pedidos = carrito.getProducts();
  for (int i = 0; i < pedidos.size(); i++) {
    ticket << pedidos.get(i) << "\n";
  }
  ticket<<"-----------------------------------------------------"<< "\n";
  ticket << "Total: $" << total;
  ticket.close();
}

int main(int argc, char **argv) {

  // Default value of string archivo = "pizzaDB.csv"
  string archivo = _ARCHIVO_;
  string logUsers = _USERS_;

  if (argc == 2) {
    archivo = argv[1];
  }
  cout << "------------------------------------------------------------------"
       << endl;
  cout << " - - Ciao e Benvenuti nella sua Pizzeria TRICOLORE - -" << endl;
  cout << "------------------------------------------------------------------"
       << endl;
  LinkedList<string> users;
  LinkedList<string> pins;
  readUsers(logUsers, users, pins);

  string usuario;
  usuario = login(logUsers, users, pins);

  // Lista base de pizzas
  LinkedList<Pizza> pizzas;
  makeList(pizzas, archivo);
  // Hashtable base de inventario
  Hashtable<int, Pizza> hashT(pizzas.size());

  Carrito<Pizza> compras;
  pausar();
  cout << endl << "- - - IL NOSTRO MENÙ - - -" << endl;
  makeHash(pizzas, hashT, archivo);

  int opcion = 0;
  while (opcion != -1) {
    printInventory(hashT);
    cout << "^^^ Questo é il nostro menù ^^^" << endl;
    cout << "<?> Ingrese ID de la pizza a ordenar" << endl;
    cin >> opcion;
    if (opcion == -1) {
      break;
    }
    compras.addProducto(hashT.get(opcion));
    pausar();
  }

  makeTicket(compras, usuario);
  cout << "------------------------------------------------------------------"
       << endl;
  cout << " - - Grazie mille per aver utilizzato i nostri servizi :) - -"
       << endl;
  cout << "------------------------------------------------------------------"
       << endl;
}