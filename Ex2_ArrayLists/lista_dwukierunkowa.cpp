//* Autor: Kacper Piątkowski

#include <iostream>
#include <algorithm>
#include <exception>
#include <limits>
#include <utility>

#define N 256 //Wielkosc tablicy
#define BEGIN -1    //oznaczenie poczatku listy
#define END -2  //oznaczenie konca listy
#define EMPTY -3    //oznaczenie pustego miejsca

/**
 ** Struktura ktora bedzie mi sluzyla do przetrzymywania '3' wymiarow  w tablicy
 * @param previous index poprzedniego elementu w tablicy
 * @param mData wartosc elementu
 * @param next index kolejnego elementu w tablicy
*/
template <typename T>
struct triple
{
    int previous = -3;
    T mData;   
    int next = -3;  
};

/**
 ** pobranie od uzytkownika opcji
 * @return numer wybranej opcji
*/
int get_option()
{
    int x = 0;
    while(true)
    {
        try
        {
            std::cin >> x;
            if(x < 1 || x > 10)
                throw std::out_of_range("Not an option");
            break;
        }
        catch(const std::exception& e)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wprowadz liczbe miedzy [1;8]\n";
        }
    }
    return x;
}

//* menu wyświetlające sie użytkownikowi na początku programu 
int menu()
{
    std::cin.exceptions(std::ios::failbit | std::ios::badbit);
    std::cout << std::endl << "\033[1;33m=================================================================";
    std::cout << std::endl << "1. Wyswietl liste" << std::endl;
    std::cout << "2. Dodaj element na koniec listy" << std::endl;
    std::cout << "3. Dodaj element na wybrane miejsce" << std::endl;
    std::cout << "4. Usun element o wybranym \033[1;3;32mindeksie\033[0m\033[1;33m z listy" << std::endl;
    std::cout << "5. Usun element o wybranej \033[1;3;32mwartosci\033[0m\033[1;33m z listy" << std::endl;
    std::cout << "6. Sprawdz czy wybrany element znajduje sie na liscie" << std::endl;
    std::cout << "7. Posortuj liste" << std::endl;
    std::cout << "8. Wyczysc liste" << std::endl;
    std::cout << "9. Wyjdz z programu." << std::endl;
    std::cout << "=================================================================";
    std::cout << std::endl << "Dokonaj wyboru: " << std::endl;
    int n;
    n = get_option();
    std::cout << "=================================================================\033[0m" << std::endl;
    return n;
}

//* Implementacja listy dwukierunkowej kursorowo
template<typename T>
class Lista_dwukierunkowa
{
    private:
        triple<T> array[N]; /** @param array[].previous index poprzedniego elementu @param array[].mData element @param array[].next index kolejnego elementu na liscie */
        int empty_index = 0; // pierwsze dostepne (wolne) pole w tablicy na ktorym mozna wpisac element
        int size = 0;   // wielkosc listy 
        int head_index = 0; // index na ktorym znajduje sie glowa listy
        int last = 0;   //index ostatniego elementu na liscie

    public:

    Lista_dwukierunkowa(T array[], int size)  //tworzenie listy za pomocą tablicy elementów
    {
        for(int i = 0; i<size; i++)
            this->add(array[i]);
    }

    //!GETTERS
    inline int get_size() { return this->size; }
    inline int get_empty_index() { return this->empty_index; }
    inline int get_head_index() { return this->head_index; }
    inline int get_last() { return this->last; }
    inline bool is_empty() { return (this->size == 0); }

    /**
     ** Zwroc wartosc elementu z listy o indeksie index
     * @param index indeks na liscie ktorego wartosc chcemy uzyskac 
     * @returns element o indeksie index 
    */
    T elem_on_index(int index)
    {
        int next = head_index;
        while(--index)
            next = array[next].next;
        return array[next].mData;
    }

