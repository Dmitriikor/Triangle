///!!!• operator+=
///!!!• return Matrix <T> operator +
///!!!• constructor std::move()
///!!!• operator std::move()
///!!!• void Matrix<T>::print(std::ostream& output) const
///!!!  add new mtx_bools to constructor
/// 
/// 
#ifndef Matrix_TEMPLATE_H__

#define Matrix_TEMPLATE_H__

#include <stdexcept>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <compare>

///using T = char;
///using pointer_type = T*;


struct Coordinate {
	size_t i;
	size_t j;

};

template <typename T>
class Matrix
{
public:
	struct str_i 
	{
		T* str;
		size_t M;

		str_i(T* initMatrix, size_t index) : str(initMatrix), M(index)
		{
		}

		T& operator[](size_t j) {
			return str[j];
		}

		//#include "IT_TEST.h"
		//using iterator = Iterator<T>;

		//!!!по строке можно проходить == итерироваться, т.е.ей нужен свой итератор
		class iterator
		{
			friend struct str_i;
			T* ptr;
			
		public:
			using value_type = T;
			using pointer = T*;
			using reference = T&;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			explicit iterator(T* p) : ptr(p)
			{
			}
			iterator& operator++()
			{
				++ptr;
				return *this;
			}
			reference operator*() const
			{
				return *ptr;
			}
			pointer operator->() const
			{
				return ptr;
			}
			iterator operator++(int)
			{
				iterator tmp(*this);
				++ptr;
				return tmp;
			}
			iterator& operator+=(difference_type n)
			{
				ptr += n;
				return *this;
			}
			iterator operator+(difference_type n) const
			{
				iterator tmp(*this);
				tmp += n;
				return tmp;
			}
			bool operator==(iterator other) const
			{
				return ptr == other.ptr;
			}
		};

		iterator begin() { return iterator(str); }
		iterator end() { return iterator(str + M); }
	};

	struct const_str_i
	{
		const T* const* stl;
		size_t i;
		size_t N;
		const_str_i(const T* const* m, size_t i, size_t N) : stl(m), i(i), N(N)
		{
		}

		const T& operator[](size_t j) const {
			return stl[i][j];
		}

		class iterator
		{
			friend class const_str_i;
			const T* const* ptr;
			//const T* const* ptr;
		public:
			using value_type = T;
			using pointer = const T*;
			using reference = const T&;
			using difference_type = std::ptrdiff_t;
			//using iterator_category = std::random_access_iterator_tag;
			using iterator_category = std::forward_iterator_tag;

			iterator(const T* const* p) : ptr(p) {}

			const reference operator*() const
			{
				return **ptr;
			}
			const pointer operator->() const
			{
				return ptr;
			}
			iterator& operator++()
			{
				++ptr;
				return *this;
			}
			const iterator operator++(int) const
			{
				iterator tmp(*this);
				++ptr;
				return tmp;
			}
			iterator& operator+=(difference_type n)
			{
				ptr += n;
				return *this;
			}
			iterator operator+(difference_type n) const
			{
				iterator tmp(*this);
				tmp += n;
				return tmp;
			}
			bool operator==(const iterator other) const
			{
				return ptr == other.ptr;
			}

			bool operator!=(const iterator other) const
			{
				return ptr != other.ptr;
			}
		};
		const iterator begin() const { return iterator(stl); }
		const iterator end() const { return iterator(stl + N); }

	};

public:
	//!!! ПО СТРОКАМ, Т.Е. "УКАЗЫВАЕТ" НА СТРОКУ
	class line_iterator 
	{
	public:
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;
		line_iterator(Matrix<T>* matrix, size_t index) : matrix_(matrix), index_(index)
		{
			if (matrix_ == nullptr)
				throw std::invalid_argument("matrix_ pointer is null");
		}
		T& operator*() const
		{
			return matrix_->arr[index_ / matrix_->M][index_ % matrix_->M];
		}
		line_iterator& operator++()
		{
			++index_;
			return *this;
		}
		line_iterator operator++(int) {
			line_iterator temp = *this;
			++(*this);
			return temp;
		}
		bool operator==(const line_iterator& other) const
		{
			return (matrix_ == other.matrix_) && (index_ == other.index_) && (matrix_ != nullptr) && (other.matrix_ != nullptr);;
		}
	private:
		Matrix<T>* matrix_;
		size_t index_;
	};

