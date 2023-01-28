#include "Triangle.h"

const Dot& Triangle_hi::get_point_in(size_t index) const {
	return point_in_triangle[index];
}

Ray <Dot> Triangle_hi::get_points_inside_Ray() const {
	return point_in_triangle;
}

////const std::vector<Dot>& Triangle_hi::get_points_inside() const {
////	return point_in_triangle;
////}

double Triangle_hi::get_AB() const {
	return side.AB;
}

double Triangle_hi::get_BC() const {
	return side.BC;
}

double Triangle_hi::get_CA() const {
	return side.CA;
}


const Dot& Triangle_hi::get_A() const {
	return vertex.a;
}

 double Triangle_hi::get_A_X() const {
	return vertex.a.x;
}

 double Triangle_hi::get_A_Y() const {
	return vertex.a.y;
}

const Dot& Triangle_hi::get_B() const {
	return vertex.b;
}

double Triangle_hi::get_B_X() const {
	return vertex.b.x;
}
double Triangle_hi::get_B_Y() const {
	return vertex.b.y;
}

const Dot& Triangle_hi::get_C() const {
	return vertex.c;
}

double Triangle_hi::get_C_X() const {
	return vertex.c.x;
}
double Triangle_hi::get_C_Y() const {
	return vertex.c.y;
}

void Triangle_hi::create(const Dot& a, const Dot& b, const Dot& c) {
	vertex.a = a;
	vertex.b = b;
	vertex.c = c;

	side.AB = length(a, b);
	side.BC = length(b, c);
	side.CA = length(c, a);

	dot_counter = 0;
	point_in_triangle.clear();

	area = count_area();
}

size_t Triangle_hi::get_dot_counter() const {
	return (*this).dot_counter;
}

void Triangle_hi::add_point_at_vector(const Dot& point) {
	point_in_triangle.push_back(point);
	dot_counter += 1;
}

double Triangle_hi::get_area() const {
	return (*this).area;
}


bool Triangle_hi::is_triangle_check() const {
	if ((side.AB + side.BC > side.CA) &&
		(side.AB + side.CA > side.BC) &&
		(side.BC + side.CA > side.AB))
		return true;

	return false;
}


void Triangle_hi::print() const {
	print_to_file(std::cout);
}

void Triangle_hi::print_to_file(std::ostream& output) const {
	output << "\ntriangle.a = ";
	output << vertex.a.x << " " << vertex.a.y << "\n";
	output << "triangle.b = ";
	output << vertex.b.x << " " << vertex.b.y << "\n";
	output << "triangle.c = ";
	output << vertex.c.x << " " << vertex.c.y << "\n";
	output << "dot_counter =\t" << this->dot_counter - 3 << std::endl;
	output << "lengthAB =\t" << this->side.AB << std::endl;
	output << "lengthBC =\t" << this->side.BC << std::endl;
	output << "lengthCA =\t" << this->side.CA << std::endl;
	output << "triangle_area =\t" << this->area << std::endl;
	output << std::endl;
}

double Triangle_hi::count_area() const {
	double p = (side.AB + side.BC + side.CA) / 2;
	double s = std::pow(p * (p - side.AB) * (p - side.BC) * (p - side.CA), 0.5);  //!!!
	return s;
}

void Triangle_hi::triangles_print_outfile(const Ray<Triangle_hi>& triangle, size_t index, const std::string& path_out) {
	std::ofstream outfile(path_out);

	for (size_t i = 0; i < index; i++) {
		outfile << "NEW Triangle_hi:" << i + 1;

		triangle[i].print_to_file(outfile);

		outfile << "point_in_triangle =\t ";
		for (size_t j = 0; j < triangle[i].get_points_inside_Ray().size(); j++) {
			outfile << triangle[i].get_point_in(j).x << "," << triangle[i].get_point_in(j).y << "; ";
		}
		outfile << std::endl;
		outfile << std::endl;
	}
}

Triangle_hi Triangle_hi::create_triangle(const Dot& a, const Dot& b, const Dot& c) const {
	Triangle_hi temp_abc(a, b, c);

	///temp_abc.create(a, b, c);

	return temp_abc;
}

bool Triangle_hi::is_inside(const Dot& point, const Triangle_hi& abc) {
	Triangle_hi t1(abc.get_A(), abc.get_B(), point);
	Triangle_hi t2(abc.get_B(), abc.get_C(), point);
	Triangle_hi t3(abc.get_C(), abc.get_A(), point);

	if (utilities::isEqual(abc.get_area(), t1.area + t2.area + t3.area))
		return true;

	return false;
}

void Triangle_hi::points_print(const Dot p[], int n) const {
	for (size_t i = 0; i < n; i++) {
		Dot coords = p[i];
		std::cout << "point N_ " << i + 1 << " = \t" << coords.x << " \t" << coords.y << "\n";
	}
}


Ray<Dot> Triangle_hi::get_point_in_triangle() const
{
	return point_in_triangle;
}