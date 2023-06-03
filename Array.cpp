#include <iostream>

template<typename T>
class Array {
public:
    Array(int size) : size(size)
    {
        arr = reinterpret_cast<T*>(malloc(size * sizeof(T)));
        
    }

    ~Array()
    {
        free(arr);
    }

    void add_to_Array(const T& value)
    {
        if (i+1 == size)
        {
            rise();
        }

        new(arr+i) T();
        arr[i] = value;
        ++i;    
    }

    void rise(int value=10)
    {
        T* new_arr = reinterpret_cast<T*>(malloc((size + value) * sizeof(T)));
        for (size_t s = 0; s < size; s++)
        {
            new_arr[s] = arr[s];
        }
        free(arr);
        arr = new_arr;

        size = size + value;
    }

    void printArray() 
    {
        for (int s = 0; s < size; s++)
        {
            std::cout << "s[" << s << "] = " << arr[s] << " \n\n";
        }
        std::cout << std::endl;
    }

private:
    T* arr;
    int size;
    int i=0;
};

