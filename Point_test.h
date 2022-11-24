#ifndef POINT_TEST_H__

#define POINT_TEST_H__

#include <iostream>

struct Point
{
	double x = 0;
	double y = 0;

	void print() const;
	bool operator==(const Point& other) const;
};

struct Dot : public Point
{
	//Dot() {} //!!! ������ ���� ����
	//Dot(const Point& p) :Point(p) { } //!!! ������ ���� ����

	char symbol = '.';
};

double length(const Point& A, const Point& B);



#endif //!POINT_TEST_H__