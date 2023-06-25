#include <iostream>

namespace forward
{
	template <typename T>
	void print(T& value)
	{
		std::cout << "l-value " << value << std::endl;
	}

	template <typename T>
	void print(T&& value)
	{
		std::cout << "r-value " << value << std::endl;
	}

	void println()
	{

	}

	//remove_reference

	//template<typename T>
	//T&& forward(T& element)
	//{
	//	return static_cast<T&&>(element);
	//}

	//УХОДИМ ОТ НЕЁ, Т.К. В НЕЙ КОМПИЛЯТОР АВТОМАТИЧЕСКИ ВЫТАСКИВАЕТ ТИП ПАРАМЕТРА И ОН НЕВЕРНЫЙ => l-value

	//для чистых r-value, передаваемых напрямую:
	template<typename T>
	T&& forward(std::remove_reference_t<T>&& element)
	{
		return static_cast<T&&>(element);
	}

	//для l-value и r-value, передаваемых через функцию, т.е. как l-value:
	template<typename T>
	T&& forward(std::remove_reference_t<T>& element)
	{
		return static_cast<T&&>(element);
	}

	template<typename T, typename... Elements>
	void println(T&& first, Elements&&... values)
	{
		print(forward<T>(first));
		println(forward<Elements>(values)...);
	}

	int main_forward()
	{
		int a = 1;
		forward<int&>(a);

		int&& r = 2;
		forward<int&&>(r);

		forward<int>(5);

		println(5, 8, a, r, "hello");

		return 0;
	}
};