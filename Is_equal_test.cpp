#include "Is_equal_test.h"

bool isEqual(long double a, long double b, long double eps)
{
	if (std::abs(a - b) <= eps)
		return true;

	return false;
}