    //znajduje pierwsze wolne miejsce w tablicy i zmienia empty_index na to wolne miejsce
    void search_first_empty()
    {
        for(int i = 0; i<N; i++) {
            if(array[i].next == EMPTY){
                this->empty_index = i;
                break;
            }
        }
    }

    /**
     ** Dodaj element do listy
     * @param element element ktory chcemy dodac do listy
     * @param index miejsce w ktoro chcemy wstawic element (jesli nie zostanie podany domyslnie bedzie to ostatni element listy) 
    */
    void add(T element, int index = -1)
    {
        if(this->is_empty()) {  //? dodajemy pierwszy element w liscie
            head_index = 0;
            last = 0;   //* staramy sie wypelniac tablice od poczaktu, wiec zaczynamy od indeksu 0
            array[0].previous = BEGIN;
            array[0].mData = element;
            array[0].next = END;
            size++;
            return;
        }
        search_first_empty();   //wyszukanie wolnego miejsca
        if(index == -1 || index == this->size) {    //? defaultowa opcja, dodawanie na koniec listy
            array[last].next = empty_index;     //* nasz ostatni element bedzie teraz wkazywal na nowo utworzony element
            array[empty_index].previous = last; //* nowy element jako poprzednika ma wczesniejszy ostatni element
            array[empty_index].mData = element;
            array[empty_index].next = END;  //* a nastepnik nowego elementu wskazuje na koniec listy
            last = empty_index; //* naszym ostatnim elementem w liscie bedzie nowo utworzony element
            size++;
        }
        else if(index == 0) {   //? dodanie nowego heada (pierwszego elementu)
            array[empty_index].previous = BEGIN;    //* nowy element bedzie poczatkiem listy
            array[empty_index].mData = element;        
            array[empty_index].next = head_index;   //* nastepnik nowego elementu wskazuje na element ktory wczesniej byl pierwszy na liscie
            array[head_index].previous = empty_index;   //* wczesniejszy pierwszy element jako poprzednika bedzie mial teraz nowy element
            head_index = empty_index;   
            size++;
        }
        else {  //? dodaje na podany index
            int next = head_index;
            for(int i = 0; i<index-1; i++)
                next = array[next].next;    //* po petli bedziemy znajdowac sie na elemencie przed ktorym mamy dodac nowy element
            int temp = array[next].next;    //* w temp przetrzymujemy na co wskazuje w/w element
            array[empty_index].previous = next;
            array[empty_index].mData = element;
            array[empty_index].next = temp; //* nastepnik nowego elementu to bedzie wczesniej przetrzymany nastepnik elementu po którym wstawilismy
            array[next].next = empty_index; //* przepinamy tak aby element po ktorym wstawilismy wskazywal na nowo powstaly element
            array[temp].previous = empty_index; //* element ktory znajduej sie po naszym nowym elemencie wskazuje na niego jako poprzednika
            size++;
        }
    }

    /**
     ** Usun element z listy
     * @param index indeks elementu ktory usuwamy (jesli nie zostanie podany domyslnie bedzie to ostatni element listy)
    */
    void remove_index(int index = -1)
    {
        if(this->is_empty())    //? jesli tablica jest pusta nic nie mozemy usunac
            return;
        
        if(this->size == 1) {
            array[head_index].next = EMPTY;
            size--;
        }
        else if(index == -1 || index == size-1) {  //? defaultowa opcja - usuwanie na koncu listy
            int previous = array[last].previous;    //* dostajemy sie do elementu przedostatniego
            array[last].previous = EMPTY;   //* ostatni element usuwamy
            array[last].next = EMPTY;   //* ostatni element usuwamy
            array[previous].next = END; //* przedostatni element staje sie ostatnim
            this->last = previous;
            size--;
        }
        else if(index == 0) {   //? usuwamy naszego heada
            int temp = array[head_index].next;  //* przechowujemy to na co wskazuje pierwszy element w liscie
            array[head_index].next = EMPTY; //* usuwamy pierwszy element
            array[temp].previous = BEGIN;   //* 2 element staje sie pierwszym, wiec wskazuje na poczatek
            head_index = temp;  //* temp (2 element) staje sie pierwszym
            size--;
        }
        else {  //? usuwamy dowolny element
            int curr = head_index;
            for(int i = 0; i<index-1; i++)
                curr = array[curr].next;  //* pod koniec dostep do elementu przed tym ktory chcemy usunac
            int next = array[curr].next;  //* dostep do srodkowego elementu
            int temp = array[next].next;  //* dostep do elementu ktory znajduje sie po tym ktory chcemy usunac
            array[temp].previous = curr;  //* element ktory jest po usunietym przepinamy tak aby jego poprzednikiem byl poprzednik usunietego
            array[next].previous = EMPTY; array[next].next = EMPTY; //* usuwam srodkowy element
            array[curr].next = temp; //* element przed usunietym przepinam tak aby jego nastepnikiem byl nastepnik usunietego
            size--;
        }
    }
    
