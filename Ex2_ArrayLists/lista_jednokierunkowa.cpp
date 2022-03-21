//* Autor: Kacper Piątkowski

#include <iostream>
#include <algorithm>
#include <exception>
#include <limits>
#include <utility>

#define N 256 //Wielkosc tablicy
#define END -1  //Oznaczenie na koniec listy
#define EMPTY -2    //Oznaczenie na puste miejsce

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
            std::cout << "Wprowadz liczbe miedzy [1;9]\n";
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

//* Implementacja listy jednokierunkowej kursorowo
template <typename T>
class List {

    private:
        std::pair<T, int> array[N]; /** @param array[].first element @param array[].second index kolejnego elementu na liscie */
        int empty_index = 0; // pierwsze dostepne (wolne) pole w tablicy na ktorym mozna wpisac element
        int size = 0;   // wielkosc listy 
        int head_index = 0; // index na ktorym znajduje sie glowa listy
        int last = 0;   //index ostatniego elementu na liscie

    public:

    //!CONSTRUCTORS
    List() { array_init(); }    //konstruktor domyslny

    List(T elements[], int size)    //tworzenie listy za pomocą tablicy elementów
    {
        array_init();       
        for(int i = 0; i<size; i++)
            add(elements[i]);
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
            next = array[next].second;
        return array[next].first;
    }

    //znajduje pierwsze wolne miejsce w tablicy i zmienia empty_index na to wolne miejsce
    void search_first_empty()
    {
        for(int i = 0; i<N; i++) {
            if(array[i].second == EMPTY){
                this->empty_index = i;
                break;
            }
        }
    }

    //inicjalizuje wszystkie [].second indeksy w tablicy na -2 (wolne miejsce)
    void array_init()
    {
        for(int i = 0; i<N; i++)
            array[i].second = EMPTY;
    }

    /**
     ** Dodaj element do listy
     * @param element element ktory chcemy dodac do listy
     * @param index miejsce w ktoro chcemy wstawic element (jesli nie zostanie podany domyslnie bedzie to ostatni element listy) 
    */
    void add(T element ,int index = -1)
    {
        if(this->is_empty()) { //? jesli nasza lista jest pusta to dodajac element staje sie naszym headem
            head_index = 0; //ustawiamy index heada na poczatek tablicy
            last = 0;
            array[head_index].first = element;  //przypisujemy podana w argumencie wartosc do tablicy o indeksie nowego heada
            array[head_index].second = END;     //przypisujemy znak konca listy
            size++;
            empty_index = 1;
            return;
        }
        search_first_empty();
        if(index == -1 || index == size) { //? chcemy wstawic na koniec listy, jest to takze defaultowa opcja jesli wywolamy funkcje bez 2 argumentu
            array[last].second = empty_index;   //* w tym momencie array[next] wskazuje na ostatni element w liscie, przepinamy index tak aby wkazywal na nowo powstaly element
            array[empty_index].first = element; //* array[empty_index] wskazujenp na nowy element
            array[empty_index].second = END;
            last = empty_index;
            size++;
        } 
        else if(index == 0) { //? chcemy wstawic na poczatek listy, wiec musimy rowniez przepiac head_index tak aby dobrze wskazywal na glowe listy
            array[empty_index].first = element; 
            array[empty_index].second = head_index;
            head_index = empty_index;
            size++;
        } 
        else {    //? chcemy wstawic w dowolna pozycje
            int next = head_index;  
            for(int i = 0; i < index-1; i++)
                next = array[next].second;  //przechodzimy przez liste do elementu po ktorym chcemy dodac (musimy przepiac tak aby poprzednik wkazywal na nowy element, a element na nastepnika poprzednika)
            int temp = array[next].second;  //* przetrzymujemy na co wskazuje nasz poprzednik
            array[next].second = empty_index; //* poprzednika przepinamy na nowo dodany element
            array[empty_index].first = element; //* przypisujemy wartosc nowo dodanego elementu
            array[empty_index].second = temp;   //* przypisujemy to na co wskazywal poprzednik
            size++;
        }        
    }