	class const_line_iterator 
	{
	public:
		using value_type = T;
		using reference = const T&;
		using pointer = const T*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;
		const_line_iterator(const Matrix<T>* matrix, size_t index) : matrix_(matrix), index_(index)
		{
			if (matrix_ == nullptr) {
				throw std::invalid_argument("matrix_ pointer is null");
			}
		}
		const T& operator*() const
		{
			return *(matrix_->arr[index_ / matrix_->M] + index_ % matrix_->M);
		}
		const_line_iterator& operator++()
		{
			++index_;
			return *this;
		}
		const_line_iterator operator++(int) {
			const_line_iterator temp = *this;
			++(*this);
			return temp;
		}
		bool operator==(const const_line_iterator& other) const {
			return (matrix_ == other.matrix_) && (index_ == other.index_) && (matrix_ != nullptr) && (other.matrix_ != nullptr);
		}
	private:
		const Matrix<T>* matrix_;
		size_t index_;
	};

	line_iterator lbegin() { return line_iterator(this, 0); }
	line_iterator lend() { return line_iterator(this, N * M); }
	const_line_iterator lbegin() const { return const_line_iterator(this, 0); }
	const_line_iterator lend() const { return const_line_iterator(this, N * M); }
	const_line_iterator const_lbegin() const { return const_line_iterator(this, 0); }
	const_line_iterator const_lend() const { return const_line_iterator(this, N * M); }


	class iterator
	{
	private:
		friend class Matrix;
		str_i obj; 
		T** mtrx;
		size_t M;
		size_t index;
	private:
		explicit iterator(T** is_this,size_t M, size_t index) : 
			mtrx(is_this),
			M(M),
			index(index),
			obj(*is_this, M)
		{
		}
	public:

		using value_type = str_i;
		using pointer = str_i*;
		using reference = str_i&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		reference operator*() const
		{
			return const_cast<reference>(obj);
		}
		pointer operator->() const
		{
			return const_cast<pointer>(&obj);
		}

		bool operator==(const iterator& other) const
		{
			return  index  == other.index;
		}

		iterator& operator+=(difference_type n)
		{
			index += n;
			return *this;
		}

		iterator& operator++()
		{
			*this += 1;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}

		iterator operator+(difference_type n) const
		{
			iterator tmp = *this;
			tmp += n;
			return tmp;
		}


		iterator& operator-=(difference_type n)
		{
			index -= n;
			return *this;
		}

		iterator& operator--()
		{
			*this -= 1;
			return *this;
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			--(*this);
			return tmp;
		}

		iterator operator-(difference_type n) const
		{
			iterator tmp = *this;
			tmp -= n;
			return tmp;
		}

		difference_type operator-(const iterator& other) const
		{
			return index - other.index;
		}

		std::strong_ordering operator<=>(const iterator& other) const
		{
			if (index < other.index)
				return std::strong_ordering::less;
			else if (index == other.index)
				return std::strong_ordering::equal;
			else
				return std::strong_ordering::greater;
		}
	};




