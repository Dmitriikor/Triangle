#include "Ray_3_test.h"
#include "hello.h"
#include "Point_test.h"
#include <iostream>
#include <exception>



int main(int argc, char const* argv[])
{
	go_debug(false);
	try
	{
		Point a;
		Point b;
		Point c;
		Point d;
		Ray_3_ test___;

		//a = { 15, 1 };
		a.x = -25; a.y = 1;
		test___.add_to_back(a);
		b.x = 0; b.y = 0;
		test___.add_to_back(b);
		c.x = -5; c.y = -12;
		test___.add_to_back(c);
		d.x = 1; d.y = 10;
		test___.add_to_back(d);
		std::cout << "\n" << "start" << "\n";

		initialize_min_max_points(test___);

		Point pt;
		pt.x = 1; pt.y = 1;

		hello_try_set_min_max_by(pt);
	
		initialize_width(); //rename

		//print_corner();
		//print_arr();
		//draw_points();

		print_arr();

			while (true) {
			
			Point to_line_1;
			std::cout << "\n\t" << "input" << "\n";
			std::cin >> to_line_1.x >> to_line_1.y;
			Point to_line_2;
			std::cout << "\n\t" << "input" << "\n";
			std::cin >> to_line_2.x >> to_line_2.y;

			hello_try_set_min_max_by(to_line_1, false);

			hello_try_set_min_max_by(to_line_2, false);

			draw_line_1_(to_line_1, to_line_2);
			
			//draw_points();

			draw_line();
			print_arr();
			
			//erase_lines();  //erase_lines_from_canvas 
			//erase_points(); //erase_points_from_canvas

			//print_arr();

			draw_line_1_(test___[0], test___[3]);		// add_new_line_to_line_Ray
			draw_line();								// add_line_to_canvas
			print_arr();								// print_canvas 

			//delite_lines();  //erase_lines_from_lines_Ray 
			//delite_points(); //erase_lines_from_points_Ray 

			/*Point er;
			std::cout << "\n\t" << "input er" << "\n";
			std::cin >> er.x >> er.y;
			erase_point(er);*/

			//print_arr();
			//canvas_clear();
			erase_line(test___[0], test___[3]);
			print_arr();
			canvas_clear();
			draw_line();
			print_arr();
			erase_point_on_lines
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
