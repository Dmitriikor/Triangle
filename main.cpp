#include <iostream>
#include <iomanip>
#include <fstream>
std::streamsize static MAX_STREAMSIZE = std::numeric_limits<std::streamsize>::max();
#include "Ray_3_test.h"
#include "hello.h"
#include "Point_test.h"
#include "Triangle_test.h"
#include "utilities.h"
#include <exception>
#include <limits>

int main(int argc, char const* argv[])
{
	std::ios_base::sync_with_stdio(false);
	 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 


	// {  test create & call base handwritten "libs"
	Ray_3_ a;
	Matrix b;
	Point c;
	Triangle d;
	//  }  test create & call base handwritten "libs"

	std::cout << "Enter number of points:\n";
	size_t n_points;
	std::cin >> n_points;
	Point* point_arr = utilities::start_dialoge(MAX_STREAMSIZE, n_points);


	int t1 = clock();


	// { work with Point arr, to create triangle and find max insade point
	Triangle* triangle_arr = new Triangle[1 * 2 * 3 * (n_points - 2) * (n_points - 1) * n_points];  // 1*2*3*(n_points-2)*(n_points-1)*n_points;
	size_t n_triangles = 0;
	for (size_t i = 0; i < n_points; i++)
	{
		for (size_t j = i + 1; j < n_points; j++)  //!!! < n
		{
			for (size_t k = j + 1; k < n_points; k++)  //!!! < n
			{
				Triangle temp_abc = d.create_triangle(point_arr[i], point_arr[j], point_arr[k]);

				if (isEqual(temp_abc.get_area(), 0))
					break;

				if (temp_abc.is_triangle()) {
					triangle_arr[n_triangles] = temp_abc;
					++n_triangles;
				}
			}
		}
	}

	Triangle* final_triangle_arr = new Triangle[n_triangles];
	for (size_t i = 0; i < n_triangles; i++)
		final_triangle_arr[i] = triangle_arr[i];
	delete[] triangle_arr;

	size_t hit = 0;
	for (size_t i = 0; i < n_triangles; i++) {
		for (size_t j = 0; j < n_points; j++)
			if (d.is_inside(point_arr[j], final_triangle_arr[i])) {
				final_triangle_arr[i].add_point_at_vector(point_arr[j]);
			}
	}

	//to do
	std::string path_out = "out.txt";

	delete[] point_arr;
	size_t max_dot = 0;
	size_t max_dot_index;
	for (size_t i = 0; i < n_triangles; i++) {
		if (final_triangle_arr[i].get_dot_counter() > max_dot) {
			max_dot = final_triangle_arr[i].get_dot_counter();
			max_dot_index = i;
		}
		d.triangles_print_outfile(final_triangle_arr, n_triangles, path_out);
	}
	final_triangle_arr[max_dot_index].print();
	size_t cout_cntr = 15;

	// } work with Point arr, to create triangle and find max insade point
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//go_debug(false);
	try
	{
		
		Point a;
		Point b;
		Point c;
		Point d;
		Ray_3_ test___;

		//a = { 15, 1 };
		a.x = -13; a.y = 1; a.symbol = '1';
		test___.add_to_back(a);
		b.x = -5; b.y = 2; b.symbol = '2';
		test___.add_to_back(b);
		c.x = -2; c.y = 5; c.symbol = '3';
		test___.add_to_back(c);
		d.x = 1; d.y = 13; d.symbol = '4';
		test___.add_to_back(d);

		std::cout << "\n" << "start" << "\n";

		
			while (true) {
			//	
			//Point to_line_1;
			//std::cout << "\n\t" << "input" << "\n";
			//std::cin >> to_line_1.x >> to_line_1.y;
	
			//Point to_line_2;
			//std::cout << "\n\t" << "input" << "\n";
			//std::cin >> to_line_2.x >> to_line_2.y;
			//std::cout << "\n\t" << "input smbl" << "\n";
			//std::cin >> to_line_2.symbol;
			//
			//hello_try_set_min_max_by(to_line_1);

			//hello_try_set_min_max_by(to_line_2);

			//draw_line_1_(to_line_1, to_line_2,false , to_line_2.symbol);
			
			//draw_points();

			//draw_line();
			//print_arr();

			//draw_line_1_(to_line_1, to_line_2, true, to_line_2.symbol);

			//draw_line();
			//print_arr();

			canvas Test_;
			 
			 
			corner Test_corner_; // to do

			canvas Test;
			corner Test_corner;
			axys Test_axys;

			Test.add_points(final_triangle_arr[max_dot_index].get_points_inside_Ray());
			//Test.calculate_line_round(to_line_1, to_line_2);
			Test_corner.create_corner(Test);
			Test_corner.print_corner(Test);
			Test_corner.draw_lines(Test);
			Test_corner.print_corner(Test);
			Test_corner.draw_points(Test);
			Test_corner.print_corner(Test);
			Test_corner.draw_lines(final_triangle_arr[max_dot_index].get_A(), final_triangle_arr[max_dot_index].get_B(), true, 'o', Test);
			Test_corner.draw_lines(final_triangle_arr[max_dot_index].get_B(), final_triangle_arr[max_dot_index].get_C(), true, 'p', Test);
			Test_corner.draw_lines(final_triangle_arr[max_dot_index].get_C(), final_triangle_arr[max_dot_index].get_A(), true, 'l', Test);
			Test_corner.print_corner(Test);
			Test_corner.create_corner(Test);
			Test_corner.print_corner(Test);


			corner().draw_points(Test);

			Test.print_corner();
			
			
			Test.print_axys();

			Test_corner.print_corner(Test);

			axys().create_axys(Test);
			axys().draw_lines(Test);
			Test_axys.print_axys(Test);
			axys().draw_points(Test);
			axys().print_axys(Test);

			//erase_lines();  //erase_lines_from_canvas 
			//erase_points(); //erase_points_from_canvas

			//print_arr();

			//draw_line_1_(test___[0], test___[3], false, '-');
			//draw_line();								// add_line_to_canvas
			//print_arr();
			//draw_line_1_(test___[0], test___[3], true, '+');// add_new_line_to_line_Ray
			//draw_line();								// add_line_to_canvas
			//print_arr();								// print_canvas 

			//delite_lines();  //erase_lines_from_lines_Ray 
			//delite_points(); //erase_lines_from_points_Ray 
			/*
			Point er;
			std::cout << "\n\t" << "input er" << "\n";
			std::cin >> er.x >> er.y;
			//erase_point(er);
			*/
			//print_arr();
			//canvas_clear();
			//delite_line(test___[0], test___[3]);
			//print_arr();
			int st = 0;
		}
		std::cout << "end hello" << "\n";
	}
		catch (const std::exception& exception)
	{
		std::cout << "\n\texception :  " << exception.what() << std::endl;
	 } 


	return 0;
}