	//class iterator 
	//{
	//private:
	//	friend class Matrix;
	//	str_i obj; //str_i* ptr;
	////public:
	//private:
	//	//std::unique_ptr<str_i> ptr;
	//	//#include <memory>
	//	//explicit iterator(Matrix<T>* is_this, size_t index) : ptr(std::make_unique<str_i>(is_this, index)){}
	//	explicit iterator(Matrix<T>* is_this, size_t index) : //_is_this(is_this), _index(index),
	//		//ptr(new str_i(is_this, index))
	//		obj(is_this, index)
	//	{
	//	/*	str_i temp(*is_this, index);
	//		
	//		ptr->my_Matrix_TEMPLATE = temp.my_Matrix_TEMPLATE;
	//		ptr->i = temp.i;
	//	
	//		std::cout << "\n\n";*/
	//	}
	//public:
	//	//iterator(const iterator& other)
	//	//{
	//	//	//ptr = other.ptr;/* new str_i(other.ptr->my_Matrix_TEMPLATE, other.ptr->i);*/
	//	//	obj = other.obj;
	//	//}
	//	//iterator& operator=(const iterator& other)
	//	//{
	//	//	if (this == &other)
	//	//		return *this;
	//	//	//delete ptr;
	//	//	ptr = other.ptr; /*new str_i(other.ptr->my_Matrix_TEMPLATE, other.ptr->i);*/
	//	//	return *this;
	//	//}
	//	//~iterator()
	//	//{
	//	//	delete ptr;
	//	//}
	//	
	//	//str_i::iterator begin() { return str_i::iterator(_is_this->arr[_index]); }
	//	//str_i::iterator end() { return str_i::iterator(_is_this->arr[_index] + (_is_this->get_M())); }
	//	using value_type = str_i;
	//	using pointer = str_i*;
	//	using reference = str_i&;
	//	using difference_type = std::ptrdiff_t;
	//	using iterator_category = std::random_access_iterator_tag;
	//	reference operator*() const
	//	{
	//		//return *ptr;
	//		return const_cast<reference>(obj);
	//	}
	//	pointer operator->() const
	//	{
	//		//return ptr.get();
	//		//return ptr;
	//		return const_cast<pointer>(&obj);
	//	}
	//	bool operator==(const iterator& other) const
	//	{
	//		//return ptr->i == other.ptr->i;
	//		return obj.i == other.obj.i;
	//	}
	//	iterator& operator+=(difference_type n)
	//	{
	//		obj.i += n;
	//		//ptr.i += n;
	//		return *this;
	//	}
	//	iterator& operator++()
	//	{
	//		*this += 1;
	//		//++ptr->i;
	//		return *this;
	//	}
	//	iterator operator++(int)
	//	{
	//		iterator tmp = *this;
	//		++(*this);
	//		return tmp;
	//	}
	//	iterator operator+(difference_type n) const
	//	{
	//		iterator tmp = *this;
	//		tmp += n;
	//		return tmp;
	//	}
	//	iterator& operator-=(difference_type n)
	//	{
	//		obj.i -= n;
	//		//ptr.i -= n;
	//		return *this;
	//	}
	//	iterator& operator--()
	//	{
	//		*this -= 1;
	//		return *this;
	//	}
	//	iterator operator--(int)
	//	{
	//		iterator tmp = *this;
	//		--(*this);
	//		return tmp;
	//	}
	//	iterator operator-(difference_type n) const
	//	{
	//		iterator tmp = *this;
	//		tmp -= n;
	//		return tmp;
	//	}
	//	difference_type operator-(const iterator& other) const
	//	{
	//		return obj.i - other.obj.i;
	//		//return ptr.i - other.ptr.i;
	//	}
	//	std::strong_ordering operator<=>(const iterator& other) const
	//	{
	//		if (obj.i < other.obj.i)
	//			return std::strong_ordering::less;
	//		else if (obj.i == other.obj.i)
	//			return std::strong_ordering::equal;
	//		else
	//			return std::strong_ordering::greater;
	//	}
	//};

	iterator begin() { return iterator(arr, get_M(), 0); }
	iterator end() { return iterator(arr, get_M(), get_N()); }
	/*const_iterator begin() const { return const_iterator(this, 0); }
	const_iterator end() const  { return const_iterator(this, get_N()); }
	const_iterator const_begin() const { return const_iterator(this, 0); }
	const_iterator const_end() const  { return const_iterator(this, get_N()); }*/

	Matrix();
	Matrix(size_t N, size_t M);
	Matrix(size_t N, size_t M, const T& value);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);

	Matrix& operator=(Matrix&& other) noexcept;

	~Matrix();

	Matrix& operator=(const Matrix& other);

	bool operator==(const Matrix& other) const;

	int operator<=>(const Matrix& other) const;

	size_t size() const
	{
		return N * M;
	}

	Matrix& operator+=(const Matrix<T>& other);
	Matrix operator+(const Matrix<T>& other) const;

	size_t get_N() const;

	size_t get_M() const;

	void resize(size_t N_, size_t M_);
	void resize(size_t strings, size_t columns, const T& value);
	void resize_and_override(size_t N_, size_t M_, const T& value);

	void fill(const T& value);
	bool is_empty();

	void print() const;
	//void print(std::ofstream& output) const;

	void set_at(const size_t N, const size_t M, const T& data);
	void set_at(Coordinate cell, const T& data);

	T& get_at(size_t N, size_t M);
	T& get_at(Coordinate cell);

	const T& get_at(size_t N, size_t M) const;
	const T& get_at(Coordinate cell) const;

	void clear();

private:
	size_t N;
	size_t M;
	T** arr;
	static T** allocate(size_t N, size_t M);

	template <typename U>
	friend void print(const Matrix<U>& other, std::ostream& outfile);
	friend class iterator;
public:
	str_i operator[](size_t i);
	const_str_i operator[](size_t i) const;
};




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_TEMPLATE_v1_start
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////template <typename T>
////std::mutex& Matrix<T>::get_cout_mutex()
////{
////	static std::mutex m;
////	return m;
////}

template <typename T>
Matrix<T>::Matrix() : N(0), M(0), arr(nullptr)
{

}

template <typename T>
Matrix<T>::Matrix(size_t N, size_t M) : N(N), M(M)
{
	if (N == 0 || M == 0)
	{
		//!!set_empty
		N = M = 0;
		arr = nullptr;
		return;
	}

	arr = allocate(N, M);
}

