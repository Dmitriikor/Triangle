#ifndef POINT_TEST_H__

#define POINT_TEST_H__

#include <iostream>

struct Point {
	int x;
	int y;

	void print() const;
};

double length(const Point& A, const Point& B);

#endif //!POINT_TEST_H__