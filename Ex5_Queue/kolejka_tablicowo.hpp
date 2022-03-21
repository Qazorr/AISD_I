#include <iostream>

#define BASE_SIZE 8

template <typename T>
class Queue{
    private:
        T *array = nullptr;
        unsigned mSize = 0;
        unsigned arraySize = BASE_SIZE;
        unsigned head = 0;

        void resize()
        {
            arraySize *= 2;
            T *new_array = new T[arraySize];
            for(int i = 0; i<mSize; i++, head++)
                new_array[i] = array[(head+i)%(arraySize/2)];
            head = 0;
            delete [] array;
            array = new_array;
        }
  
    public:

        inline unsigned size() { return mSize; }
        inline bool is_empty() { return mSize == 0; }

        Queue() { array = new T[arraySize]; }   
        ~Queue() { delete []array; }

        void push(T data)
        {
            if(mSize == arraySize)
                resize();
            array[(head+mSize) % arraySize] = data;
            mSize++;              
        }

        T pop()
        {
            if(is_empty())
                throw std::out_of_range("\033[1;31mQUEUE IS EMPTY, COULDN'T POP\033[0m");
            else {
                int retvalue = array[head % arraySize];
                head++;
                mSize--;
                return retvalue;
            }
        }

        const T& front() 
        { 
            if(is_empty())
                throw std::out_of_range("\033[1;31mQUEUE IS EMPTY, COULDN'T ACCESS THE FRONT ELEMENT\033[0m");
            return array[head % arraySize];
        }

        void print()
        {
            if(is_empty())
                std::cout << "\033[31mQUEUE IS EMPTY\033[0m";
            else {
                for(int i = 0; i<mSize; i++) {
                    if(i == 0)
                        std::cout << "\033[31m" << array[(head+i) % arraySize] << "\033[0m ";
                    else
                        std::cout << array[(head+i) % arraySize] << " ";
                }
            }
            std::cout << std::endl;
        }

        void clear()
        {
            if(is_empty()) {}
            else {
                while(mSize) 
                    pop(); 
            }
        }
};