template<typename T>
inline Matrix<T>::Matrix(size_t N, size_t M, const T& value) : N(N), M(M), arr(nullptr)
{
	if (N == 0 || M == 0)
	{
		return;
	}

	arr = allocate(N, M);
	fill(value);
}

template <typename T>
void Matrix<T>::resize_and_override(size_t N_, size_t M_, const T& value)
{

	if (N == N_ && M == M_)
		return;

	if (N_ == 0 || M_ == 0)
	{
		clear();
		return;
	}

	T** new_arr;
	new_arr = allocate(N_, M_);

	clear();

	arr = new_arr;

	fill(value);

}

template <typename T>
void Matrix<T>::resize(size_t N_, size_t M_, const T& value)
{


	if (N == N_ && M == M_)
		return;

	if (N_ == 0 || M_ == 0)
	{
		clear();
		return;
	}

	T** new_arr;
	new_arr = allocate(N_, M_);

	int min_N_lim = (N_ < N) ? N_ : N;
	int min_M_lim = (M_ < M) ? M_ : M;

	for (size_t i = 0; i < min_N_lim; ++i)
		for (size_t j = 0; j < min_M_lim; ++j)
			new_arr[i][j] = arr[i][j];

	for (size_t i = 0; i < N_; ++i)
		for (size_t j = 0; j < M_; ++j)
			if (new_arr[i][j] == T())
				new_arr[i][j] = value;

	clear();
	N = N_;
	M = M_;
	arr = new_arr;
	;
}

template <typename T>
void Matrix<T>::resize(size_t N_, size_t M_)
{


	if (N == N_ && M == M_)
		return;

	if (N_ == 0 || M_ == 0)
	{
		clear();
		return;
	}

	T** new_arr;
	new_arr = allocate(N_, M_);

	int min_N_lim = (N_ < N) ? N_ : N;
	int min_M_lim = (M_ < M) ? M_ : M;

	for (size_t i = 0; i < min_N_lim; ++i)
		for (size_t j = 0; j < min_M_lim; ++j)
			new_arr[i][j] = arr[i][j];

	clear();
	N = N_;
	M = M_;
	arr = new_arr;

}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : N(other.N), M(other.M)
{
	if (N == 0)
	{
		arr = nullptr;
		return;
	}

	arr = allocate(N, M);
	//!!! copy-function
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			arr[i][j] = other.arr[i][j];
		}
	}
}

template<typename T>
Matrix<T>::Matrix(Matrix&& other) : Matrix()
{

	////N = 0;
	////M = 0;
	////arr = nullptr;
	if (arr != nullptr)
		throw std::out_of_range("this not yet formed");
	////std::swap(N, other.N);
	////std::swap(M, other.M);
	////std::swap(arr, other.arr);

	*this = std::move(other); //!!! this not yet formed => constructor, null (NOT clear!)

}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
{

	clear();

	std::swap(N, other.N);
	std::swap(M, other.M);

	std::swap(arr, other.arr);

	return *this;
}

template <typename T>
Matrix<T>::~Matrix()
{
	clear();
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (other.arr == nullptr)
	{
		return *this;
	}

	clear();

	N = other.N;
	M = other.M;

	arr = allocate(N, M);

	//!!! copy-function

	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			arr[i][j] = other.arr[i][j];
		}
	}

	return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix& other) const
{
	return (*this <=> other) == 0;
}

template<typename T>
int Matrix<T>::operator<=>(const Matrix& other) const
{
	if (size() < other.size())
		return -1;

	if (size() > other.size())
		return +1;

	return 0;
}

////template<typename T>
////std::partial_ordering Matrix<T>::operator<=>(const Matrix& other) const
////{
////	/*if (N < other.N || M < other.M)
////		return std::partial_ordering::less;
////
////	if (N > other.N || M > other.M)
////		return std::partial_ordering::greater;*/
////	if (N == other.N && M == other.M)
////		return std::partial_ordering::equivalent;
////}



template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{


	int new_N = N + other.N;
	int new_M = M + other.M;
	T** new_arr = allocate(new_N, new_M);

	{
		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < M; ++j)
			{
				new_arr[i][j] = arr[i][j];
			}
		}
	}
	{
		for (size_t i = 0; i < other.N; ++i)
		{
			for (size_t j = 0; j < other.M; ++j)
			{
				new_arr[i + N][j + M] = other.arr[i][j];
			}
		}
	}

	N = new_N;
	M = new_M;
	arr = new_arr;

	return *this;
}

