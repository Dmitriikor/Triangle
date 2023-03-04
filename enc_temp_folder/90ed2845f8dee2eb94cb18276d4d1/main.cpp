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
#include "Axys.h"

////struct A {
////	void p()
////	{
////		std::cout << "1" << std::endl;
////	}
////};
////
////struct B : A {
////	void p()
////	{
////		std::cout << "2" << std::endl;
////	}
////};
////
////void foo()
////{
////	B b;
////
////	b.A::p();
////}
////
////double (mmm)() noexcept {
////	return DBL_MAX;
////}
////
////double (*mmm2)() = mmm;

int main(int argc, char const* argv[])
{
	////mmm();

	while (1) {
		double t1;

		try
		{
			size_t n_points = 10;
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

			int case_to_output_file_patch_switch;
			std::cout << "Choise output file settings:\n";
			std::cout << "\t 1 Save file in root folder, \n";
			std::cout << "\t 2 Or manual path to save : \n";
			case_to_output_file_patch_switch = 1;

			////std::cin >> case_to_output_file_patch_switch;

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
			input_switch = 3;

			////std::cin >> input_switch;
			////std::cin.ignore(MAX_STREAMSIZE, '\n');

			if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
				std::cout << "PROGRAM OVER\n";
				return 0;
			}

			std::ifstream infile(path_in);
			std::ofstream outfile(path_out);

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

			Ray<Dot> copy_to_print;
			if (Fin_Triangle.get_dot_counter() != 0)
			{
				Corner out_print;

				out_print.insert(Fin_Triangle.get_point_array(), '*');

				////*for (size_t i = 0; i < Fin_Triangle.size_point_array(); i++)
				////	copy_to_print.add_to_back(Fin_Triangle.get_point(i));*/

				out_print.insert(copy_to_print);
				out_print.add_line(Fin_Triangle.get_a(), Fin_Triangle.get_b(), '*');
				out_print.add_line(Fin_Triangle.get_b(), Fin_Triangle.get_c(), '*');
				out_print.add_line(Fin_Triangle.get_c(), Fin_Triangle.get_a(), '*');

				out_print.add_line(Fin_Triangle.get_a(), Fin_Triangle.get_a(),'+');

				out_print.print();
				out_print.print_to_file();

				////out_print.clear();
				////out_print.insert(Fin_Triangle.get_point_array(), '+');
				///out_print.clear();



				Axys a_out_print;
				a_out_print += out_print;
				a_out_print.print();
				////a_out_print.add_line({ 10,10 }, { -10,-10 }, '*');
				////a_out_print.print();


				Canvas_console ttst;
				///ttst.add_line({ 0,0 }, { 0,0 }, '&');
				///ttst.add_line({ 1,1 }, { 1,1  }, '/');
				///ttst.add_line({ 3,1 }, { 3, 1 }, '\\');
				///ttst.add_line({ 0,10 }, { 10, 0 }, '&');
				ttst += out_print;
				ttst.print();
			}
			////int t2;
			////std::cin >> t2;
		}
		catch (const std::runtime_error& exception)
		{
			std::cout << "\n\texception :  " << exception.what() << std::endl;
		}

		double t2 = clock();
		std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;

	int t2pause;
	////std::cin >> t2pause;
	}
	return 0;
}
