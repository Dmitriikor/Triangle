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
		if (size == other.size && index == other.index)
		{
			for (size_t cntr = 0; cntr < index; cntr++)
			{
				if (arr[cntr] != other.arr[cntr])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	Array() = default;
	Array(const Array<T>& other)
	{
		//std::cout << "Array(const Array<T>& other)\n";
		size = other.size;
		index = 0;
		arr = reinterpret_cast<T*>(malloc(size * sizeof(T)));
		for (size_t cntr = 0; cntr < other.index; cntr++)
		{
			add_to_Array(other.arr[cntr]);
		}
	}
	~Array()
	{
		free(arr);
	}
	template<typename... Elements>
	void add_to_Array(Elements&&... values)
	{
		if (index >= size)
		{
			rise();
		}

		//static_assert(std::is_constructible_v<T, Elements...>,"THIS IS ERROR");

		if (std::is_constructible_v<T, Elements...>)
		{
			new(arr + index) T(std::forward<Elements>(values)...);
			++index;
		}
	}
	void remove_from_Array(int delVal)
	{
		//if (delVal < 0 || delVal >= index)
		//{
		//    std::cout << "Invalid delVal!" << std::endl;
		//    return;
		//}

		//for (int j = delVal; j < index - 1; j++)
		//{
		//    arr[j] = arr[j + 1];
		//}

		//arr[index-1] = 0;

		//index--;

		if (delVal < 0 || delVal >= index)
		{
			std::cout << "Invalid delVal!" << std::endl;
			return;
		}

		index--;

		if (index >= 0)
		{
			//T* new_arr = reinterpret_cast<T*>(malloc(index * sizeof(T)));
			//if (delVal > 0)
			//    memcpy(new_arr, arr, delVal * sizeof(T));
			//if (delVal < index)
			//    memcpy(new_arr + delVal, arr + delVal + 1, (index - delVal) * sizeof(T));

			//free(arr);
			//arr = new_arr;

			//std::cout << "memmove" << std::endl;
			memmove(arr + delVal, arr + delVal + 1, (index - delVal) * sizeof(T));
			
		}
		else
		{
			free(arr);
			arr = nullptr;
		}
	}
	void remove_from_Array()
	{
		if (index == 0)
		{
			return;
		}

		index--;

		if (index >= 0)
		{
			memmove(arr, arr + 1, index * sizeof(T));
		}
		else
		{
			free(arr);
			arr = nullptr;
		}
	}
	void printArray()
	{
		for (int s = 0; s < index; s++)
		{
			std::cout << "s[" << s << "] = " << arr[s] << " \n";
		}
		std::cout << "++---INDEX_END---++"<< " \n";
		for (int s = index; s < size; s++)
		{
			std::cout << "s[" << s << "] = " << arr[s] << " \n";
		}
		std::cout << "-----SIZE_END-----" << " \n";
		std::cout << std::endl;
	}
	void cutArray()
	{
		T* new_arr = reinterpret_cast<T*>(realloc(arr, index * sizeof(T)));
			if (new_arr == nullptr)
			{
				std::cout << "arr == nullptr" << std::endl;
				free(arr);
				throw std::bad_alloc();
			}
		size = index;
		arr = new_arr;
	}
	size_t sizeArray() const
	{
		return index;
	}
	bool is_emptyArray()
	{
		if (arr = nullptr)
			return true;
		return false;
	}



	//push_back
	//void add_to_Array(const T& value)
	//{
	//	if (index >= size)
	//	{
	//		rise();
	//	}
	//	 
	//	if constexpr (std::is_move_constructible_v<T>)
	//	{
	//	new(arr + index) T(std::move(value));
	//	}
	//	else
	//	{
	//		new(arr + index) T(value);
	//	}
	//	++index;
	//}
	//emplace_back
	//void add_to_Array(a, b, c)
	//{
	//	if (index >= size)
	//	{
	//		//std::cout << "\n RISE \n";
	//		rise();
	//	}
	//	new(arr + index) T(a, b, c);
	//	++index;
	//}
private:
	void rise(int value = 10)
	{
		//T* new_arr = reinterpret_cast<T*>(malloc((size + value) * sizeof(T)));
		//memcpy(new_arr, arr, index * sizeof(T));
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
	size_t size = 0;
	size_t index = 0;
};