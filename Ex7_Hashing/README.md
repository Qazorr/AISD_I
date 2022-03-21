# **Autor: Kacper Piątkowski** #

## Zawartosc i opis ##

#
Katalog zawiera:

* plik **hpp** - `HashMap.hpp` w ktorym znajduje sie implementacja HashMapy opartej na hashowaniu otwartym
* plik **cpp** - `HashMap.cpp` w ktorym znajduje sie prezentacja HashMapy
#

## Funkcje w HashMapie ##

#
### **Pola klasy**
#

* `entries[]` - tablica Entries w ktorych przechowuje klucz i value
* `mSize` - wielkosc HashMapy

### **Metody prywatne**

#
### **Metody publiczne**
#

* `inline int size()` - zwraca wielkosc HashMapy
* `inline bool is_empty()` - czy HashMapa jest pusta
* `inline bool is_full()` - czy HashMapa jest pelna
* `V& operator[](const std::string& key)` - operator pozwalajacy na dostanie sie do elementu poprzez wywolanie `map[key]`
* `void insert(const Entry<std::string, V>& entry)` - dodanie nowego entry do HashMapy
* `void remove(const std::string& key)` - usuwa `entry` o kluczu `key` z HashMapy (jesli go nie ma to nic sie nie dzieje) 
* `bool find(const std::string& key)` - znajuje wartosc w HashMapie i zwraca czy zostala znaleziona czy nie
* `void display(bool full = false)` - wyswietla cala HashMape (ustawienie full = true skutkuje wypisaniem calej tablicy `entries[]`)

#
## Jak uruchomic programy:

* Standardowa kompilacja:
        `g++ HashMap.cpp`
* Wywołanie:
        `./a.out`

* Po wywołaniu w terminalu powinno wyświetlić się menu, któro służy użytkownikowi do operacji na HashMapie
#

## Porownanie:

Jesli w komorce tylko jedna zlozonsc znaczy to ze srednia i najgorsza jest taka sama.

| Srednia\Najgorsza
| :---: |

| Struktura\Zlozonosc     | Acess | Search |  Insertion | Deletion |
| :---: |   :-:    |    :-:   |    :-:    | :-: |
| tablica  | $\mathcal{O}(1)$ |$\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| stos |   $\mathcal{O}(n)$   |    $\mathcal{O}(n)$  |    $\mathcal{O}(1)$   | $\mathcal{O}(1)$|
| kolejka  | $\mathcal{O}(n)$   |    $\mathcal{O}(n)$  |    $\mathcal{O}(1)$   | $\mathcal{O}(1)$|
| lista jednokierunkowa |   $\mathcal{O}(n)$   |    $\mathcal{O}(n)$  |    $\mathcal{O}(1)$   | $\mathcal{O}(1)$|
| lista dwukierunkowa  | $\mathcal{O}(n)$   |    $\mathcal{O}(n)$  |    $\mathcal{O}(1)$   | $\mathcal{O}(1)$|
| drzewo BST  | $\mathcal{O}(\log n)$ \ $\mathcal{O}(n)$ |$\mathcal{O}(\log n)$ \ $\mathcal{O}(n)$ | $\mathcal{O}(\log n)$ \ $\mathcal{O}(n)$ | $\mathcal{O}(\log n)$ \ $\mathcal{O}(n)$ |
| drzewo AVL  | $\mathcal{O}(\log n)$ |$\mathcal{O}(\log n)$ | $\mathcal{O}(\log n)$ | $\mathcal{O}(\log n)$ |
| **hashmapa**  | $-$ |$\mathcal{O}(1)$ \ $\mathcal{O}(n)$| $\mathcal{O}(1)$ \ $\mathcal{O}(n)$ | $\mathcal{O}(1)$ \ $\mathcal{O}(n)$ |

#