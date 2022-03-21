#include <iostream>
#include <exception>

template <typename T>
struct Node
{
    T mData;
    Node *under = nullptr;

    Node(T data) : mData(data), under(nullptr) {}
};

template <typename T>
class Stack{
    private:
        int mSize = 0;
        Node<T> *head = nullptr;

    public:

        Stack() = default;
        ~Stack() { clear(); }

        inline bool is_empty() { return mSize == 0; }
        inline int size() { return mSize; }

        void push(T data)
        {
            Node<T> *tmp = head;
            Node<T> *elmt = new Node<T>(data);
            elmt->under = tmp;
            head = elmt;
            mSize++;
        }

        T pop()
        {
            if(is_empty())
                throw std::out_of_range("\033[1;31mSTACK IS EMPTY, COULDN'T POP\033[0m");
            Node<T> *tmp = head;
            T val = head->mData;
            head = head->under;
            delete tmp;
            mSize--;
            return val;
        }

        const T& top()
        {
            if(is_empty())
                throw std::out_of_range("\033[1;31mSTACK IS EMPTY, COULDN'T ACCESS THE TOP ELEMENT\033[0m");
            return head->mData;
        }

        void clear()
        {
            while(!is_empty())
                pop();
        }
    
        void print()
        {
            if(is_empty())
                std::cout << "\033[31mSTACK IS EMPTY\033[0m\n";
            else {
                Node<T> *curr = head;
                std::cout << "\033[32mSTACK:\033[0m ";
                for(int i = 0; i<mSize; i++) {
                    if(!i) {
                        std::cout << "\033[31m"<< curr->mData << "\033[0m ";
                        curr = curr->under;
                    } 
                    else {
                        std::cout << curr->mData << " ";
                        curr = curr->under;
                    }
                }
                std::cout << std::endl;
            }
        }
};