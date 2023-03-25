#include "Matrix_TEMPLATE.h"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_TEMPLATE_v1_start
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





Matrix_TEMPLATE::Matrix_TEMPLATE() : N(0), M(0), arr(nullptr)
{

}

Matrix_TEMPLATE::Matrix_TEMPLATE(size_t N, size_t M) : N(N), M(M)
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

void Matrix_TEMPLATE::resize(size_t N_, size_t M_)
{
	T** new_arr;
	new_arr = allocate(N_, M_);

	int min_N_lim = N;
	if (N_ < N) min_N_lim = N_;
	int min_M_lim = M;
	if (M_ < M) min_M_lim = M_;

	std::cout << "\n";
	for (size_t i = 0; i < min_N_lim; i++)
	{

		for (size_t j = 0; j < min_M_lim; j++)
		{
			new_arr[i][j] = arr[i][j];

		}
	}
	clear();
	N = N_;
	M = M_;
	arr = new_arr;
}



//Matrix_TEMPLATE::Matrix_TEMPLATE(size_t N_, size_t M_)
//{
//	arr = resize_and_save(N_, M_);
//	N = N_;
//	M = M_;
//	
//}
//
//
//T** Matrix_TEMPLATE::resize_and_save( size_t N_, size_t M_)
//{
//	int old_N = N;
//	int old_M = M;
//	T** new_arr = allocate(N_, M_);
//	for (size_t i = 0; i < old_N; i++)
//	{
//		for (size_t j = 0; j < old_M; j++) 
//		{
//
//		}
//	}
//	 
//
//}

Matrix_TEMPLATE::Matrix_TEMPLATE(const Matrix_TEMPLATE& other) : N(other.N), M(other.M)
{
	if (N == 0) // && M == 0 или other.arr == nullptr
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

Matrix_TEMPLATE::~Matrix_TEMPLATE()
{
	clear();
}

Matrix_TEMPLATE& Matrix_TEMPLATE::operator=(const Matrix_TEMPLATE& other)
{
	if (this != &other)
	{
		clear();

		if (other.arr != nullptr)
		{
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
		}
	}

	return *this;
}

Matrix_TEMPLATE::str_i Matrix_TEMPLATE::operator[](size_t i) {
	return str_i(*this, i);
}

Matrix_TEMPLATE::const_str_i Matrix_TEMPLATE::operator[](size_t i) const {
	return const_str_i(*this, i);
}


T** Matrix_TEMPLATE::allocate(size_t N_, size_t M_)
{
	T** new_arr = new T * [N_]();

	for (size_t i = 0; i < N_; i++) {
		new_arr[i] = new T[M_]();
	}

	return new_arr;
}


size_t Matrix_TEMPLATE::get_N() const {
	return N;
}

size_t Matrix_TEMPLATE::get_M() const {
	return M;
}

//void Matrix_TEMPLATE::resize(size_t strings, size_t columns) {
//	if (strings == 0 || columns == 0)
//		throw std::logic_error("logic_error in void create_Matrix_TEMPLATE : strings == 0 or columns == 0 => Matrix_TEMPLATE 0x0");
//
//	if (arr == nullptr) {
//		//crt_cntr++;
//		N = strings;
//		M = columns;
//		//std::cout << "\n\t" << "Matrix_TEMPLATE " << "create" << " N = " << N << " M = " << M << "\n\n\n";
//
//		allocate(N,M);
//	}
//	else {
//		throw std::logic_error("logic_error in void create_Matrix_TEMPLATE : Matrix_TEMPLATE ALREADY EXIST");
//		//std::cout << "\n\t\nMatrix_TEMPLATE ALREADY EXIST\n\n";
//		//return NULL;
//	}
//	//return arr;
//}

void Matrix_TEMPLATE::fill(const T& value)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = value;
		}
	}
}

//void Matrix_TEMPLATE::set_at(size_t i, size_t j, const T& data) {
//	if (i < N && j < M) {
//		if (arr != nullptr)
//			arr[i][j] = data;
//		else {
//			throw std::length_error("length_error in void set_at : NO create_Matrix_TEMPLATE");
//			//std::cout << "\n\n\t NO create_Matrix_TEMPLATE\n\n";
//		}
//	}
//	else {
//		throw std::out_of_range("out_of_range in void set_at : metod N or M > Matrix_TEMPLATE N,M ");
//		//std::cout << "\n\n\t  metod N or M > Matrix_TEMPLATE N,M \n\n";
//	}
//}



void Matrix_TEMPLATE::set_at(size_t i, size_t j, const T& data) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void set_at : metod i = " + std::to_string(i) + " > Matrix_TEMPLATE N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void set_at : metod j = " + std::to_string(j) + " > Matrix_TEMPLATE M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void set_at : NO create_Matrix_TEMPLATE");

	arr[i][j] = data;
}

void Matrix_TEMPLATE::set_at(Coordinates_TEMPLATE cell, const T& data) {
	set_at(cell.i, cell.j, data);
}

T& Matrix_TEMPLATE::get_at(size_t i, size_t j) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void get_at : metod i = " + std::to_string(i) + " > Matrix_TEMPLATE N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void get_at : metod j = " + std::to_string(j) + " > Matrix_TEMPLATE M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void get_at : NO create_Matrix_TEMPLATE");

	return arr[i][j];
}

T& Matrix_TEMPLATE::get_at(Coordinates_TEMPLATE cell) {
	return get_at(cell.i, cell.j);
}

void Matrix_TEMPLATE::clear() {
	if (arr != nullptr)
	{
		//std::cout << "\n\t" << "~Matrix_TEMPLATE " << "remove" << " N = " << N << " M = " << M << "\n\n\n";
		//--crt_cntr;
		//if(crt_cntr < 0 )
			//throw std::out_of_range("clear_Matrix_TEMPLATE  crt_cntr < 0");

		/*for (size_t i = 0; i < N; i++) {
			arr[i] = nullptr;
		}
		arr = nullptr;*/
		//Sleep(10000);
		//std::cout << "\n\t" << "crt_cntr = " << crt_cntr << " N = " << N << " M = " << M << "\n\n\n";
		//print();

		for (size_t i = 0; i < N; i++) {
			delete[] arr[i];
		}

		delete[] arr;

		arr = nullptr;
		N = 0;
		M = 0;
	}
}

bool Matrix_TEMPLATE::is_empty()
{
	if (arr == nullptr)
		return true;

	return false;
}

void Matrix_TEMPLATE::print() const
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			std::cout << arr[i][j];

		}
		std::cout << "\n";
	}
}

void Matrix_TEMPLATE::print(std::ofstream& output) const 
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			output << arr[i][j];

		}
		output << "\n";
	}

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_TEMPLATE_v1_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
