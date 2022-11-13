#ifndef TRIANGLE_TEST_H__

#define TRIANGLE_TEST_H__

#include <vector> //!!!RAY
#include <fstream>
#include <cmath>
#include "Ray_3_test.h"
#include "Point_test.h"
#include "Is_equal_test.h"

class Triangle {
private:
	struct Side {
		double AB;
		double BC;
		double CA;
	} side;

	Ray_3_ point_in_triangle;

	//std::vector<Point> point_in_triangle;
	size_t dot_counter;
	double area;

	struct Vertex {
		Point a;
		Point b;
		Point c;
	} vertex;

	double count_area() const;

public:
	//Конструктор!!!

const Point& get_point_in(size_t index) const;

//const std::vector<Point>& get_points_inside() const;
const Ray_3_ get_points_inside_Ray() const;

double get_AB() const; 

double get_BC() const;  

double get_CA() const;  

const Point& get_A() const;

const int get_A_X() const;

const int get_A_Y() const;

const Point& get_B() const;

const int get_B_X() const;

const int get_B_Y() const;

const Point& get_C() const;

const int get_C_X() const;

const int get_C_Y() const;

void create(const Point& a, const Point& b, const Point& c); 

size_t get_dot_counter() const; 

void add_point_at_vector(const Point& point);  

double get_area() const; 

bool is_triangle() const; 

void print() const;

void print_to_file(std::ostream& output)const;

void triangles_print_outfile(const Triangle triangle[], size_t index, const std::string& path_out);

Triangle create_triangle(const Point& a, const Point& b, const Point& c);

bool is_inside(const Point& point, const Triangle& abc);

void points_print(const Point p[], int n);
};
#endif //! TRIANGLE_TEST_H__