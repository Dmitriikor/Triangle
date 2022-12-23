#ifndef TRIANGLE_TEST_H__

#define TRIANGLE_TEST_H__

//#include <vector> //!!!RAY
#include <fstream>
#include <cmath>
#include "Ray_template.h"
#include "Point_test.h"
#include "Is_equal_test.h"
//#include "Ray_3_test.h"


class Triangle_low {

protected:
	struct Vertex {
		Dot a;
		Dot b;
		Dot c;
	} vertex;

public:
	Dot& get_a()
	{
		return vertex.a;
	}
	Dot& get_b()
	{
		return vertex.b;
	}
	Dot& get_c()
	{
		return vertex.c;
	}

	//Triangle_low()
	//{

	//}

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

	Ray_template <Dot> point_in_triangle;

	Ray_template <int> ppoint;

	//std::vector<Dot> point_in_triangle;

	size_t dot_counter;
	double area;
	bool is_treangle;



	double count_area() const;

public:
	bool is_treangle_()
	{
		return is_treangle;
	}

	//Triangle_hi()
	//{

	//};

	Triangle_hi(Dot a, Dot b, Dot c) : Triangle_low(a,b,c)
	{
		/*vertex.a = a;
		vertex.b = b;
		vertex.c = c;*/

		side.AB = length(a, b);
		side.BC = length(b, c);
		side.CA = length(c, a);

		dot_counter = 0;
		area = count_area();
		point_in_triangle.clear();


		if ((side.AB + side.BC > side.CA) &&
			(side.AB + side.CA > side.BC) &&
			(side.BC + side.CA > side.AB))
			is_treangle = true;
		else
			is_treangle = false;

	};

	Triangle_hi(const Triangle_hi &other_) : Triangle_low(other_.vertex.a, other_.vertex.b, other_.vertex.c)
	{
		if (this == &other_)
			return;

		/*vertex.a = other_.vertex.a;
		vertex.b = other_.vertex.b;
		vertex.c = other_.vertex.c;*/

		side.AB = other_.side.AB;
		side.BC = other_.side.BC;
		side.CA = other_.side.CA;

		dot_counter = other_.dot_counter;

		int length = other_.point_in_triangle.size();

		for (size_t i = 0; i < length; i++)
		{
			point_in_triangle.add_to_back(other_.point_in_triangle[i]);
		}

		area = other_.area;

		is_treangle = other_.is_treangle;

	};

	Triangle_hi& operator = (const Triangle_hi& other_)
	{
		if (this == &other_)
			return *this;

		vertex.a = other_.vertex.a;
		vertex.b = other_.vertex.b;
		vertex.c = other_.vertex.c;

		side.AB = other_.side.AB;
		side.BC = other_.side.BC;
		side.CA = other_.side.CA;

		dot_counter = other_.dot_counter;

		int length = other_.point_in_triangle.size();

		for (size_t i = 0; i < length; i++)
		{
			point_in_triangle.add_to_back(other_.point_in_triangle[i]);
		}

		area = other_.area;

		is_treangle = other_.is_treangle;

	}

	Triangle_hi(Triangle_hi&& other_) : Triangle_low(other_.vertex.a, other_.vertex.b, other_.vertex.c)
	{
		if (this == &other_)
			return;

		/*vertex.a = other_.vertex.a;
		vertex.b = other_.vertex.b;
		vertex.c = other_.vertex.c;*/

		side.AB = other_.side.AB;
		side.BC = other_.side.BC;
		side.CA = other_.side.CA;

		dot_counter = other_.dot_counter;
		area = other_.area;

		point_in_triangle = other_.point_in_triangle;
		other_.point_in_triangle = nullptr;

		is_treangle = other_.is_treangle;

	};





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
		point_in_triangle.clear();

		area = 0;

		is_treangle = false;
	};

const Dot& get_point_in(size_t index) const;

//const std::vector<Dot>& get_points_inside() const;
const Ray_template <Dot> get_points_inside_Ray() const;

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

static void triangles_print_outfile(const Triangle_hi triangle[], size_t index, const std::string& path_out);

Triangle_hi create_triangle(const Dot& a, const Dot& b, const Dot& c);

bool is_inside(const Dot& point, const Triangle_hi& abc);

void points_print(const Dot p[], int n);
};
#endif //! TRIANGLE_TEST_H__