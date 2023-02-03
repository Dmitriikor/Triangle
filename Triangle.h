#ifndef TRIANGLE_TEST_H__

#define TRIANGLE_TEST_H__

//#include <vector> //!!!RAY
#include <fstream>
#include <cmath>
#include "Ray.h"
#include "Point.h"
#include "Is_equal_test.h"
#include "utilities.h"
//#include "Ray_3_test.h"


//!!! Dot => Point

class Triangle_low {

protected:
	struct Vertex {
		Point a;
		Point b;
		Point c;
	} vertex;

public:
	const Point& get_a() const
	{
		return vertex.a;
	}
	const Point& get_b() const
	{
		return vertex.b;
	}
	const Point& get_c() const
	{
		return vertex.c;
	}

	//!!! set'еры

	Triangle_low() = default;

	Triangle_low(Point a, Point b, Point c)
	{
		vertex.a = a;
		vertex.b = b;
		vertex.c = c;
	}
};


class Triangle_hi : public Triangle_low
{

private:
	struct Side {
		double AB;
		double BC;
		double CA;
	} side;

	Ray <Point> point_in_triangle;

	//std::vector<Point> point_in_triangle;

	//size_t dot_counter;
	double area;
	bool is_triangle;

	double count_area() const;

public:

	bool is_triangle_() const //!!! is_triangle without '_'
	{
		return is_triangle;
	}

	Triangle_hi() :Triangle_low(), side({ 0, 0, 0 })/*, dot_counter(0)*/, area(0), is_triangle(0)
	{

	}

	Triangle_hi(Point a, Point b, Point c) : Triangle_low(a, b, c)
	{

		side.AB = length(a, b);
		side.BC = length(b, c);
		side.CA = length(c, a);

		/*dot_counter = 0;*/
		area = count_area();

		if ((side.AB + side.BC > side.CA) &&
			(side.AB + side.CA > side.BC) &&
			(side.BC + side.CA > side.AB))
			is_triangle = true;
		else
			is_triangle = false;

	};

	//Triangle_hi(const Triangle_hi& other) //!!! other
	//	: Triangle_low(other), side(other.side), dot_counter(other.dot_counter), point_in_triangle(other.point_in_triangle),
	//	area(other.area), is_triangle(other.is_triangle)
	//{
	//	
	//};

	Triangle_hi(Triangle_hi&& other) = default;

	Triangle_hi& operator = (const Triangle_hi& other)
	{
		if (this == &other)
			return *this;

		vertex = other.vertex;

		side = other.side;

		/*dot_counter = other.dot_counter;*/

		point_in_triangle.clear();

		int length = other.point_in_triangle.size();
		for (size_t i = 0; i < length; i++)
		{
			point_in_triangle.add_to_back(other.point_in_triangle[i]);
		}

		area = other.area;

		is_triangle = other.is_triangle;

		return *this;
	}

	Triangle_hi& operator = (Triangle_hi&& other) = default;

	~Triangle_hi()
	{
		vertex = { {}, {}, {} };

		side = {};

		//dot_counter = 0;

		area = 0;

		is_triangle = false;
	};

	//const std::vector<Point>& get_points_inside() const;
	//Ray <Point> get_points_inside_Ray() const;

	double get_AB() const;

	double get_BC() const;

	double get_CA() const;

	/*const Point& get_a() const;

	double get_A_X() const;

	 double get_A_Y() const;

	const Point& get_b() const;

	double get_B_X() const;

	double get_B_Y() const;

	const Point& get_c() const;

	double get_C_X() const;

	double get_C_Y() const;*/

	//void create(const Point& a, const Point& b, const Point& c);

	const Ray<Point>& get_point_array() const;
	size_t size_point_array() const;

	size_t get_dot_counter() const;

	Point get_point_in(size_t index) const;

	double get_area() const;

	void add_point_at_vector(const Point& point);

	bool is_triangle_check() const;

	bool is_inside(const Point& point) const;

	void print() const;

	void print_to_file(std::ostream& output)const;
};

//Triangle_hi create_triangle(const Point& a, const Point& b, const Point& c) const;

void triangles_print_outfile(const Ray<Triangle_hi>& triangle, size_t index, const std::string& path_out);

#endif //! TRIANGLE_TEST_H__