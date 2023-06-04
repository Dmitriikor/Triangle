﻿#include <iostream>

template<typename T>
class Array 
{
public:
    Array(int size) : size(size)
    {
        arr = reinterpret_cast<T*>(malloc(size * sizeof(T)));
        
    }

    ~Array()
    {
        free(arr);
    }

    bool operator==(const Array& other) const
    {
        return arr == other.arr && size == other.size && i == other.i;
    }

    Array() = default;

    Array(T* arr, int size) : arr(arr), size(size)
    {
    }

    void add_to_Array(const T& value)
    {
        if (i >= size)
        {
            //std::cout << "\n RISE \n";
            rise();
        }

        new(arr+i) T();
        arr[i] = value;
        ++i;    
    }

    void remove_from_Array(int index)
    {
        //if (index < 0 || index >= i)
        //{
        //    std::cout << "Invalid index!" << std::endl;
        //    return;
        //}

        //for (int j = index; j < i - 1; j++)
        //{
        //    arr[j] = arr[j + 1];
        //}

        //arr[i-1] = 0;

        //i--;

        if (index < 0 || index >= i)
        {
            std::cout << "Invalid index!" << std::endl;
            return;
        }

        i--;

        if (i > 0)
        {
            //T* new_arr = reinterpret_cast<T*>(malloc(i * sizeof(T)));
            //if (index > 0)
            //    memcpy(new_arr, arr, index * sizeof(T));
            //if (index < i)
            //    memcpy(new_arr + index, arr + index + 1, (i - index) * sizeof(T));

            //free(arr);
            //arr = new_arr;

            //std::cout << "memmove" << std::endl;
            memmove(arr + index, arr + index + 1, (i - index) * sizeof(T));
            arr = reinterpret_cast<T*>(realloc(arr, i * sizeof(T)));
        }
        else
        {
            free(arr);
            arr = nullptr;
        }
        size = i;

    }

    void printArray() 
    {
        for (int s = 0; s < size; s++)
        {
            std::cout << "s[" << s << "] = " << arr[s] << " \n";
        }
        std::cout << std::endl;
    }
private:
    void rise(int value=10)
    {
        //T* new_arr = reinterpret_cast<T*>(malloc((size + value) * sizeof(T)));
        //memcpy(new_arr, arr, i * sizeof(T));
        ////for (size_t s = 0; s < size; s++)
        ////{
        ////    new_arr[s] = arr[s];
        ////}
        //free(arr);
        //arr = new_arr;
        //size = size + value;
        //std::cout << "realloc" << std::endl;

        arr = reinterpret_cast<T*>(realloc(arr, (size + value) * sizeof(T)));

        if (arr == nullptr)
        {
            std::cout << "arr == nullptr" << std::endl;
            throw std::bad_alloc();
        }
 
        size = size + value;
       


    }

    T* arr;
    int size=0;
    int i=0;

};

