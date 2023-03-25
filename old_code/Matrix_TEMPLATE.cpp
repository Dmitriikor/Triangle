#include "Matrix_TEMPLATE.h"

template <typename T>
Matrix_TEMPLATE<T>& operator+(Matrix_TEMPLATE<T>& lhs, const Matrix_TEMPLATE<T>& rhs)
{
	lhs += rhs;
	//return lhs;
	return std::move(lhs);
}
