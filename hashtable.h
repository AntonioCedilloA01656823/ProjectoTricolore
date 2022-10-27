template <typename K, typename T> /* K key, T value*/
class HashPair {
public:
  K key;
  T value;
  HashPair(K key, T value) {
    this->key = key;
    this->value = value;
  }
  HashPair() {}
};
template <typename K, typename T> class Hashtable {
private:
  int size;
  LinkedList<HashPair<K, T> *> *tabla;
  /* O(i) */
  int fh(K key) const {
    int position = (key-1) % size;

    return position;
  }

public:
  /* O(n) */
  Hashtable(int size = 50) {
    this->size = size;
    tabla = new LinkedList<HashPair<K, T> *>[size];
    for (int i = 0; i < size; i++) {
      tabla[i] = LinkedList<HashPair<K, T> *>();
    }
  }

  /* O(n^2) */
  bool put(K key, T value) {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> lista = tabla[posicion];
    int indice = -1;
    for (int i = 0; i < lista.size(); i++) { // O(n)
      if (lista.get(i)->key == key) {        // O(n)
        indice = i;
      }
    }
    if (indice >= 0) { // Actualiza
      lista.get(indice)->value = value;
    } else { // Agrega nuevo
      tabla[posicion].addLast(new HashPair<K, T>(key, value));
    }
    return (indice >= 0) ? 0 : 1; // Si lo encuentra es 0, si no, es 1
  }

  /* O(n^2)*/
  T get(K key) const {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> lista = tabla[posicion];
    int indice = -1;
    for (int i = 0; i < lista.size(); i++) { // O(n)
      if (lista.get(i)->key == key) {        // O(n)
        indice = i;
      }
    }
    if (indice < 0) {
      throw -1;
    }
    return lista.get(indice)->value;
  }
  /* O(n^2) */
  bool contains(K key) const {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> lista = tabla[posicion];
    int indice = -1;
    for (int i = 0; i < lista.size(); i++) { // O(n)
      if (lista.get(i)->key == key) {        // O(n)
        indice = i;
      }
    }

    return (indice < 0) ? 0 : 1;
  }
  /* O(n^2)*/
  void print() {
    for (int i = 0; i < size; i++) {              // O(n)
      for (int j = 0; j < tabla[i].size(); j++) { // O(n)
        cout << "i:" << i << " k: " << tabla[i].get(j)->key << " >> " << endl;
        tabla[i].get(j)->value.print();
        cout << endl; // O(n)
      }
    }
  }
  /* O (n)*/
  T get_or_default(K key, T default_value = T()) const {
    if (contains(key)) {
      return get(key); // O(n)
    } else {
      return default_value;
    }
  }
  bool is_empty() { return tabla->is_empty(); }
  /* O(n^4) */
  LinkedList<K> keys() const {
    LinkedList<K> keysList;
    for (int i = 0; i < size; i++) {              // O(n)
      for (int j = 0; j < tabla[i].size(); j++) { // O(n)
        keysList.addLast(tabla[i].get(j)->key);   // O(n^2)
      }
    }
    return keysList;
  }

  bool remove(K key) {
    if (contains(key)) {
      int posicion = fh(key);

      LinkedList<HashPair<K, T> *> tempList;
      for (int i = 0; i < tabla[posicion].size(); i++) {
        if (tabla[posicion].get(i)->key != key) {
          tempList.addLast(tabla[posicion].get(i));
        }
      }
      tabla[posicion] = tempList;
      return true;
    } else {
      return false;
    }
  }
  int hashSize() {
    int nElements = 0;
    for (int i = 0; i < size; i++) {
      nElements += tabla[i].size();
    }
    return nElements;
  }
};