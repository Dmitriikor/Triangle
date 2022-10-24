#ifndef POINT_TEST_H__

#define POINT_TEST_H__

#include <iostream>

struct Point {
	double x;
	double y;

	void print() const;
	bool operator==(const Point& other) const ;




};

double length(const Point& A, const Point& B);



#endif //!POINT_TEST_H__