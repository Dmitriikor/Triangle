#ifndef POINT_TEST_H__

#define POINT_TEST_H__

#include <iostream>

//!!! два printa, пример в main
//!!! cin << Point
struct Point
{
	double x;
	double y;

	Point() :x(0), y(0) {};
	Point(double x, double y) : x(x), y(y) {};

	void print() const;
	bool operator==(const Point& other) const;
};

struct Dot : public Point
{
	char symbol;

	Dot() :Point(), symbol('.') {};
	Dot(double x, double y, char symbol = '.') : Point(x, y), symbol(symbol) {};

	Dot(const Point& p, char symbol = '.') :Point(p), symbol(symbol) { };

	friend std::ostream& operator<<(std::ostream& out, const Dot& p);
};

double length(const Point& A, const Point& B);



#endif //!POINT_TEST_H__