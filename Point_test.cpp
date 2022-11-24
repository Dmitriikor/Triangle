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

class Dot {
public:
	Dot() :Dot(0, 0) { }

	Dot(int x, int y) { ++counter; set_x_y(x, y);  }

	~Dot() { --counter; }

	int print() const {
		std::cout << x << " " << y << std::endl;
	}

	//статический метод - метод работы со статическими данными
	static int get_counter() {
		return counter;
	}
	//статический метод: как бы свободная функция внутри класса
	static void print_type() {
		std::cout << "Dot 2D with counter." << std::endl;
	}

	//.h
	friend std::ostream& operator<<(std::ostream& out, const Dot& p);
	friend std::istream& operator>>(std::istream& in, Dot& p);

	void set_x_y(int x, int y) {
		Dot::x = x;
		Dot::y = y;

		length = pow(pow(x, 2) + pow(y, 2), 0.5);
	}

private:
	static int counter;

	int x, y;
	double length;

public:
	bool operator<(const Dot& other) const;
	bool operator>(const Dot& other) const;
	bool operator<=(const Dot& other) const;
	bool operator>=(const Dot& other) const;

	bool operator==(const Dot& other) const;
	bool operator!=(const Dot& other) const;

};


bool Dot::operator<(const Dot& other) const {
	if (this->length < other.length)
		return true;
	return false;
}

bool Dot::operator>(const Dot& other) const {
	return other < *this;
}

bool Dot::operator<=(const Dot& other) const {
	return !(*this > other);
}

bool Dot::operator>=(const Dot& other) const {
	return !(*this < other);
}

bool Dot::operator==(const Dot& other) const {
	return !(*this < other) && !(*this > other);
}

bool Dot::operator!=(const Dot& other) const {
	return !(*this == other);
}



//.cpp
int Dot::counter = 0;



//.cpp

std::ostream& operator<<(std::ostream& out, const Dot& p) {
	out << "(" << p.x << "; " << p.y << ")" << std::endl;
	out << "all = " << Dot::counter << std::endl;

	return out;
}

//.cpp
std::istream& operator>>(std::istream& in, Dot& p) {
	in >> p.x >> p.y;

	return in;
}


int main() {
	Dot p1(1, 1), p2(-2, -2);

	std::cout << (p1 == p2);

	return 0;
}


*/