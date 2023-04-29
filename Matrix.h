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
class Matrix {
private:
	//struct str_i {
	//	Matrix& my_Matrix_TEMPLATE;
	//	size_t i;
	//	str_i(Matrix& m, size_t i) : my_Matrix_TEMPLATE(m), i(i) {
	//	}
	//	T& operator[](size_t j) {
	//		return my_Matrix_TEMPLATE.arr[i][j];
	//	}
	//};
	//struct const_str_i {
	//	const Matrix& my_Matrix_TEMPLATE;
	//	size_t i;
	//	const_str_i(const Matrix& m, size_t i) : my_Matrix_TEMPLATE(m), i(i) {
	//	}
	//	const T& operator[](size_t j) const {
	//		return my_Matrix_TEMPLATE.arr[i][j];
	//	}
	//};

	struct str_i {
			Matrix& my_Matrix_TEMPLATE;
			size_t i;
			str_i(Matrix& m, size_t i) : my_Matrix_TEMPLATE(m), i(i) {
			}
			T& operator[](size_t j) {
				return my_Matrix_TEMPLATE.arr[i][j];
			}

		//!!!по строке можно проходить == итерироваться, т.е.ей нужен свой итератор
		class iterator
		{
			friend class str_i;
			T* ptr;
		public:
			using value_type = T;
			using pointer = T*;
			using reference = T&;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::random_access_iterator_tag;

			iterator(T* p) : ptr(p)
			{
			}
			reference operator*() const
			{
				return *ptr;
			}
			pointer operator->() const
			{
				return ptr;
			}
			iterator& operator++()
			{
				++ptr;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp(*this);
				++ptr; return tmp;
			}
			iterator& operator+=(difference_type n)
			{
				ptr += n;
				return *this;
			}
			bool operator==(iterator other) const
			{
				return ptr == other.ptr;
			}
		};
		iterator begin() { return iterator(my_Matrix_TEMPLATE.arr[i]); }
		iterator end() { return iterator(my_Matrix_TEMPLATE.arr[i] + my_Matrix_TEMPLATE.M); }

	};

	struct const_str_i 
	{
		const Matrix& my_Matrix_TEMPLATE;
		size_t i;
		const_str_i(const Matrix& m, size_t i) : my_Matrix_TEMPLATE(m), i(i) {
		}
		const T& operator[](size_t j) const {
			return my_Matrix_TEMPLATE.arr[i][j];
		}

		 const class iterator
		{
			friend class str_i;
			const T* ptr;
		public:
			using value_type = T;
			using pointer = const T*;
			using reference = const T&;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::random_access_iterator_tag;

			iterator(const T* p) : ptr(p) {}

			const reference operator*() const
			{
				return *ptr;
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
			iterator& operator--()
			{
				--ptr;
				return *this;
			}
			const iterator operator++(int) const
			{
				iterator tmp(*this);
				++ptr;
				return tmp;
			}
			const iterator operator--(int) const
			{
				iterator tmp(*this);
				--ptr;
				return tmp;
			}
			iterator& operator+=(difference_type n)
			{
				ptr += n;
				return *this;
			}
			iterator& operator-=(difference_type n)
			{
				ptr -= n;
				return *this;
			}
			bool operator==(const iterator other) const
			{
				return ptr == other.ptr;
			}
		};
		const iterator begin() const
		{
			return iterator(my_Matrix_TEMPLATE.arr[i]);
		}
		const iterator end() const
		{
			return iterator(my_Matrix_TEMPLATE.arr[i] + my_Matrix_TEMPLATE.M);
		}
	};

public:
	//!!! ПО СТРОКАМ, Т.Е. "УКАЗЫВАЕТ" НА СТРОКУ
	class iterator {
	public:
		//using value_type = T;
		//using reference = T&;
		//using pointer = T*;
		//using difference_type = std::ptrdiff_t;
		//using iterator_category = std::forward_iterator_tag; //!!! однажды поменять
		//iterator(T* str, int M)
		//{
		//	str_i(str, M);
		//	//saved_ptr_ = matrix;
		//}
		iterator(Matrix<T>* matrix, size_t index) : matrix_(matrix), index_(index)
		{
			//saved_ptr_ = matrix;
		}
		T& operator*() const 
		{
			int t1 = *(matrix_->arr[index_ / matrix_->M]);
			int t2 = index_ % matrix_->M;
			int t3 = t1 + t2;
			//std::cout << "\nint t1 = " << t1 << "; int t2 = " << t2 << "; int t3 = " << t3 << "; index_ = "<< index_ << "; \n";
			return *(matrix_->arr[index_ / matrix_->M] + index_ % matrix_->M);
		}
		iterator& operator++()
		{
			++index_;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++(*this);
			return temp;
		}
		bool operator==(const iterator& other) const {
			return (matrix_ == other.matrix_) && (index_ == other.index_);
		}
		/*
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}
		*/
		//size_t rows() const { return matrix_->get_M(); }
		//size_t cols() const { return matrix_->get_N(); }
	private:
		Matrix<T>* matrix_;
		//Matrix<T>* saved_ptr_;
		size_t index_;
	};
	iterator begin() { return iterator(this, 0); }
	//iterator begin() { return iterator(arr[0], M); }
	iterator end() { return iterator(this, N*M); }

//class m_iterator 
//{
//	private:
//		size_t i;
//		size_t j;
//		Matrix<T>& m;
//	public:
//		m_iterator(size_t i, size_t j, Matrix<T>& m) : i(i), j(j), m(m) 
//		{
//		}
//		bool operator==(const m_iterator& other) const 
//		{
//			return (i == other.i) && (j == other.j);
//		}
//		bool operator!=(const m_iterator& other) const 
//		{
//			return !(*this == other);
//		}
//		T& operator*() 
//		{
//			return m.arr[i][j];
//		}
//		m_iterator& operator++() 
//		{
//			if (j == m.M - 1) {
//				i++;
//				j = 0;
//			}
//			else {
//				j++;
//			}
//			return *this;
//		}
//};
//m_iterator begin() {return m_iterator(0, 0, *this);}
//m_iterator end() {return m_iterator(N, 0, *this);}



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
	return str_i(*this, i);
}

template <typename T>
typename Matrix<T>::const_str_i Matrix<T>::operator[](size_t i) const {
	return const_str_i(*this, i);
}

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