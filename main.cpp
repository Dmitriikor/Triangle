#include "Ray_3_test.h"
#include "hello.h"
#include "Point_test.h"
#include <iostream>
#include <exception>


int main(int argc, char const* argv[])
{
	std::ios_base::sync_with_stdio(false);

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
			Point to_line_1;
			std::cout << "\n\t" << "input" << "\n";
			std::cin >> to_line_1.x >> to_line_1.y;
	
			Point to_line_2;
			std::cout << "\n\t" << "input" << "\n";
			std::cin >> to_line_2.x >> to_line_2.y;
			std::cout << "\n\t" << "input smbl" << "\n";
			std::cin >> to_line_2.symbol;
			
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

			Test.add_points(test___);
			//Test.calculate_line_round(to_line_1, to_line_2);
			Test_corner.create_corner(Test);
			Test_corner.print_corner(Test);
			Test_corner.draw_lines(Test);
			Test_corner.print_corner(Test);
			Test_corner.draw_points(Test);
			Test_corner.print_corner(Test);
			Test_corner.draw_lines(to_line_1, to_line_2, true, '-', Test);
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