    /**
     ** Usun element z listy o podanym indeksie
     * @param index indeks elementu ktory usuwamy (jesli nie zostanie podany domyslnie bedzie to ostatni element listy)
    */
    void remove_index(int index = -1)
    {
        if(this->is_empty())
            return;

        if(this->size == 1) {
            array[head_index].second = EMPTY;
            size--;
        } 
        else if(index == -1 || index == size-1) {  //? defaultową opcją jest usuniecie ostatniego elementu w liscie
            int next = head_index;
            for(int i = 0; i<size-2; i++)
                next = array[next].second;  //* przechodzimy do elementu ktory znajduje sie 2 indeksy przed ostatnim
            array[array[next].second].second = EMPTY;   //* ustawiamy tak aby ostatni element byl pusty
            array[next].second = END;   //* nastepnik ustawiamy aby pokazywal na koniec
            this->last = next;
            size--;
        } 
        else if(index == 0) {     //? usuwamy pierwszy element w liscie (heada)
            int temp = head_index;      //* w zmiennej tymczasowej przetrzymujemy indeks heada
            head_index = array[head_index].second;  //* przepinamy glowe na nastepnika
            array[temp].second = EMPTY; //* ustawiamy na wczesniejszym headzie puste pole
            size--;
        } 
        else {    //? usuwamy dowolny element
            int next = head_index;  
            for(int i = 0; i<index-1; i++)  //* przechodzimy do elementu przed tym ktory chcemy usunac
                next = array[next].second;
            int temp = array[next].second;  //* musimy przetrzymac indeks elementu ktory chcemy usunac zeby potem sie do niego dostac
            array[next].second = array[array[next].second].second;  //* przepinamy poprzednika elementu ktory chcemy usunac tak aby wskazywal na nastepnika elementu usuwanego
            array[temp].second = EMPTY; //* ustawiamy pole usunietego elementu na puste
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
     * @returns indeks elementu w liscie, -1 jesli element nie znajduje sie na liscie 
    */ 
    int contains(T element)
    {
        int next = head_index;
        for(int i = 0; i<this->size; i++) { //* bedziemy przechodzic przez cala liste
            if(array[next].first == element)    //* jesli dany element tablicy jest rowny szukanemu zwracamy index na liscie
                return i;
            next = array[next].second;
        }
        return -1;  //* jesli nie znajdziemy elementu zwracamy -1
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
            std::cout << "\033[1;32m" << array[index].first << "\033[0m";  //? tak jak wyzej tylko zielony
            if((index = array[index].second) != END)    //* jesli kolejny element bylby ostatnim nie wypiszemy ->
                std::cout << "\033[31m->\033[0m";
        }
        std::cout << std::endl;
    }

    //* Wyczysc liste
    void clear() 
    {
        //? usuwanie elementu dekrementuje wielkosc listy, wiec w pewnym momencie bedzie while(0) co skonczy nam dzialanie funckji
        while(this->size) 
            this->remove_index(0);
    }

    //* Posortuj liste
    void sort()
    {
        T *sorted = new T[this->size]; //* Tworze nowa tablice w ktorej bede przechowywal wszystkie elementy z listy
        int next = head_index;
        for(int i = 0; i<this->size; i++){
            sorted[i] = array[next].first;  //* wypelniam tablice elementami z listy
            next = array[next].second;
        }
        std::sort(sorted, sorted+this->size); //* Sortuje tablice z elementami
        int array_size = this->size;
        this->clear();  //* czyszcze cala liste, po to by dodac ja w posortowanej kolejnosci
        for(int i = 0; i<array_size; i++) {
            this->add(sorted[i]);   //* dodaje po kolei elementy posortowane na koniec listy
        }
        delete [] sorted;
    }

    void debug()
    {
        std::cout << "\033[31mLAST = " << this->last << "\nHEAD = " << this->head_index << "\nSIZE = " << this->size << "\033[0m" << std::endl;
        for(int i = 0; i<16; i++) {
            std::cout << "\033[31m["<< i << "] \033[0m";
            std::cout << this->array[i].first << " " << this->array[i].second << std::endl;
        }
    }
};

int main()
{
    int liczby[12] = {5,9,8,10,16,12,10,5,13,22,51,65};
    List<int> lista(liczby, 12);
    int element;

    // std::string imiona[5] = {"Kacper", "Jarek", "Jakub", "Tymoteusz", "Zuzia"};
    // List<std::string> lista(imiona, 5);
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