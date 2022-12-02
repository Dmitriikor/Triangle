#include "Matrix_test.h"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_start
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





Matrix::Matrix() : N(0), M(0), arr(nullptr)
{

}


Matrix::Matrix(size_t N, size_t M) : N(N), M(M), arr(nullptr)
{
	if (arr != nullptr)
	{
		resaize(N,M);
	}

	arr = allocate(N, M);
}

void Matrix::resaize(size_t N_, size_t M_)
{
	for (size_t i = 0; i < N; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	arr = allocate(N_, M_);
}

Matrix::Matrix(const Matrix& other) : arr(nullptr)
{
	N = other.N;
	M = other.M;

	if (N != 0 && M != 0)
	{
		arr = allocate(N, M);

		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < M; j++)
			{
				arr[i][j] = other.arr[i][j];
			}
		}
	}
}

Matrix::~Matrix()
{
	clear();
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		clear();

		N = other.N;
		M = other.M;

		arr = allocate(N, M);

		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < M; j++)
			{
				arr[i][j] = other.arr[i][j];
			}
		}
	}

	return *this;
}

Matrix::str_i Matrix::operator[](size_t i) {
	return str_i(*this, i);
}

Matrix::const_str_i Matrix::operator[](size_t i) const {
	return const_str_i(*this, i);
}


T** Matrix::allocate(size_t N_, size_t M_)
{
	
		T** new_arr = new T * [N_]();

		for (size_t i = 0; i < N_; i++) {
			new_arr[i] = new T[M_]();
		}

		return new_arr;
	
}


size_t Matrix::get_N() const {
	return N;
}

size_t Matrix::get_M() const {
	return M;
}

//void Matrix::resize(size_t strings, size_t columns) {
//	if (strings == 0 || columns == 0)
//		throw std::logic_error("logic_error in void create_matrix : strings == 0 or columns == 0 => MATRIX 0x0");
//
//	if (arr == nullptr) {
//		//crt_cntr++;
//		N = strings;
//		M = columns;
//		//std::cout << "\n\t" << "Matrix " << "create" << " N = " << N << " M = " << M << "\n\n\n";
//
//		allocate(N,M);
//	}
//	else {
//		throw std::logic_error("logic_error in void create_matrix : MATRIX ALREADY EXIST");
//		//std::cout << "\n\t\nMATRIX ALREADY EXIST\n\n";
//		//return NULL;
//	}
//	//return arr;
//}

void Matrix::fill(const T& value)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = value;
		}
	}
}

//void Matrix::set_at(size_t i, size_t j, const T& data) {
//	if (i < N && j < M) {
//		if (arr != nullptr)
//			arr[i][j] = data;
//		else {
//			throw std::length_error("length_error in void set_at : NO create_matrix");
//			//std::cout << "\n\n\t NO create_matrix\n\n";
//		}
//	}
//	else {
//		throw std::out_of_range("out_of_range in void set_at : metod N or M > matrix N,M ");
//		//std::cout << "\n\n\t  metod N or M > matrix N,M \n\n";
//	}
//}



void Matrix::set_at(size_t i, size_t j, const T& data) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void set_at : metod i = " + std::to_string(i) + " > matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void set_at : metod j = " + std::to_string(j) + " > matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void set_at : NO create_matrix");

	arr[i][j] = data;
}

void Matrix::set_at(Coordinates cell, const T& data) {
	set_at(cell.i, cell.j, data);
}

T& Matrix::get_at(size_t i, size_t j) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void get_at : metod i = " + std::to_string(i) + " > matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void get_at : metod j = " + std::to_string(j) + " > matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void get_at : NO create_matrix");

	return arr[i][j];
}

T& Matrix::get_at(Coordinates cell) {
	return get_at(cell.i, cell.j);
}

void Matrix::clear() {
	if (arr != nullptr)
	{
		//std::cout << "\n\t" << "~Matrix " << "remove" << " N = " << N << " M = " << M << "\n\n\n";
		//--crt_cntr;
		//if(crt_cntr < 0 )
			//throw std::out_of_range("clear_matrix  crt_cntr < 0");

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

bool Matrix::is_empty()
{
	if (arr == nullptr)
		return true;

	return false;
}

void Matrix::print() const
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
void Matrix::print(std::ofstream& output) const {
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
//Matrix_v1_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
