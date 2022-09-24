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
				arr[i] = new T[M]();
			}
		}
		else {
			throw std::logic_error("logic_error in void create_matrix : MATRIX ALREADY EXIST");
			//std::cout << "\n\t\nMATRIX ALREADY EXIST\n\n";
			//return NULL;
		}
		//return arr;
	}

	void Matrix::set_at(const size_t N, const size_t M, const T& data) {
		if (N <= this->N && M <= this->M) {
			if (arr != nullptr)
				arr[N][M] = data;
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

	T& Matrix::get_at(size_t N, size_t M) {
		if (N <= this->N && M <= this->M) {
			if (arr != nullptr)
				return arr[N][M];
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

	void Matrix::clear_matrix() {

		for (size_t i = 0; i < N; i++) {
			delete[] arr[i];
		}

		delete[] arr;

		arr = nullptr;
		N = 0;
		M = 0;

	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
