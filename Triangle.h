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


class Triangle_low {

protected:
	struct Vertex {
		Dot a;
		Dot b;
		Dot c;
	} vertex;

public:
	const Dot& get_a() const
	{
		return vertex.a;
	}
	const Dot& get_b() const
	{
		return vertex.b;
	}
	const Dot& get_c() const
	{
		return vertex.c;
	}

	//!!! set'еры

	Triangle_low() = default;

	Triangle_low(Dot a, Dot b, Dot c)
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

	Ray <Dot> point_in_triangle;

	//std::vector<Dot> point_in_triangle;

	size_t dot_counter;
	double area;
	bool is_triangle;

	double count_area() const;

public:

	bool is_triangle_() const //!!! is_triangle without '_'
	{
		return is_triangle;
	}

	Triangle_hi() :Triangle_low(), side({ 0, 0, 0 }), dot_counter(0), area(0), is_triangle(0)
	{

	}

	Triangle_hi(Dot a, Dot b, Dot c) : Triangle_low(a, b, c)
	{

		side.AB = length(a, b);
		side.BC = length(b, c);
		side.CA = length(c, a);

		dot_counter = 0;
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

		vertex.a = other.vertex.a;
		vertex.b = other.vertex.b;
		vertex.c = other.vertex.c;

		side.AB = other.side.AB;
		side.BC = other.side.BC;
		side.CA = other.side.CA;

		dot_counter = other.dot_counter;

		int length = other.point_in_triangle.size();

		for (size_t i = 0; i < length; i++)
		{
			point_in_triangle.add_to_back(other.point_in_triangle[i]);
		}

		area = other.area;

		is_triangle = other.is_triangle;

		return *this;
	}

	Triangle_hi& operator = (Triangle_hi&& other)
	{
		if (this == &other)
			return *this;

		vertex.a = other.vertex.a;
		vertex.b = other.vertex.b;
		vertex.c = other.vertex.c;

		side.AB = other.side.AB;
		side.BC = other.side.BC;
		side.CA = other.side.CA;

		dot_counter = other.dot_counter;

		std::swap(point_in_triangle, other.point_in_triangle);

		area = other.area;

		is_triangle = other.is_triangle;

	}



	~Triangle_hi()
	{
		vertex.a.x = 0;
		vertex.a.y = 0;
		vertex.b.x = 0;
		vertex.b.y = 0;
		vertex.c.x = 0;
		vertex.c.y = 0;

		side.AB = 0;
		side.BC = 0;
		side.CA = 0;

		dot_counter = 0;

		area = 0;

		is_triangle = false;
	};




	const Dot& get_point_in(size_t index) const;

	//const std::vector<Dot>& get_points_inside() const;
	 Ray <Dot> get_points_inside_Ray() const;

	double get_AB() const;

	double get_BC() const;

	double get_CA() const;

	const Dot& get_A() const;

	double get_A_X() const;

	 double get_A_Y() const;

	const Dot& get_B() const;

	double get_B_X() const;

	double get_B_Y() const;

	const Dot& get_C() const;

	double get_C_X() const;

	double get_C_Y() const;

	void create(const Dot& a, const Dot& b, const Dot& c);

	size_t get_dot_counter() const;

	void add_point_at_vector(const Dot& point);

	double get_area() const;

	bool is_triangle_check() const;

	void print() const;

	void print_to_file(std::ostream& output)const;

	static void triangles_print_outfile(const Ray<Triangle_hi>& triangle, size_t index, const std::string& path_out);

	Triangle_hi create_triangle(const Dot& a, const Dot& b, const Dot& c) const;

	static bool is_inside(const Dot& point, const Triangle_hi& abc);

	void points_print(const Dot p[], int n)const;

	Ray<Dot> get_point_in_triangle() const;
};
#endif //! TRIANGLE_TEST_H__