    /**
     ** Usun element z listy o danej wartosci
     * @returns czy element zostal usuniety
    */
    bool remove_elem(T element)
    {
        int position;
        if((position = this->contains(element)) != -1){
            this->remove_index(position);
            return true;
        }
        return false;
    }

    /**
     ** Sprawdz czy element znajduje sie w liscie
     * @param element szukany element
     * @returns indeks elementu w *tablicy*, -1 jesli element nie znajduje sie na liscie 
    */ 
    int contains(T element)
    {
        int next = head_index;
        for(int i = 0; i<this->size; i++) {
            if(array[next].mData == element)
                return i;
            next = array[next].next;
        }
        return -1;
    }

    //* Wyswietlenie listy
    void print()
    {
        if(this->is_empty()) {
            std::cout << "\033[31mLista jest pusta!\033[0m\n"; //? '\033[31m' zmienia kolor tekstu na czerwony, '\033[0m' wraca do standardowego koloru
            return;
        }
        int index = head_index;
        std::cout << "\033[1;31mLISTA: \033[0m"; 
        while(index != END) {
            std::cout << "\033[1;32m" << array[index].mData << "\033[0m";  //? tak jak wyzej tylko zielony
            if((index = array[index].next) != END)  //* jesli kolejny element bylby ostatnim nie wypiszemy <->
                std::cout << "\033[31m<->\033[0m";
        }
        std::cout << std::endl;
    }

    //* Wyczysc liste
    void clear()
    {
        //? usuwanie elementu dekrementuje wielkosc listy, wiec w pewnym momencie bedzie while(0) co skonczy nam dzialanie funckji
        while(this->size)
            this->remove_index();
    }
    
    //* Posortuj liste
    void sort()
    {
        T *sorted = new T[this->size]; //* Tworze nowa tablice w ktorej bede przechowywal wszystkie elementy z listy
        int next = head_index;
        for(int i = 0; i<this->size; i++){
            sorted[i] = array[next].mData;
            next = array[next].next;
        }
        std::sort(sorted, sorted+this->size); //* Sortuje tablice z elementami
        int array_size = this->size;
        this->clear();  //* czyszcze cala liste, po to by dodac ja w posortowanej kolejnosci
        for(int i = 0; i<array_size; i++) {
            this->add(sorted[i]);
        }
        delete [] sorted;
    }

    //wyswietlenie tablicy oraz kluczowych zmiennych
    void debug()
    {
        std::cout << "\033[31mLAST = " << this->last << "\nHEAD = " << this->head_index << "\nSIZE = " << this->size << "\033[0m" << std::endl;
        for(int i = 0; i<16; i++) {
            std::cout << "\033[31m["<< i << "] \033[0m";
            std::cout << this->array[i].previous << " " << this->array[i].mData << " " << this->array[i].next << std::endl;
        }
    }
};


