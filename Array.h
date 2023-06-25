#include <iostream>
#include <type_traits>

template<typename T>
class Array
{
private:
	T* arr_ = nullptr;
	size_t capacity_ = 0;
	size_t size_ = 0;
public:
	Array() = default;
	Array(size_t capacity_) : capacity_(capacity_)
	{
		arr_ = reinterpret_cast<T*>(malloc(capacity_ * sizeof(T)));
		//if arr_ == nullptr ...
	}
	Array(const Array<T>& other)
	{
		//std::cout << "Array(const Array<T>& other)\n";
		capacity_ = other.capacity_;
		size_ = 0;
		arr_ = reinterpret_cast<T*>(malloc(capacity_ * sizeof(T)));
		//if arr_ == nullptr ...
		
		//=>

		//delegating constructor
		
		for (size_t i = 0; i < other.size_; i++)
		{
			//push_back(other.arr_[i]);
			//construct as copy
		}
	}
	~Array()
	{
		/*for (size_t i = 0; i < size_; i++)
		{
			arr_[i].~T();
		}
		free(arr_);
		arr_ = nullptr;*/
		clear();
	}
	bool operator==(const Array& other) const
	{
		if (size_ != other.size_)
			return false;

		for (size_t cntr = 0; cntr < size_; cntr++)
		{
			if (arr_[cntr] != other.arr_[cntr])
			{
				return false;
			}
		}

		return true;
	}
	size_t size() const
	{
		return size_;
	}
	bool is_empty() const
	{
		if (arr_ = nullptr)
			return true;
		return false;
	}
	template<typename... Elements>
	void push_back(Elements&&... values)
	{
		if (size_ == capacity_)
		{
			increaseCapacity();
		}
		static_assert(std::is_constructible_v<T, Elements...>, "THIS IS ERROR");
		new(arr_ + size_) T(std::forward<Elements>(values)...);
		++size_;
	}
	void pop_back()
	{
		if (size_ == 0)
		{
			//throw ...
			return;
		}

		size_--;

		if (size_ > 0)
		{
			//деструктор
			memmove(arr_, arr_ + 1, size_ * sizeof(T));
		}
		else
		{
			clear();
		}
	}
	T& at(size_t index)
	{
		if (index >= size_)
		{
			throw std::out_of_range("Invalid index!");
		}
		return arr_[index];
	}
	T& front()
	{
		//throw ...
		return arr_[0];
	}
	T& back()
	{
		//throw ...
		return arr_[size_-1];
	}
	class Iterator
	{
	private:
		T* ptr_;

	public:
		explicit Iterator(T* ptr) : ptr_(ptr) {}

		Iterator& operator++()
		{
			++ptr_;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator iterator = *this;
			++ptr_;
			return iterator;
		}

		Iterator& operator--()
		{
			--ptr_;
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator iterator = *this;
			--ptr_;
			return iterator;
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}

		bool operator==(const Iterator& other) const
		{
			return ptr_ == other.ptr_;
		}

		bool operator!=(const Iterator& other) const
		{
			return ptr_ != other.ptr_;
		}
	};

	Iterator begin()
	{
		return Iterator(arr_);
	}

	Iterator end()
	{
		return Iterator(arr_ + size_);
	}

	void clear()
	{
		for (size_t i = 0; i < size_; i++)
		{
			arr_[i].~T();
		}
		free(arr_);
		arr_ = nullptr;
		size_ = 0;
	}

