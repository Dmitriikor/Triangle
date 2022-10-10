#ifndef MATRIX_TEST_H__

#define MATRIX_TEST_H__
#include <string>
using T = std::string;
using pointer_type = T*;


class Matrix {
private:
	size_t N = 0;
	size_t M = 0;
	T** arr = nullptr;

private:
	struct str_i {
		Matrix& my_matrix;
		size_t i;

		str_i(Matrix& m, size_t i) : my_matrix(m), i(i) {
			//str_i::i = i;
		}

		T& operator[](size_t j) /*const*/ {
			return my_matrix.arr[i][j];
		}
	};

	struct const_str_i {
		const Matrix& my_matrix;
		size_t i;

		const_str_i(const Matrix& m, size_t i) : my_matrix(m), i(i) {
			//str_i::i = i;
		}

		const T& operator[](size_t j) const {
			return my_matrix.arr[i][j];
		}
	};

public:
	str_i operator[](size_t i) {
		return str_i(*this, i);
	}

	const_str_i operator[](size_t i) const {
		return const_str_i(*this, i);
	}

	size_t get_N() const;

	size_t get_M() const;

	void create_matrix(size_t strings, size_t columns);

	void set_at(const size_t N, const size_t M, const T& data);

	T& get_at(size_t N, size_t M);

	void clear_matrix();

};

#endif //! MATRIX_TEST_H__

