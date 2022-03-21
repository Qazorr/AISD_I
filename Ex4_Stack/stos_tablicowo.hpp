#include <iostream>

#define BASE_SIZE 16

template <typename T>
class Stack{
    private:
        T *array;
        int mSize = 0;  //size of current stack
        int arrSize = BASE_SIZE;    //size of an array
    
        void resize()
        {
            arrSize *= 2;
            T *new_array = new T[arrSize];
            std::copy(array, array+mSize, new_array);
            delete [] array;
            array = new_array;
        }

    
    public:

        Stack() { array = new T[arrSize]; }
        ~Stack() { delete [] array; }

        inline int size() { return mSize; }
        inline bool is_empty() { return mSize == 0; }    

    
        void push(T data)
        {
            if(mSize == arrSize)
                resize();
            array[mSize++] = data;
        }

        T pop()
        {
            if(is_empty())
                throw std::out_of_range("\033[1;31mSTACK IS EMPTY, COULDN'T POP\033[0m");
            return array[--mSize];
        }

        const T& top()
        {
            if(is_empty())
                throw std::out_of_range("\033[1;31mSTACK IS EMPTY, COULDN'T ACCESS THE TOP ELEMENT\033[0m");
            return array[mSize-1];
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
                std::cout << "\033[32mSTACK:\033[0m ";
                for(int i = mSize-1; i>=0; i--) {
                    if(i == mSize-1)
                        std::cout << "\033[31m"<< array[i] << "\033[0m ";
                    else
                        std::cout << array[i] << " ";
                }
                std::cout << std::endl;
            }
        }    
};