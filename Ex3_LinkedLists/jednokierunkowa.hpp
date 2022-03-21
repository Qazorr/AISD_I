#ifndef JEDNOKIERUNKOWA_H
#define JENDOKIERUNKOWA_H

#include <iostream>
#include <iterator>

template <typename T>
struct Node {
    public:
        T mData;    //wartosc Node'a
        Node *next = nullptr;   //wskaznik na następnika

        Node() = default;   //konstruktor domyslny
        Node(T x) : mData(x), next(nullptr) {}  //konstruktor inicjalizujacy wartosc Node'a
};

template <typename T>
class List {
    //members
    private:
        int size = 0;
        Node<T> *head, *tail;

    //private methods
    private:
        /**
         ** Dodaj pierwszy element (tzn jesli size == 0)
         *@param data wartosc elementu ktory wstawiamy
        */
        void push_first(T data)
        {
            Node<T> *elmt = new Node<T>(data);
            this->head = elmt;
            this->tail = elmt;
            elmt->next = nullptr;
            size++;
        }
        
        //* Usun ostatni element (tzn, jesli size == 1, wywolana zostanie ta funkcja)
        void pop_single()
        {
            Node<T> *tmp = head;
            head = nullptr;
            tail = nullptr;
            delete tmp;
            size--;
        }

    //public methods
    public:
        //! Iterator
        struct Iterator{
            using iterator_category = std::forward_iterator_tag;
            using value_type = Node<T>;
            using pointer = Node<T>*;
            using reference = T&;

            //constructor
            Iterator(pointer ptr) : m_ptr(ptr) {}

            reference operator*() const { return m_ptr->mData; }
            pointer operator->() { return m_ptr; }

            //incrementations
            Iterator& operator++() 
            {
                m_ptr = m_ptr->next;
                return *this;
            }
            Iterator& operator++(int) 
            { 
                ++(*this);
                return *this; 
            }

            friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

            inline pointer get_ptr() { return m_ptr; }

            private:
                pointer m_ptr;
        };

        Iterator begin() { return Iterator(head); }
        Iterator end() { return Iterator(nullptr); }

        //! Konstruktory
        List() : head(nullptr), tail(nullptr), size(0) {}
        List(T array[], int arr_size)
        {
            for(int i = 0; i<arr_size; i++)
                push_back(array[i]);
        }

        //!Destruktor
        ~List() { clear(); }

        inline int get_size() { return this->size; } 
        inline bool is_empty() { return this->size == 0; }
        inline const T& front() { return head->mData; }
        inline const T& back() { return tail->mData; }
        
        /**
         ** Zwroc wartosc elementu na danej pozycji 
         * @param pos pozycja elementu ktory chcemy sprawdzic
         * @returns wartosc elementu na pozycji pos 
        */
        const T& on_index(int pos)
        {
            Node<T> *curr = head;
            for(int i = 0; i<pos; i++)
                curr = curr->next;
            return curr->mData;
        }

        /**
         ** Dodaj element na poczatek listy
         * @param data wartosc elementu ktory chcemy dodac  
        */
        void push_front(T data)
        {
            if(is_empty())
                this->push_first(data);
            else {
                Node<T> *elmt = new Node<T>(data);
                elmt->next = head;
                this->head = elmt;
                size++;
            }
        }

        /**
         ** Dodaj element na koniec listy 
         * @param data wartosc elementu ktory chcemy dodac
        */
        void push_back(T data)
        {
            if(is_empty()) 
                this->push_first(data);
            else {
                Node<T> *elmt = new Node<T>(data);
                elmt->mData = data;
                this->tail->next = elmt;
                this->tail = elmt;
                elmt->next = nullptr;
                size++;
            }
        }

        /**
         ** Dodaj element na wybrana pozycje (liczoną od 0) 
         * @param data wartosc elementu ktory chcemy dodac
         * @param pos pozycja na ktora chcemy dodac element
        */ 
        void insert(T data, int pos)
        {
            if(pos < 0 || pos > this->size+1) {}
            else if(is_empty())
                push_first(data);
            else if(pos == 0)
                push_front(data);
            else if(pos == this->size)
                push_back(data);
            else {
                Node<T> *curr = head;
                for(int i = 1; i<pos; i++) {
                    curr = curr->next;                
                }
                Node<T> *tmp = new Node<T>(data);
                tmp->next = curr->next;
                curr->next = tmp;
                size++;          
            }
        }