template <typename T>
typename Matrix<T>::str_i Matrix<T>::operator[](size_t i) {
	return str_i(arr[i], M);
}

template <typename T>
typename Matrix<T>::const_str_i Matrix<T>::operator[](size_t i) const {
	return const_str_i(arr, i, N);
}
//
//
//template <typename T>
//typename Matrix<T>::str_i Matrix<T>::operator[](size_t i) {
//	return str_i(*arr, i);
//}
//
//template <typename T>
//typename Matrix<T>::const_str_i Matrix<T>::operator[](size_t i) const {
//	return const_str_i(arr, i);
//}

template <typename T>
T** Matrix<T>::allocate(size_t N_, size_t M_)
{
	T** new_arr = new T * [N_]();

	for (size_t i = 0; i < N_; ++i) {
		new_arr[i] = new T[M_]();
	}

	return new_arr;
}

template <typename T>
size_t Matrix<T>::get_N() const {
	return N;
}

template <typename T>
size_t Matrix<T>::get_M() const {
	return M;
}

template <typename T>
void Matrix<T>::fill(const T& value)
{


	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			arr[i][j] = value;
		}
	}

}

template <typename T>
void Matrix<T>::set_at(size_t i, size_t j, const T& data) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void set_at : method i = " + std::to_string(i) + " > Matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void set_at : method j = " + std::to_string(j) + " > Matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void set_at : NO create_Matrix_TEMPLATE");

	arr[i][j] = data;

}

template <typename T>
void Matrix<T>::set_at(Coordinate cell, const T& data) {
	set_at(cell.i, cell.j, data);
}

template <typename T>
T& Matrix<T>::get_at(size_t i, size_t j) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void get_at : method i = " + std::to_string(i) + " > Matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void get_at : method j = " + std::to_string(j) + " > Matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void get_at : NO create_Matrix_TEMPLATE");

	return arr[i][j];
}

template <typename T>
T& Matrix<T>::get_at(Coordinate cell) {
	return get_at(cell.i, cell.j);
}

template <typename T>
const T& Matrix<T>::get_at(size_t i, size_t j) const {
	if (i >= N)
		throw std::out_of_range("out_of_range in void get_at : method i = " + std::to_string(i) + " > Matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void get_at : method j = " + std::to_string(j) + " > Matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void get_at : NO create_Matrix_TEMPLATE");

	return arr[i][j];
}

template <typename T>
const T& Matrix<T>::get_at(Coordinate cell) const {
	return get_at(cell.i, cell.j);
}

template <typename T>
void Matrix<T>::clear() {
	if (arr != nullptr)
	{
		for (size_t i = 0; i < N; ++i) {
			delete[] arr[i];
		}
		delete[] arr;

		arr = nullptr;
	}
	N = 0;
	M = 0;
}

template <typename T>
bool Matrix<T>::is_empty()
{
	if (arr == nullptr)
		return true;

	return false;
}

template <typename T>
void print(const Matrix<T>& other, std::ostream& outfile)
{
	for (size_t i = 0; i < other.N; ++i)
	{
		for (size_t j = 0; j < other.M; ++j)
		{
			outfile << other.arr[i][j];
		}
		outfile << std::endl;
	}
}

template <typename T>
void Matrix<T>::print() const
{
	/*for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			std::cout << arr[i][j];
		}
		std::cout << "\n";
	}*/

	::print(*this, std::cout);

	//this->print(std::cout);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	Matrix<T> copy = *this;
	copy += other;
	return copy;
	//return std::move(copy);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_TEMPLATE_v1_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //! Matrix_TEMPLATE_H__









////#include <iostream>
////#include <mutex>
////
////std::ostream&
////print_one(std::ostream& os)
////{
////	return os;
////}
////
////template <class A0, class ...Args>
////std::ostream&
////print_one(std::ostream& os, const A0& a0, const Args& ...args)
////{
////	os << a0;
////	return print_one(os, args...);
////}
////
////template <class ...Args>
////std::ostream&
////print(std::ostream& os, const Args& ...args)
////{
////	return print_one(os, args...);
////}
////
////std::mutex&
////get_cout_mutex()
////{
////	static std::mutex m;
////	return m;
////}
////
////template <class ...Args>
////std::ostream&
////print(const Args& ...args)
////{
////	std::lock_guard<std::mutex> _(get_cout_mutex());
////	return print(std::cout, args...);
////}
////
////
////void exec()
////{
////	print("Hello ", std::this_thread::get_id(), '\n');
////	std::this_thread::sleep_for(std::chrono::milliseconds(100));
////}