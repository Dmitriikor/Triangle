#ifndef MATRIX_TEMPLATE_H__

#define MATRIX_TEMPLATE_H__

#include <Windows.h>
#include <stdexcept>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

#include <thread>
#include <mutex>




//template <class ...Args>
//std::ostream& printsT(const Args& ...args)
//{
//	std::lock_guard<std::mutex> _(get_cout_mutex());
//	return print(std::cout, args...);
//}


///using T = char;
///using pointer_type = T*;
/// 
 

struct Coordinates_TEMPLATE {
	size_t i;
	size_t j;

};

template <typename T>
class Matrix_TEMPLATE {

public:
	Matrix_TEMPLATE();
	Matrix_TEMPLATE(size_t N, size_t M);
	Matrix_TEMPLATE(size_t N, size_t M, const T& value);
	Matrix_TEMPLATE(const Matrix_TEMPLATE& other);

	Matrix_TEMPLATE(Matrix_TEMPLATE&& other);
	Matrix_TEMPLATE& operator=(Matrix_TEMPLATE&& other);

	~Matrix_TEMPLATE();

	Matrix_TEMPLATE& operator=(const Matrix_TEMPLATE& other);

	size_t get_N() const;

	size_t get_M() const;

	void resize(size_t N_, size_t M_);
	void resize(size_t strings, size_t columns, const T& value);
	void resize_and_override(size_t N_, size_t M_, const T& value);

	void fill(const T& value);
	bool is_empty();

	void print();
	void print(std::ofstream& output) const;
	void print(std::ostream& output) const;

	void set_at(const size_t N, const size_t M, const T& data);
	void set_at(Coordinates cell, const T& data);

	T& get_at(size_t N, size_t M);
	T& get_at(Coordinates cell);

	const T& get_at(size_t N, size_t M) const;
	const T& get_at(Coordinates cell) const;

	void clear();

private:
	size_t N;
	size_t M;
	T** arr;
	static T** allocate(size_t N, size_t M);

	struct str_i {
		Matrix_TEMPLATE& my_matrix;
		size_t i;

		str_i(Matrix_TEMPLATE& m, size_t i) : my_matrix(m), i(i) {
		}

		T& operator[](size_t j) {
			return my_matrix.arr[i][j];
		}
	};
	struct const_str_i {
		const Matrix_TEMPLATE& my_matrix;
		size_t i;

		const_str_i(const Matrix_TEMPLATE& m, size_t i) : my_matrix(m), i(i) {
		}

		const T& operator[](size_t j) const {
			return my_matrix.arr[i][j];
		}
	};

	std::thread* DefenseThread;
	//mutable;
	//static std::mutex lockit;
	mutable std::mutex m;
	std::mutex& get_cout_mutex();
	//std::thread* DefenseThread;
	void  do_something();

public:

	str_i operator[](size_t i);
	const_str_i operator[](size_t i) const;

	///!!! operator+=
	///!!! return Matrix_TEMPLATE <T> operator +
	///!!!� constructor std::move()
	///!!!� operator std::move()
	///!!! void Matrix_TEMPLATE<T>::print(std::ostream& output) const

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_start
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::mutex& Matrix_TEMPLATE<T>::get_cout_mutex()
{
	static std::mutex m;
	return m;
}



template <typename T>
Matrix_TEMPLATE<T>::Matrix_TEMPLATE() : N(0), M(0), arr(nullptr)
{

}

template <typename T>
Matrix_TEMPLATE<T>::Matrix_TEMPLATE(size_t N, size_t M) : N(N), M(M)
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
inline Matrix_TEMPLATE<T>::Matrix_TEMPLATE(size_t N, size_t M, const T& value) : N(N), M(M)
{
	if (N == 0 || M == 0)
	{
		//!!!set_empty
		N = M = 0;
		arr = nullptr;
		return;
	}

	arr = allocate(N, M);
	fill(value);
}

template <typename T>
void Matrix_TEMPLATE<T>::resize_and_override(size_t N_, size_t M_, const T& value)
{
	resize(N_, M_);
	fill(value);
}

template <typename T>
void Matrix_TEMPLATE<T>::resize(size_t N_, size_t M_, const T& value)
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

	for (size_t i = 0; i < min_N_lim; i++)
		for (size_t j = 0; j < min_M_lim; j++) {
			std::lock_guard<std::mutex> _(get_cout_mutex());
			new_arr[i][j] = arr[i][j];
		}


	for (size_t i = 0; i < N_; i++)
	{
		for (size_t j = 0; j < M_; j++) 
		{
			if (new_arr[i][j] == T())
			{
				std::lock_guard<std::mutex> _(get_cout_mutex());
				new_arr[i][j] = value;
			}
		}


	}

	clear();
	N = N_;
	M = M_;
	arr = new_arr;
}

template <typename T>
void Matrix_TEMPLATE<T>::resize(size_t N_, size_t M_)
{
	if (N == N_ && M == M_)
		return;

	if (N_ == 0 || M_ == 0)
	{
		clear();
		return;
	}
	std::lock_guard<std::mutex> _(get_cout_mutex());
	T** new_arr;
	new_arr = allocate(N_, M_);

	int min_N_lim = (N_ < N) ? N_ : N;
	int min_M_lim = (M_ < M) ? M_ : M;

	for (size_t i = 0; i < min_N_lim; i++)
		for (size_t j = 0; j < min_M_lim; j++)
			new_arr[i][j] = arr[i][j];

	clear();
	N = N_;
	M = M_;
	arr = new_arr;
}

