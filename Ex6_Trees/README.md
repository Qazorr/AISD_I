# **Autor: Kacper Piątkowski** #

## Zawartosc i opis ##

#
Katalog zawiera:

* 2 pliki **hpp** - `BST.hpp` i `AVL.hpp` w ktorej znajduje sie implementacja drzewa BST oraz AVL
* 2 pliki **cpp** - `BST.cpp` i `AVL.cpp` w ktorej znajduje sie prezentacja drzew
#

## Funkcje w drzewach ##

#
### **Pola klasy**
#

**BST i AVL:**
* `root` - wskaznik na korzen drzewa

### **Metody prywatne BST i AVL**

#


* `void insert_f(Node<T> *node, int data)` - dodaje nowy Node z wartoscia **data** rekurencyjnie, rozpoczynajac od **node**
* `Node<T>* find_f(Node<T> *node, int data)` - znajduje Node z wartoscia **data** rekurencyjnie, rozpoczynajac od **node** 
* `Node<T>* remove_f(Node<T>* node, int data)` - usuwa Node z wartoscia **data** rekurencyjnie, rozpoczynajac od **node**
* `void traverse_inorder(Node<T>* node)` - przechodzi po drzewie inorder 
* `void traverse_preorder(Node<T>* node)` - przechodzi po drzewie preorder
* `void traverse_postorder(Node<T>* node)` - przechodzi po drzewie postorder
* `Node<T>* smallest(Node<T>* node)` - znajduje najmniejszy Node rozpoczynajac od **node**
* `Node<T>* largest(Node<T>* node)` - znajduje najwiekszy Node rozpoczynajac od **node**

#

### **Metody prywatne AVL**

* `inline int get_height(Node<T> *node)` - zwraca wysokosc poddrzewa o korzeniu **node**
* `inline int get_balance_factor(Node<T> *node)` - zwraca roznice pomiedzy wysokoscia lewego a prawego poddrzewa Node'a **node**
* `void update(Node<T>* node)` - updateuje wysokosc poddrzewa o korzeniu **node**
* `Node<T>* balance(Node<T>* node)` - funkcja wykonuje balans drzewa w oparciu o rotacje:
    * `Node<T>* single_left_rotation(Node<T>* &parent_node)`
    * `Node<T>* single_right_rotation(Node<T>* &parent_node`

#

### **Metody publiczne BST I AVL**
#

* `T min()` - zwraca najmniejsza wartosc w drzewie
* `T max()` - zwraca najwieksza wartosc w drzewie
* `inline void display_inorder()` - wyswietla drzewo w kolejnosci inorder
* `inline void display_preorder()` - wyswietla drzewo w kolejnosci preorder
* `inline void display_postorder()` - wyswietla drzewo w kolejnosci postorder
* `inline void insert(T data)` - dodaje nowy Node do drzewa o wartosci **data** (w przypadku gdy Node o danej wartosci istnieje, nic sie nie dzieje)
* `inline void remove(T data)` - usuwa Node z drzewa o wartosci **data** (w przypadku gdy nie znajdziemy wartosci **data** w drzewie nic sie nie dzieje)
* `inline Node<T>* find(T data)` - wyszukuje Node o wartosci **data** w drzewie i go zwraca (w przypadku gdy taki Node nie istnieje zwracany jest **nullptr**)

#
## Jak uruchomic programy:

* Standardowa kompilacja:
        `g++ BST.cpp` albo `g++ AVL.cpp`
* Wywołanie:
        `./a.out`

* Po wywołaniu w terminalu powinno wyświetlić się menu, któro służy użytkownikowi do operacji na drzewach
#