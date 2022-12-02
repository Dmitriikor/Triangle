#ifndef TRIANGLE_TEST_H__

#define TRIANGLE_TEST_H__

#include <vector> //!!!RAY
#include <fstream>
#include <cmath>

#include "Point_test.h"
#include "Is_equal_test.h"
#include "Ray_3_test.h"

class Triangle {
private:
	struct Side {
		double AB;
		double BC;
		double CA;
	} side;

	Ray_3_ point_in_triangle;

	//std::vector<Dot> point_in_triangle;
	size_t dot_counter;
	double area;

	struct Vertex {
		Dot a;
		Dot b;
		Dot c;
	} vertex;

	double count_area() const;

public:
	//Конструктор!!!

const Dot& get_point_in(size_t index) const;

//const std::vector<Dot>& get_points_inside() const;
const Ray_3_ get_points_inside_Ray() const;

double get_AB() const; 

double get_BC() const;  

double get_CA() const;  

const Dot& get_A() const;

const int get_A_X() const;

const int get_A_Y() const;

const Dot& get_B() const;

const int get_B_X() const;

const int get_B_Y() const;

const Dot& get_C() const;

const int get_C_X() const;

const int get_C_Y() const;

void create(const Dot& a, const Dot& b, const Dot& c); 

size_t get_dot_counter() const; 

void add_point_at_vector(const Dot& point);  

double get_area() const; 

bool is_triangle() const; 

void print() const;

void print_to_file(std::ostream& output)const;

void triangles_print_outfile(const Triangle triangle[], size_t index, const std::string& path_out);

Triangle create_triangle(const Dot& a, const Dot& b, const Dot& c);

bool is_inside(const Dot& point, const Triangle& abc);

void points_print(const Dot p[], int n);
};
#endif //! TRIANGLE_TEST_H__