	void insert(size_t index, T& const value)
	{
		//вставка по нулевому индексу в конец пустого массива?

		if (index < 0 || index > size_)
		{
			std::cout << "Invalid index!" << '\n';
			return;
		}
		if (size_ == capacity_)
		{
			increaseCapacity();
		}
		//memmove(arr_ + index + 1, arr_ + index, (size_ - index) * sizeof(T));
		std::move_backward(arr_ + index, arr_ + size_, arr_ + index + 1);
		arr_[index] = value;
		size_++;
	}
	void erase(size_t index)
	{
		//if (index < 0 || index >= size_)
		//{
		//    std::cout << "Invalid index!" << std::endl;
		//    return;
		//}

		//for (int j = index; j < size_ - 1; j++)
		//{
		//    arr_[j] = arr_[j + 1];
		//}

		//arr_[size_-1] = 0;

		//size_--;

		if (index < 0 || index >= size_)
		{
			std::cout << "Invalid index!" << std::endl;
			return;
		}

		size_--;

		if (size_ > 0)
		{
			//T* new_arr = reinterpret_cast<T*>(malloc(size_ * sizeof(T)));
			//if (index > 0)
			//    memcpy(new_arr, arr_, index * sizeof(T));
			//if (index < size_)
			//    memcpy(new_arr + index, arr_ + index + 1, (size_ - index) * sizeof(T));

			//free(arr_);
			//arr_ = new_arr;

			//std::cout << "memmove" << std::endl;

			arr_[index].~T();

			memmove(arr_ + index, arr_ + index + 1, (size_ - index) * sizeof(T));
			//std::move(...)
		}
		else
		{
			clear();
		}
	}
	template<typename... Args>
	void emplace(Args&&... args)
	{
		if (size_ == capacity_)
		{
			increaseCapacity();
		}
		new(&arr_[size_]) T(std::forward<Args>(args)...);
		++size_;
	}
	void print()
	{
		for (int i = 0; i < size_; i++)
		{
			std::cout << "i[" << i << "] = " << arr_[i] << " \n";
		}
		std::cout << "++---SIZE_END---++" << " \n";
		for (int i = size_; i < capacity_; i++)
		{
			std::cout << "i[" << i << "] = " << arr_[i] << " \n";
		}
		std::cout << "-----CAPACITY_END-----" << " \n";
		std::cout << std::endl;
	}
	void cut()
	{
		T* new_arr = reinterpret_cast<T*>(realloc(arr_, size_ * sizeof(T)));
		if (new_arr == nullptr)
		{
			std::cout << "arr_ == nullptr" << std::endl;
			free(arr_);
			throw std::bad_alloc();
		}
		capacity_ = size_;
		arr_ = new_arr;
	}
	void resize(int size)
	{
		increaseCapacity(size);
	}
private:
	void increaseCapacity(int delta = 10)
	{
		//T* new_arr = reinterpret_cast<T*>(malloc((capacity_ + value) * sizeof(T)));
		//memcpy(new_arr, arr_, size_ * sizeof(T));
		////for (size_t s = 0; s < capacity_; s++)
		////{
		////    new_arr[s] = arr_[s];
		////}
		//free(arr_);
		//arr_ = new_arr;
		//capacity_ = capacity_ + value;
		//std::cout << "realloc" << std::endl;
		T* new_arr = reinterpret_cast<T*>(realloc(arr_, (capacity_ + delta) * sizeof(T)));
		if (new_arr == nullptr)
		{
			std::cout << "arr_ == nullptr" << std::endl;
			//free(arr_);
			throw std::bad_alloc();
		}
		arr_ = new_arr;
		capacity_ = capacity_ + delta;
	}
	//push_back
	//void add_to_Array(const T& value)
	//{
	//	if (size_ >= capacity_)
	//	{
	//		rise();
	//	}
	//	 
	//	if constexpr (std::is_move_constructible_v<T>)
	//	{
	//	new(arr_ + size_) T(std::move(value));
	//	}
	//	else
	//	{
	//		new(arr_ + size_) T(value);
	//	}
	//	++size_;
	//}
	//emplace_back
	//void add_to_Array(a, b, c)
	//{
	//	if (size_ >= capacity_)
	//	{
	//		//std::cout << "\n RISE \n";
	//		rise();
	//	}
	//	new(arr_ + size_) T(a, b, c);
	//	++size_;
	//}
};