        /**
         ** Dodaj element za wybranym elementem w liscie 
         * @param data wartosc elementu ktory chcemy dodac
         * @param it iterator elementu za którym chcemy dodac element
        */
        void insert(T data, Iterator it)
        {   
            if(it == end()) {} 
            else if(is_empty())
                push_first(data);
            else if(it == begin()) 
                push_front(data);
            else if(it == Iterator(tail)) 
                push_back(data);
            else {
                Node<T>* tmp = it->next;
                Node<T>* elmt = new Node<T>(data);
                elmt->next = tmp;
                it->next = elmt;
                size++;
            }
        }

        //* Usun element z poczatku listy
        void pop_front()
        {
            if(is_empty()) {}
            else if(size == 1)
                pop_single();
            else {
                Node<T> *temp = head;
                head = head->next;
                delete temp;
                size--;
            }
        }

        //* Usun element na koncu listy
        void pop_back()
        {
            if(is_empty()) {}
            else if(size == 1)
                pop_single();
            else {
                Node<T> *current_elmt = head;
                while(current_elmt->next->next)
                    current_elmt = current_elmt->next;
                Node<T> *tmp = tail;
                delete tmp;
                tail = current_elmt;
                current_elmt->next = nullptr;
                size--;
            }
        }

        /**
         ** Usun element na wybranej pozycji (liczoną od 0) 
         * @param pos pozycja elementu ktory chcemy usunac
        */ 
        void erase(int pos)
        {
            if(is_empty()) {}
            else if(size == 1)
                pop_single();
            else if(pos == 0)
                pop_front();
            else if(pos == size-1)
                pop_back();
            else {
                Node<T> *curr = head;
                for(int i = 1; i<pos; i++)
                    curr = curr->next;
                    
                Node<T> *tmp = curr->next;
                curr->next = tmp->next;
                delete tmp;
                size--;
            }
        }

        /**
         ** Usun wybrany element 
         * @param it iterator elementu ktory chcemy usunac
        */         
        void erase(Iterator it)
        {
            if(is_empty() || it == end()) {}
            else if(it == Iterator(tail))
                pop_back();
            else if(it == begin())
                pop_front();
            else {
                Iterator curr = begin();
                Iterator prev = begin();
                while(curr->next) {
                    prev = curr;
                    if(++curr == it)
                        break;
                }

                Node<T> *tmp = prev->next; //3
                prev->next = prev->next->next;
                delete tmp;
                size--;
            }
        }

        /**
         ** Sprawdz czy wartosc znajduje sie na liscie 
         * @param data wartosc którą sprawdzamy
         * @returns true jesli znajduje sie na liscie, w przeciwnym razie false
        */
        bool contains(const T& data)
        {
            Node<T> *curr = head;
            while(curr){
                if(curr->mData == data)
                    return true;
                curr = curr->next;
            }
            return false;
        }

        /**
         ** Znajdz element o wybranej wartosci w liscie 
         * @param data wartosc ktorą szukamy
         * @returns iterator do elementu znalezionego (jesli nie zostanie znaleziony zostanie zwrocony nullptr) 
        */ 
        Iterator find(const T& data)
        {
            auto it = this->begin();
            for( ; it != this->end(); ++it) {
                if(it->mData == data)
                    return Iterator(it);
            }
            return Iterator(it);
        }

        //* Posortuj liste
        void sort()
        {
            if(is_empty()) {}
            else {
                Iterator curr = this->begin(), index = Iterator(curr->next), end = this->end();
                while(curr != end) {
                    index = Iterator(curr->next);
                    while(index != end) {
                        if(curr->mData > index->mData)
                            std::swap(curr->mData, index->mData);
                        ++index;
                    }
                    ++curr;
                }
            }
        }

        //* Wyczysc liste
        void clear()
        {
            while(!is_empty())
                pop_front();
        }

        //* Wypisz liste
        void print()
        {
            if(is_empty()){
                std::cout << "\033[31mLista jest pusta!\033[0m\n";
                return;
            }
            for(auto it = this->begin(), end = this->end(); it != end; ++it) {
                std::cout << "\033[1;32m" << it->mData << "\033[0m";
                if(it->next != nullptr)
                    std::cout << "\033[31m->\033[0m";
            }
            std::cout << std::endl;
        }
};

#endif