template <typename T>
Matrix_TEMPLATE<T>::Matrix_TEMPLATE(const Matrix_TEMPLATE<T>& other) : N(other.N), M(other.M)
{
	if (N == 0)
	{
		arr = nullptr;
		return;
	}

	arr = allocate(N, M);
	//!!! copy-function
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = other.arr[i][j];
		}
	}
}


template<typename T>
Matrix_TEMPLATE<T>::Matrix_TEMPLATE(Matrix_TEMPLATE&& other)
{
	std::swap(N, other.N);
	std::swap(M, other.M);

	clear();

	std::swap(arr, other.arr);
}

template<typename T>
inline Matrix_TEMPLATE<T>& Matrix_TEMPLATE<T>::operator=(Matrix_TEMPLATE&& other)
{
	std::swap(N, other.N);
	std::swap(M, other.M);

	clear();

	std::swap(arr, other.arr);


	return *this;
}

template <typename T>
Matrix_TEMPLATE<T>::~Matrix_TEMPLATE()
{
	std::lock_guard<std::mutex> _(get_cout_mutex());
	std::cout << "\n Exit DefenseThread is : " << DefenseThread->get_id() << "\n";
	DefenseThread->join();
	clear();
}

template <typename T>
Matrix_TEMPLATE<T>& Matrix_TEMPLATE<T>::operator=(const Matrix_TEMPLATE<T>& other)
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

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = other.arr[i][j];
		}
	}

	return *this;
}

template <typename T>
typename Matrix_TEMPLATE<T>::str_i Matrix_TEMPLATE<T>::operator[](size_t i) {
	return str_i(*this, i);
}

template <typename T>
typename Matrix_TEMPLATE<T>::const_str_i Matrix_TEMPLATE<T>::operator[](size_t i) const {
	return const_str_i(*this, i);
}

template <typename T>
T** Matrix_TEMPLATE<T>::allocate(size_t N_, size_t M_)
{
	T** new_arr = new T * [N_]();

	for (size_t i = 0; i < N_; i++) {
		new_arr[i] = new T[M_]();
	}

	return new_arr;
}

template <typename T>
size_t Matrix_TEMPLATE<T>::get_N() const {
	return N;
}

template <typename T>
size_t Matrix_TEMPLATE<T>::get_M() const {
	return M;
}

template <typename T>
void Matrix_TEMPLATE<T>::fill(const T& value)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = value;
		}
	}
}

template <typename T>
void Matrix_TEMPLATE<T>::set_at(size_t i, size_t j, const T& data) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void set_at : method i = " + std::to_string(i) + " > matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void set_at : method j = " + std::to_string(j) + " > matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void set_at : NO create_matrix");

	arr[i][j] = data;
}

template <typename T>
void Matrix_TEMPLATE<T>::set_at(Coordinates cell, const T& data) {
	set_at(cell.i, cell.j, data);
}

template <typename T>
T& Matrix_TEMPLATE<T>::get_at(size_t i, size_t j) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void get_at : method i = " + std::to_string(i) + " > matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void get_at : method j = " + std::to_string(j) + " > matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void get_at : NO create_matrix");

	return arr[i][j];
}

template <typename T>
T& Matrix_TEMPLATE<T>::get_at(Coordinates cell) {
	return get_at(cell.i, cell.j);
}

template <typename T>
const T& Matrix_TEMPLATE<T>::get_at(size_t i, size_t j) const {
	if (i >= N)
		throw std::out_of_range("out_of_range in void get_at : method i = " + std::to_string(i) + " > matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void get_at : method j = " + std::to_string(j) + " > matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void get_at : NO create_matrix");

	return arr[i][j];
}

template <typename T>
const T& Matrix_TEMPLATE<T>::get_at(Coordinates cell) const {
	return get_at(cell.i, cell.j);
}

template <typename T>
void Matrix_TEMPLATE<T>::clear() {
	if (arr != nullptr)
	{
		for (size_t i = 0; i < N; i++) {
			delete[] arr[i];
		}
		delete[] arr;

		arr = nullptr;
		N = 0;
		M = 0;
	}
}

template <typename T>
bool Matrix_TEMPLATE<T>::is_empty()
{
	if (arr == nullptr)
		return true;

	return false;
}


//std::mutex Matrix_TEMPLATE<T>::lockit;







template <typename T>
void Matrix_TEMPLATE<T>::do_something()
{
	//printsT("Hello enter", std::this_thread::get_id(), '\n');

	std::lock_guard<std::mutex> _(get_cout_mutex());
	std::cout << "\n Enter DefenseThread is : " << DefenseThread->get_id() << "\n";
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < M; j++)
			{
				std::cout << arr[i][j];
			}
			std::cout << "\n";
		}
}

#include "windows.h" 
#include "Windows.h" 

template <typename T>
void Matrix_TEMPLATE<T>::print()
{
	//std::lock_guard<std::mutex> lockit(std::mutex);

	//Sleep(1000);

	DefenseThread = new std::thread(&Matrix_TEMPLATE<T>::do_something, this);

	


	/*
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			std::cout << arr[i][j];
		}
		std::cout << "\n";
	}
	*/
}

//template <typename T>
//void Matrix_TEMPLATE<T>::print(std::ofstream& output) const
//{
//	for (size_t i = 0; i < N; i++)
//	{
//		for (size_t j = 0; j < M; j++)
//		{
//			output << arr[i][j];
//		}
//		output << "\n";
//	}
//}




template<typename T>
inline void Matrix_TEMPLATE<T>::print(std::ostream& output) const
{


	///thr = std::move(std::thread{do_something});


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //! MATRIX_TEMPLATE_H__
