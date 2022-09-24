#include "Point_test.h"

void Point::print() const {
	std::cout << x << " " << y << "\n";
}

double length(const Point& A, const Point& B) {
	return pow(pow(B.x - A.x, 2) + pow(B.y - A.y, 2), 0.5);  //!!!
}