#include <iostream>
#include <type_traits>

template<typename T>
class Array
{
public:

	Array(int size) : size(size)
	{
		arr = reinterpret_cast<T*>(malloc(size * sizeof(T)));
	}

	bool operator==(const Array& other) const
	{
		return arr == other.arr && size == other.size && i == other.i;
		//лучше по индексам (по элементам)
	}

	Array() = default;

	Array(const T* arr, int size) :size(size)
	{
		//копирование
	}

	~Array()
	{
		free(arr);
	}


	template<typename... Elements>
	void add_to_Array(Elements&&... values)
	{
		if (i >= size)
		{
			rise();
		}

		static_assert(std::is_constructible_v<T, Elements...>,"THIS IS ERROR");

		if (std::is_constructible_v<T, Elements...>)
		{
			new(arr + i) T(std::forward<Elements>(values)...);
			++i;
		}
	}


	//push_back
	//void add_to_Array(const T& value)
	//{
	//	if (i >= size)
	//	{
	//		rise();
	//	}
	//	 
	//	if constexpr (std::is_move_constructible_v<T>)
	//	{
	//	new(arr + i) T(std::move(value));
	//	}
	//	else
	//	{
	//		new(arr + i) T(value);
	//	}
	//	++i;
	//}

	//emplace_back
	//void add_to_Array(a, b, c)
	//{
	//	if (i >= size)
	//	{
	//		//std::cout << "\n RISE \n";
	//		rise();
	//	}

	//	new(arr + i) T(a, b, c);
	//	++i;
	//}

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
		for (int s = 0; s < i; s++)
		{
			std::cout << "s[" << s << "] = " << arr[s] << " \n";
		}
		std::cout << "++---INDEX_END---++"<< " \n";
		for (int s = i; s < size; s++)
		{
			std::cout << "s[" << s << "] = " << arr[s] << " \n";
		}
		std::cout << "-----SIZE_END-----" << " \n";
		std::cout << std::endl;
	}

	void cutArray()
	{
			T* new_arr = reinterpret_cast<T*>(realloc(arr, i * sizeof(T)));
			if (new_arr == nullptr)
			{
				std::cout << "arr == nullptr" << std::endl;
				free(arr);
				throw std::bad_alloc();
			}
		arr = new_arr;
	}

private:
	void rise(int value = 10)
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

		T* new_arr = reinterpret_cast<T*>(realloc(arr, (size + value) * sizeof(T)));

		if (new_arr == nullptr)
		{
			std::cout << "arr == nullptr" << std::endl;
			free(arr);
			throw std::bad_alloc();
		}

		arr = new_arr;
		size = size + value;
	}

	T* arr = nullptr;
	int size = 0;
	int i = 0;
};