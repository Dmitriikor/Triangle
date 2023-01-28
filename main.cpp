#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
std::streamsize static MAX_STREAMSIZE = std::numeric_limits<std::streamsize>::max();
///#include "Ray_3_test.h"
#include <exception>
#include <utility>

#include "Windows.h" 
#include "Canvas.h"
#include "Point.h"
#include "Triangle.h"
#include "utilities.h"
#include "Ray.h"
#include "Matrix.h"
#include "Find_Triangle.h"
#include "Corner.h"

int main(int argc, char const* argv[])
{
	double t1;

	try
	{
		size_t n_points = 0;
		while (true)
		{
			if (n_points >= 3)
				break;
			else {
				Sleep(1500);
				system("cls");
				std::cout << "Enter number of points:\n";
				std::cin >> n_points;
			}
			std::cout << "The number of points to build a triangle must be at least 3 \n";

		}

		int   case_to_output_file_patch_switch;
		std::cout << "Choise output file settings:\n";
		std::cout << "\t 1 Save file in root folder, \n";
		std::cout << "\t 2 Or manual path to save : \n";

		std::cin >> case_to_output_file_patch_switch;
		std::string path_in;
		std::string path_out;

		switch (case_to_output_file_patch_switch)
		{
		case 1:
		{
			path_in = { "points.txt" };
			path_out = { "out.txt" };
			break;
		}
		case 2:
		{
			///std::getline (std::cin,name);
			std::cout << "\n Enter path_in \n\t";
			std::getline(std::cin, path_in);
			std::cout << "\n Enter path_out \n\t";
			std::getline(std::cin, path_out);
			break;
		}
		default:
		{
			std::cout << "PROGRAM OVER\n";
			return 0;
		}
		}

		std::cout << "Choose mode:\n";
		std::cout << "\t 1 input on file, \n";
		std::cout << "\t 2 input manual,  \n";
		std::cout << "\t 3 automatically generate random points \n";

		int input_switch;
		std::cin >> input_switch;
		std::cin.ignore(MAX_STREAMSIZE, '\n');

		if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
			std::cout << "PROGRAM OVER\n";
			return 0;
		}

		std::ifstream infile(path_in);
		///std::ofstream outfile(path_out);

		std::istream& input = input_switch == 1 ? infile : std::cin;

		if (input_switch == 2)
			std::cout << "Enter points:\n";

		Ray<Dot> point_arr;

		if (input_switch == 1)
			std::cout << "\n \tAttention! Only the above quantity will be taken from the file \n";
		for (size_t i = 0; i < n_points; i++) {
			Dot temp;

			if (input_switch == 3) {
				temp.x = utilities::random_INT(-20, 20);
				temp.y = utilities::random_INT(-20, 20);
			}
			else {
				input >> temp.x >> temp.y;
			}
			point_arr.add_to_back(temp);
		}


		 t1 = clock();


		Triangle_hi Fin_Triangle;
		Fin_Triangle = Find_Triangle(point_arr, n_points);


		if (Fin_Triangle.get_dot_counter() != 0)
		{
			Corner out_print;
			out_print.insert(Fin_Triangle.get_point_in_triangle());

			out_print.add_lines(Fin_Triangle.get_A(), Fin_Triangle.get_B(),'*');
			out_print.add_lines(Fin_Triangle.get_B(), Fin_Triangle.get_C(),'*');
			out_print.add_lines(Fin_Triangle.get_C(), Fin_Triangle.get_A(),'*');
		 
			out_print.print_file();
			out_print.print();
		}

	}
	catch (const std::runtime_error& exception)
	{
		std::cout << "\n\texception :  " << exception.what() << std::endl;
	}
	double t2 = clock();
	std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;

	std::cin >> t2;
	return 0;
}
