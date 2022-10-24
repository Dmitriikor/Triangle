#include "Point_test.h"

void Point::print() const {
	std::cout << x << " " << y << "\n";
}

double length(const Point& A, const Point& B) {
	return pow(pow(B.x - A.x, 2) + pow(B.y - A.y, 2), 0.5);  //!!!
}

bool Point_isEqual(double a, double b) {
	const double eps = 1e-5;
	if (abs(a - b) <= eps)
		return true;
	return false;
}

bool Point::operator==(const Point& other) const {
	if (Point_isEqual(x, other.x) && Point_isEqual(y, other.y))
		return true;
	return false;
}



/*


#include <iostream>
#include <cmath>

class Point {
public:
	Point() :Point(0, 0) { }

	Point(int x, int y) { ++counter; set_x_y(x, y);  }

	~Point() { --counter; }

	int print() const {
		std::cout << x << " " << y << std::endl;
	}

	//статический метод - метод работы со статическими данными
	static int get_counter() {
		return counter;
	}
	//статический метод: как бы свободная функция внутри класса
	static void print_type() {
		std::cout << "Point 2D with counter." << std::endl;
	}

	//.h
	friend std::ostream& operator<<(std::ostream& out, const Point& p);
	friend std::istream& operator>>(std::istream& in, Point& p);

	void set_x_y(int x, int y) {
		Point::x = x;
		Point::y = y;

		length = pow(pow(x, 2) + pow(y, 2), 0.5);
	}

private:
	static int counter;

	int x, y;
	double length;

public:
	bool operator<(const Point& other) const;
	bool operator>(const Point& other) const;
	bool operator<=(const Point& other) const;
	bool operator>=(const Point& other) const;

	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;

};


bool Point::operator<(const Point& other) const {
	if (this->length < other.length)
		return true;
	return false;
}

bool Point::operator>(const Point& other) const {
	return other < *this;
}

bool Point::operator<=(const Point& other) const {
	return !(*this > other);
}

bool Point::operator>=(const Point& other) const {
	return !(*this < other);
}

bool Point::operator==(const Point& other) const {
	return !(*this < other) && !(*this > other);
}

bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}



//.cpp
int Point::counter = 0;



//.cpp

std::ostream& operator<<(std::ostream& out, const Point& p) {
	out << "(" << p.x << "; " << p.y << ")" << std::endl;
	out << "all = " << Point::counter << std::endl;

	return out;
}

//.cpp
std::istream& operator>>(std::istream& in, Point& p) {
	in >> p.x >> p.y;

	return in;
}


int main() {
	Point p1(1, 1), p2(-2, -2);

	std::cout << (p1 == p2);

	return 0;
}


*/