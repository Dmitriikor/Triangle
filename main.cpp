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
	 
	int OS_start_dialoge_type_;
	std::cout << "Choise OS:\n \t1 Win, \n \t2 Ubuntu: \n \t3 Manual path to save:\n";
	std::cin >> OS_start_dialoge_type_;
	std::string path_in;
	std::string path_out;

	switch (OS_start_dialoge_type_) {
	case 1: {
		path_in = { "points.txt" };
		path_out = { "out.txt" };
		break;
	}
	case 2: {
		path_in = { "Tiangle_RE/points.txt" };
		path_out = { "Tiangle_RE/out2.txt" };
		break;
	}
	case 3: {
		//std::getline (std::cin,name);
		std::cout << "\n Enter path_in \n\t";
		std::getline(std::cin, path_in);
		std::cout << "\n Enter path_out \n\t";
		std::getline(std::cin, path_out);
		break;
	}
	default: {
		std::cout << "PROGRAM OVER\n";
		return 0;
	}
	}


	std::cout << "Choise mode:\n \t1 input on file, \n \t2 input manual: \n \t3 auto:\n";
	int input_switch;
	std::cin >> input_switch;
	std::cin.ignore(MAX_STREAMSIZE, '\n');

	if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
		std::cout << "PROGRAM OVER\n";
		return 0;
	}

	std::ifstream infile(path_in);
	std::ofstream outfile(path_out);


	std::istream& input = input_switch == 1 ? infile : std::cin;

	//if (input_switch == 2 || input_switch == 3)


	if (input_switch == 2)
		std::cout << "Enter points:\n";

	int max_x = INT_MIN;
	int max_y = INT_MIN;
	int min_x = INT_MAX;
	int min_y = INT_MAX;

	Point* point_arr = new Point[n_points];

	for (size_t i = 0; i < n_points; i++) {
		Point temp;

		if (input_switch == 3) {
			//(rand()%range)±shift
			//srand(time(NULL) + (rand() % 225000));
			temp.x = utilities::random_INT(-20, 20);
			//Sleep(1000);
			//srand(time(NULL) + (rand() % 155000));
			temp.y = utilities::random_INT(-20, 20);
			std::cout << temp.x << " " << temp.y << "\n";
		}
		else {
			input >> temp.x >> temp.y;
		}

		if (temp.x > max_x)
			max_x = temp.x;
		if (temp.y > max_y)
			max_y = temp.y;

		if (temp.x < min_x)
			min_x = temp.x;
		if (temp.y < min_y)
			min_y = temp.y;

		point_arr[i] = temp;
	}



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
	std::string path_out2 = "out.txt";

	delete[] point_arr;
	size_t max_dot = 0;
	size_t max_dot_index;
	for (size_t i = 0; i < n_triangles; i++) {
		if (final_triangle_arr[i].get_dot_counter() > max_dot) {
			max_dot = final_triangle_arr[i].get_dot_counter();
			max_dot_index = i;
		}
		d.triangles_print_outfile(final_triangle_arr, n_triangles, path_out2);
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

		int rnd = utilities::random_INT(0, 90);
		std::cout << "\n" << rnd << "\n";

		//a = { 15, 1 };

		std::cout << "\n" << "start" << "\n";

			corner Test_corner;
			axys Test_axys;
		
		while (true) {
			//	system("cls");
			a.x = utilities::random_INT(-15, 15); a.y = utilities::random_INT(-15, 15); a.symbol = '+';
			test___.add_to_back(a);
			b.x = utilities::random_INT(-15, 15); b.y = utilities::random_INT(-15, 15); b.symbol = '+';
			test___.add_to_back(b);
			c.x = utilities::random_INT(-15, 15); c.y = utilities::random_INT(-15, 15); c.symbol = '+';
			test___.add_to_back(c);
			d.x = utilities::random_INT(-15, 15); d.y = utilities::random_INT(-15, 15); d.symbol = '+';
			test___.add_to_back(d);


			std::cout << "\n";
			std::cout << "\n";
			std::cout << "\n";


			std::cout << "\n";
			//canvas Test_;

			//for (size_t i = 0; i < test___.size(); i++)
			//{
			//	std::cout << test___[i].x << " , " << test___[i].y << " ; ";
			//}

			Test_corner.add_points(test___);
			test___.clear();


			Point tpm; tpm.x = -3; tpm.y = 3; tpm.symbol = 'o';
			Test_corner.insert(tpm);
			Test_corner.print_point();


			Point tpm2; tpm2.x = -5; tpm2.y = 5; tpm2.symbol = '!';
			Point tpm3; tpm3.x = 5; tpm3.y = -5; tpm3.symbol = '!';
			Test_corner.add_lines(tpm2, tpm3,true,'-');
			Test_corner.print_line();

			Point tpm4; tpm4.x = -5; tpm4.y = -5; tpm4.symbol = '!';
			Point tpm5; tpm5.x = 5; tpm5.y = 5; tpm5.symbol = '!';
			Test_corner.add_lines(tpm4, tpm5, true,'*');
			Test_corner.print_line();

			Point tpm6; tpm6.x = 0; tpm6.y = 0; tpm6.symbol = '!';
			Test_corner.delite(tpm6);
			Test_corner.print_all();

			Test_corner.delite_line(tpm4, tpm5);
			Test_corner.print_all();


			std::cout << "\n";




std::cout << "\n";
			for (size_t i = 0; i < Test_corner.points_to_draw().size(); i++)
			{
				std::cout << Test_corner.points_to_draw()[i].x << "," << Test_corner.points_to_draw()[i].y << ";  ";
			}
std::cout << "\n";


			//system("cls");
			std::cout << "\n";
			//Test_axys.add_points(test___);
			//Test_axys.create();
			//Test_axys.draw_points();
			//Test_axys.print();


			std::ofstream outfile_corner("corner_path_out.txt");

			Test_corner.print_to_file();

			//std::ofstream outfile_axys("axys_path_out.txt");
			//Test_axys.print_to_file(outfile_axys);
			std::cout << "end hello" << "\n";

		}
			////	
			////Point to_line_1;
			////std::cout << "\n\t" << "input" << "\n";
			////std::cin >> to_line_1.x >> to_line_1.y;
	
			////Point to_line_2;
			////std::cout << "\n\t" << "input" << "\n";
			////std::cin >> to_line_2.x >> to_line_2.y;
			////std::cout << "\n\t" << "input smbl" << "\n";
			////std::cin >> to_line_2.symbol;
			////
			////hello_try_set_min_max_by(to_line_1);

			////hello_try_set_min_max_by(to_line_2);

			////draw_line_1_(to_line_1, to_line_2,false , to_line_2.symbol);
			//
			////draw_points();

			////draw_line();
			////print_arr();

			////draw_line_1_(to_line_1, to_line_2, true, to_line_2.symbol);

			////draw_line();
			////print_arr();




			//canvas Test_;
			// 
			// 
			//corner Test_corner_; // to do

			//canvas Test;
			//corner Test_corner;
			//axys Test_axys;

			//Test.add_points(final_triangle_arr[max_dot_index].get_points_inside_Ray());
			////Test.calculate_line_round(to_line_1, to_line_2);
			//Test_corner.create(Test);
			//Test_corner.print(Test);
			//Test_corner.draw_lines(Test);
			//Test_corner.print(Test);
			//Test_corner.draw_points(Test);
			//Test_corner.print(Test);
			//Test_corner.draw_lines(final_triangle_arr[max_dot_index].get_A(), final_triangle_arr[max_dot_index].get_B(), true, 'o', Test);
			//Test_corner.draw_lines(final_triangle_arr[max_dot_index].get_B(), final_triangle_arr[max_dot_index].get_C(), true, 'p', Test);
			//Test_corner.draw_lines(final_triangle_arr[max_dot_index].get_C(), final_triangle_arr[max_dot_index].get_A(), true, 'l', Test);
			//Test_corner.print(Test);
			//Test_corner.create(Test);
			//Test_corner.print(Test);


			//corner().draw_points(Test);

			//Test.print();
			//
			//
			//Test.print();

			//Test_corner.print(Test);

			//std::ofstream outfile("Matrix_path_out.txt");
			//Test.print_to_file(outfile);


			//axys().create(Test);
			//axys().draw_lines(Test);
			//Test_axys.print(Test);
			//axys().draw_points(Test);
			//axys().print(Test);

			////erase_lines();  //erase_lines_from_canvas 
			////erase_points(); //erase_points_from_canvas

			////print_arr();

			////draw_line_1_(test___[0], test___[3], false, '-');
			////draw_line();								// add_line_to_canvas
			////print_arr();
			////draw_line_1_(test___[0], test___[3], true, '+');// add_new_line_to_line_Ray
			////draw_line();								// add_line_to_canvas
			////print_arr();								// print_canvas 

			////delite_lines();  //erase_lines_from_lines_Ray 
			////delite_points(); //erase_lines_from_points_Ray 
			///*
			//Point er;
			//std::cout << "\n\t" << "input er" << "\n";
			//std::cin >> er.x >> er.y;
			////erase_point(er);
			//*/
			////print_arr();
			////canvas_clear();
			////delite_line(test___[0], test___[3]);
			////print_arr();
			//int st = 0;
		//}
		std::cout << "end hello" << "\n";
	}
		catch (const std::exception& exception)
	{
		std::cout << "\n\texception :  " << exception.what() << std::endl;
	 } 


	return 0;
}
