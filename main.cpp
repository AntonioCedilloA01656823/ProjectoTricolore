/*
Integrantes:
Jonathan Josué Fuentes Ramírez A01661894
Alejandro Pozos Aguirre        A01656017
*/

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
    cout << pizzaTemp << endl;
  }
  fin.close();
}

// Leyendo el documento de usuarios
void login(string documento, string usuario, string password) {
  // O(1)
  LinkedList<string> users;
  LinkedList<string> pins;

  ifstream file(documento);     // O(1)
  string line;                  // O(1)
  char delimit = ',';           // O(1)
  while (getline(file, line)) { // O(n)
    stringstream stream(line);  // O(1)
    string user, pin;
    getline(stream, user, delimit);
    getline(stream, pin, delimit);

    users.addLast(user);
    pins.addLast(pin);
  }

  for (int i = 0; i < users.size(); i++) {
    for (int i = 0; i < pins.size(); i++) {
      string tempUser= users.get(i);
      string tempPin = pins.get(i);

      if(tempUser == usuario && tempPin == password){
        cout << "Bienvenido a Pizzeria Tricolore"<<endl;

      } else{
        string newUser;
        string newPin;
        
        cout << "Intentalo de nuevo.";
        cout << "Usuario:";
        cin >> newUser;
        cout<<endl;
        cout<<"Password:";
        cin>>newPin;
        cout<<endl;

        string logUsers = "usuarios.csv";
        login(logUsers,newUser,newPin);
        
        
      }
    }
  }
}

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

void makePedido(Carrito<Pizza> &carrito, Hashtable<int, Pizza> &inventario, int id) {
  Pizza pizzaSelect = inventario.get(id);
  carrito.addProducto(pizzaSelect);
  cout<<"Su pedido es: "<<pizzaSelect<<endl;
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

  cout << "Ingresa tu usuario y contraseña"<<endl;
  string usuario;
  string password;

  cout<<"Usuario: ";
  cin>>usuario;
  cout<<endl;
  cout<<"Password: ";
  cout<<endl;

  login

  // Lista base de pizzas
  LinkedList<Pizza> pizzas;
  makeList(pizzas, archivo);
  // Hashtable base de inventario
  Hashtable<int, Pizza> hashT(pizzas.size());

  cout << "- - - HASH TABLE - - -" << endl;
  cin >> start;
  cout << endl;
  makeHash(pizzas, hashT, archivo);
  printInventory(hashT);
  
  int opcion;
  while (opcion !=-1){
    cin>>opcion;
    if ()
  }
  cout << "------------------------------------------------------------------"
       << endl;
  cout << " - - Grazie mille per aver utilizzato i nostri servizi :) - -"
       << endl;
  cout << "------------------------------------------------------------------"
       << endl;
}