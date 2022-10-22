#include "Ray_3_test.h"
#include "hello.h"
#include "Point_test.h"
#include <iostream>
#include <exception>

int main(int argc, char const* argv[])
{
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

		initialize_min_max_points(test___, true);

		Point pt;
		pt.x = 20; pt.y = -15;

		hello_try_set_min_max_by(pt);

		initialize_width(); //rename

		//print_corner();

		print_arr();

		draw_points();


		while (true) {
			Point to_line_1;
			std::cout << "\n\t" << "input" << "\n";
			std::cin >> to_line_1.x >> to_line_1.y;
			Point to_line_2;
			std::cout << "\n\t" << "input" << "\n";
			std::cin >> to_line_2.x >> to_line_2.y;

			hello_try_set_min_max_by(to_line_1, false);

			hello_try_set_min_max_by(to_line_2, false);

			hello_draw_line_1(to_line_1, to_line_2);

			draw_points(true);
		}
		std::cout << "end hello" << "\n";
	}
		catch (const std::exception& exception)
	{
		std::cout << "\n\texception :  " << exception.what() << std::endl;
	 } 


	return 0;
}
