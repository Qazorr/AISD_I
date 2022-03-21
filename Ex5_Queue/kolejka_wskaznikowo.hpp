#include <iostream>

template <typename T>
struct Node
{
    T mData;
    Node *previous = nullptr;

    Node(T data) : mData(data) {}
};

template <typename T>
class Queue {
    private:
        unsigned mSize;
        Node<T> *head, *last;

    public:

        inline unsigned size() { return mSize; }
        inline bool is_empty() { return mSize == 0; }

        Queue() : mSize(0), head(nullptr), last(nullptr) {}
        ~Queue() { clear(); }

        void push(T data)
        {
            Node<T> *el = new Node<T>(data);
            if(mSize == 0) {
                el->previous = nullptr;
                head = el;
                last = el;
                mSize++;
            }
            else {
                last->previous = el;
                last = last->previous;
                mSize++;
            }
        }


        T pop()
        {
            if(is_empty())
                throw std::out_of_range("\033[1;31mQUEUE IS EMPTY, COULDN'T POP\033[0m");
            else {
                T retValue = head->mData;
                Node<T> *tmp = head;
                head = head->previous;
                mSize--;
                delete tmp;
                return retValue;
            }
        }


        const T& front() 
        { 
            if(is_empty())
                throw std::out_of_range("\033[1;31mQUEUE IS EMPTY, COULDN'T ACCESS THE FRONT ELEMENT\033[0m");
            return head->mData;
        }

        const T& back() 
        { 
            if(is_empty())
                throw std::out_of_range("\033[1;31mQUEUE IS EMPTY, COULDN'T ACCESS THE BACK ELEMENT\033[0m");
            return last->mData;
        }

        void clear()
        {
            if(is_empty()) {}
            else {
                while(mSize) 
                    pop(); 
            }
        }

        void print()
        {
            if(is_empty())
                std::cout << "\033[31mQUEUE IS EMPTY\033[0m";
            else {
                Node<T> *tmp = head;
                for( ; tmp != nullptr; tmp = tmp->previous){
                    if(tmp == head)
                        std::cout << "\033[31m" << tmp->mData << "\033[0m ";
                    else
                        std::cout << tmp->mData << " ";
                }
            }
            std::cout << std::endl;
        }

};