#include "Matrix_test.h"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_start
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t Matrix::get_N() const {
	return N;
}

size_t Matrix::get_M() const {
	return M;
}

void Matrix::create_matrix(size_t strings, size_t columns) {
	if (arr == nullptr) {

		N = strings;
		M = columns;

		arr = new T * [N];
		for (size_t i = 0; i < N; i++) {
			arr[i] = new T[M];
		}
	}
	else {
		throw std::logic_error("logic_error in void create_matrix : MATRIX ALREADY EXIST");
		//std::cout << "\n\t\nMATRIX ALREADY EXIST\n\n";
		//return NULL;
	}
	//return arr;
}

void Matrix::fill(char symbol)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = symbol;
		}
	}
}

void Matrix::set_at(size_t i, size_t j, const T& data) {
	if (i < N && j < M) {
		if (arr != nullptr)
			arr[i][j] = data;
		else {
			throw std::length_error("length_error in void set_at : NO create_matrix");
			//std::cout << "\n\n\t NO create_matrix\n\n";
		}
	}
	else {
		throw std::out_of_range("out_of_range in void set_at : metod N or M > matrix N,M ");
		//std::cout << "\n\n\t  metod N or M > matrix N,M \n\n";
	}
}

void Matrix::set_at(Coordinates cell, const T& data) {
	set_at(cell.i, cell.j, data);
}

T& Matrix::get_at(size_t i, size_t j) {
	if (i < N && j < M) {
		if (arr != nullptr)
			return arr[i][j];
		else {
			throw std::logic_error("logic_error in get_at : NO MATRIX EXIST");
			//std::cout << "\n\t\nMATRIX NO EXIST\n\n";
		}
	}
	else {
		throw std::out_of_range("out_of_range in int get_at : metod N or M > matrix N,M ");
		//std::cout << "\n\n\t  metod N or M > matrix N,M \n\n";
	}
}

T& Matrix::get_at(Coordinates cell) {
	return get_at(cell.i, cell.j);
}

void Matrix::clear_matrix() {
	
	/*for (size_t i = 0; i < N; i++) {
		std::cout << N << " " << M << "\n";
		delete[] arr[i];
	}

	delete[] arr;*/

	for (size_t i = 0; i < N; i++) {
		std::cout << N << " " << M << "\n";
		arr[i] = nullptr;
	}

	arr = nullptr;
	N = 0;
	M = 0;

}

bool Matrix::is_empty()
{
	if (arr == nullptr)
		return true;
	
	return false;
}

void Matrix::Matrix_print()
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