int main()
{
    int liczby[12] = {5,9,8,10,16,12,10,5,13,22,51,65};
    Lista_dwukierunkowa<int> lista(liczby, 12);
    int element;

    // std::string imiona[5] = {"Kacper", "Jarek", "Jakub", "Tymoteusz", "Zuzia"};
    // Lista_dwukierunkowa<std::string> lista(imiona, 5);
    // std::string element;
    
    int position;
    
    while(true)
    {
        switch(menu())
        {
            case 1:
                std::cout << std::endl;
                lista.print();
                
                break;
            case 2:
                std::cout << "\nPodaj element jaki chcesz dodac: ";
                std::cin >> element;
                lista.add(element);
                std::cout << "\033[32mElement '" << element <<  "' zostal dodany\033[0m\n";
                
                break;
            case 3:
                std::cout << "\nPodaj element jaki chcesz dodac: ";
                std::cin >> element;
                lista.print();
                std::cout << "\nPodaj miejsce na ktore chcesz dodac element z przedzialu [1:" << lista.get_size()+1 << "] : ";
                std::cin >> position;
                if(position >= 1 && position <= lista.get_size()+1){
                    lista.add(element, position-1);
                    std::cout << "\033[32mElement '" << element << "' zostal dodany\033[0m\n\n";
                    lista.print();
                }
                else
                    std::cout << "\033[31mZostala wybrana pozycja spoza zakresu listy. Element nie zostal dodany.\033[0m\n";
                
                break;
            case 4:
                if(!lista.is_empty()){
                    std::cout << std::endl;
                    lista.print();
                    std::cout << "\nPodaj miejsce elementu ktory chcesz usunac z przedzialu [1:" << lista.get_size() << "] : ";
                    std::cin >> position;
                    if(position >= 1 && position <= lista.get_size()+1) {
                        element = lista.elem_on_index(position);
                        lista.remove_index(position-1);
                        std::cout << "\033[32mElement o indeksie '" << position << "' i wartosci '" << element << "' zostal usniety\033[0m\n\n";
                        lista.print();
                    }
                    else{
                        std::cout << "\033[31mZostala wybrana pozycja spoza zakresu listy. Element nie zostal usuniety.\033[0m\n";
                    }
                }
                else
                    std::cout << "\n\033[1;31mLista jest pusta, wiec element nie zostal usuniety.\033[0m\n";
                
                break;
            case 5:
                std::cout << std::endl;
                if(lista.is_empty()){
                    lista.print();
                    break;
                }
                lista.print();
                std::cout << "Jaki element chcesz usunac? : ";
                std::cin >> element;
                if(lista.remove_elem(element)) {
                    std::cout << "\033[1;32mElement '" << element << "' zostal usuniety\033[0m\n";
                    lista.print();
                }
                else
                    std::cout << "\033[1;31mElement nie znajduje sie na liscie, więc nie zostal usuniety.\033[0m\n";
                
                break;
            case 6:
                    if(lista.is_empty()) {
                        std::cout << std::endl;
                        lista.print();
                        break;
                    }
                    std::cout << "\nWpisz element ktory chcesz sprawdzic czy znajduje sie na liscie: ";
                    std::cin >> element;
                    if(lista.contains(element) != -1)
                        std::cout << "\n\033[1;32mElement '"<< element << "' znajduje sie na liscie\033[0m\n";
                    else
                        std::cout << "\n\033[1;31mElement '"<< element << "' nie znajduje sie na liscie\033[0m\n";
                
                break;
            case 7:
                if(!lista.is_empty()){
                    std::cout << "\nPrzed sortowaniem:\n";   
                    lista.print();
                    lista.sort();
                    std::cout << "Po sortowaniu:\n";
                    lista.print();
                }
                else{
                    std::cout << std::endl;
                    lista.print();
                }
                
                break;
            case 8:
                std::cout << std::endl;
                lista.print();
                if(lista.is_empty())
                    break;
                std::cout << "\n\033[1;31mCzyszczenie listy...\033[0m\n\n";
                lista.clear();
                lista.print();
                break;
            case 9:
                exit(EXIT_SUCCESS);
                
            case 10:
                lista.debug();
                break;
            default:
                break;
        }
    }
}