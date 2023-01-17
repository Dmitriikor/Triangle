#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
std::streamsize static MAX_STREAMSIZE = std::numeric_limits<std::streamsize>::max();
///#include "Ray_3_test.h"
#include "hello.h"
#include "Point_test.h"
#include "Triangle_test.h"
#include "utilities.h"
#include "Ray_template.h"
#include "Matrix_TEMPLATE.h"
#include <exception>
#include <utility>


#include "windows.h" 
#include "Windows.h" 


int main(int argc, char const* argv[])
{
	///utilities::fast_print(); //don't work in g++/gcc


	///std::ios_base::sync_with_stdio(false);
	///std::cin.tie(NULL);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	/// {  test create & call base handwritten "libs"
	///Ray_3_ a;
	///Matrix b;
	///Dot c;
	///  }  test create & call base handwritten "libs"
	{
		Matrix_TEMPLATE test_once_1(1, 2, 'o');
		Matrix_TEMPLATE test_once_2(1, 2, 'o');
		Matrix_TEMPLATE test_once_3(1, 2, 'o');
		Matrix_TEMPLATE<char> test_once_4(1, 2, 'o');

		test_once_1.print();
		std::cout << std::endl;

		std::cout << "\t\t\t\n\n" << "1" << "\n";

		test_once_2.resize(10, 10, 'q');
		test_once_2.print();
		std::cout << std::endl;

		std::cout << "\t\t\t\n\n" << "2" << "\n";

		test_once_3.resize(20, 20, 'w');
		test_once_3.print();
		std::cout << std::endl;

		std::cout << "\t\t\t\n\n" << "3" << "\n";

		test_once_4.resize(30, 30, 'e');
		test_once_4.print();
		std::cout << std::endl;

		std::cout << "\t\t\t\n\n" << "4" << "\n";

		test_once_4.resize(50, 50, 'r');
		std::cout << std::endl;

		std::cout << "\t\t\t\n\n" << "5" << "\n";
		test_once_4.print();

	

	
		Matrix_TEMPLATE<int> test_move_1_1(2, 2, 2);
		Matrix_TEMPLATE<int> test_move_2_2(3, 3, 3);
		


		test_move_1_1.print();
		test_move_2_2.print();
		std::cout << "----------+=+=-------------------------\n";
		Sleep(4000);

		Matrix_TEMPLATE<int> test_move_3_3(4,4,4);
		
		test_move_3_3 += test_move_2_2;

		test_move_3_3.print();
		std::cout << "----------+=+=-------------------------\n";
		Sleep(4000);
		std::cout << "----------++++-------------------------\n";
		Matrix_TEMPLATE<int> test_move_3_4 = test_move_3_3 + test_move_3_3;

		test_move_3_4.print();

		Sleep(4000);
		std::cout << "----------++++-------------------------\n";
		test_move_1_1.resize(10, 15, 0);
		test_move_2_2.resize(5, 5, 5);

		test_move_1_1.print();
		test_move_2_2.print();
		std::cout << "---------------------------------------\n";


		test_move_1_1.set_at(9, 14, 9);
		test_move_2_2.set_at(4, 4, 8);
		std::cout << "---------------------------------------\n";

		test_move_2_2 = std::move(test_move_1_1);
		std::cout << "--std::move(test_move_1_1);------------\n";

		test_move_2_2.print();
		std::cout << "--std::move(test_move_2_2);------------\n";

		Matrix_TEMPLATE<int> test_move_2_3 = std::move(test_move_2_2);

		test_move_2_3.print();
		std::cout << "---------------------------------------\n";
	}
	



	Ray_template<int> test_move_1o;
	Ray_template<int> test_move_2o;
	Sleep(2000);
	std::cout << "---------------------------------------\n";
	print(test_move_1o);
	print(test_move_2o);
	std::cout << "---------------------------------------\n";

	test_move_1o.add_to_back(5);
	test_move_1o.add_to_first(4);
	std::cout << "---------------------------------------\n";

	print(test_move_1o);
	print(test_move_2o);
	std::cout << "---------------------------------------\n";

	test_move_2o = std::move(test_move_1o);

	print(test_move_2o);
	std::cout << "---------------------------------------\n";
	

	Ray_template<int> test_move_1;
	Ray_template<int> test_move_2 = std::move(test_move_1);
	Ray_template<int> test_move_3 (20,30);
	test_move_3.add_to_back(5);
	test_move_3.add_to_first(4);
	std::cout << test_move_3[0];
	std::cout << test_move_3[1];

	print(test_move_3);
	test_move_3 = std::move(test_move_3);

	test_move_1 = std::move(test_move_3);
	print(test_move_1);

	Triangle_hi t = Triangle_hi({ 1, 2 }, { 3,4 }, { 5,6 });

	Triangle_hi t_2 = std::move(t);


	///Triangle_hi d;
	Sleep(5000);
	std::cout << "Enter number of points:\n";
	size_t n_points;
	//std::cin >> n_points;

	n_points = 3;

	int OS_start_dialoge_type_;
	std::cout << "Choise OS:\n \t1 Win, \n \t2 Ubuntu: \n \t3 Manual path to save:\n";
	//std::cin >> OS_start_dialoge_type_;
	std::string path_in;
	std::string path_out;

	OS_start_dialoge_type_ = 1;


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
		///std::getline (std::cin,name);
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


	std::cout << "Choose mode:\n \t1 input on file, \n \t2 input manual: \n \t3 auto:\n";
	int input_switch;
	//std::cin >> input_switch;
	//std::cin.ignore(MAX_STREAMSIZE, '\n');

	input_switch = 3;


	if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
		std::cout << "PROGRAM OVER\n";
		return 0;
	}

	std::ifstream infile(path_in);
	std::ofstream outfile(path_out);


	std::istream& input = input_switch == 1 ? infile : std::cin;

	///if (input_switch == 2 || input_switch == 3)


	if (input_switch == 2)
		std::cout << "Enter points:\n";

	int max_x = INT_MIN;
	int max_y = INT_MIN;
	int min_x = INT_MAX;
	int min_y = INT_MAX;

	Dot* point_arr = new Dot[n_points];

	for (size_t i = 0; i < n_points; i++) {
		Dot temp;

		if (input_switch == 3) {
			///(rand()%range)�shift
			///srand(time(NULL) + (rand() % 225000));
			temp.x = utilities::random_INT(-20, 20);
			///Sleep(1000);
			///srand(time(NULL) + (rand() % 155000));
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
	Dot test_holder;

	// { work with Dot arr, to create triangle and find max inside point
	Triangle_hi d;
	Triangle_hi* triangle_arr = new Triangle_hi[1 * 2 * 3 * (n_points - 2) * (n_points - 1) * n_points];  /// 1*2*3*(n_points-2)*(n_points-1)*n_points;
	size_t n_triangles = 0;
	for (size_t i = 0; i < n_points; i++)
	{
		for (size_t j = i + 1; j < n_points; j++)  //!!! < n
		{
			for (size_t k = j + 1; k < n_points; k++)  //!!! < n
			{
				Triangle_hi temp_abc = d.create_triangle(point_arr[i], point_arr[j], point_arr[k]);

				if (isEqual(temp_abc.get_area(), 0))
					break;

				if (temp_abc.is_triangle_()) {
					triangle_arr[n_triangles] = temp_abc;
					++n_triangles;
				}
			}
		}
	}

	Triangle_hi* final_triangle_arr = new Triangle_hi[n_triangles];
	for (size_t i = 0; i < n_triangles; i++)
		final_triangle_arr[i] = triangle_arr[i];
	delete[] triangle_arr;

	///size_t hit = 0;
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
	size_t max_dot_index = 0;
	for (size_t i = 0; i < n_triangles; i++) {
		if (final_triangle_arr[i].get_dot_counter() > max_dot) {
			max_dot = final_triangle_arr[i].get_dot_counter();
			max_dot_index = i;
		}
		Triangle_hi::triangles_print_outfile(final_triangle_arr, n_triangles, path_out2);
	}

	final_triangle_arr[max_dot_index].print();
	size_t cout_cntr = 15;

	// } work with Dot arr, to create triangle and find max inside point

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	///go_debug(false);
	try
	{

		Dot a;
		Dot b;
		Dot c;
		Dot d;
		///Ray_3_ test___;
		Ray_template<Dot> test___;

		int rnd = utilities::random_INT(0, 90);
		std::cout << "\n" << rnd << "\n";

		//a = { 15, 1 };

		std::cout << "\n" << "start" << "\n";
		Corner Test_corner;
		Corner Test_corner_2;
		Axys Test_axys;

		bool is_cont = true;
		while (is_cont == true) {

			//system("cls");

			int st_x_rnd_lmt = -20; int ed_x_rnd_lmt = 20;
			int st_y_rnd_lmt = -10; int ed_y_rnd_lmt = 10;

			a.x = utilities::random_INT(st_x_rnd_lmt, ed_x_rnd_lmt); a.y = utilities::random_INT(st_y_rnd_lmt, ed_y_rnd_lmt); a.symbol = '^';
			test___.add_to_back(a);
			b.x = utilities::random_INT(st_x_rnd_lmt, ed_x_rnd_lmt); b.y = utilities::random_INT(st_y_rnd_lmt, ed_y_rnd_lmt); b.symbol = '^';
			test___.add_to_back(b);
			c.x = utilities::random_INT(st_x_rnd_lmt, ed_x_rnd_lmt); c.y = utilities::random_INT(st_y_rnd_lmt, ed_y_rnd_lmt); c.symbol = '^';
			test___.add_to_back(c);
			d.x = utilities::random_INT(st_x_rnd_lmt, ed_x_rnd_lmt); d.y = utilities::random_INT(st_y_rnd_lmt, ed_y_rnd_lmt); d.symbol = '^';
			test___.add_to_back(d);



			Test_corner.insert(test___);
			test___.clear();


			Dot tpm; tpm.x = utilities::random_INT(st_x_rnd_lmt, ed_x_rnd_lmt); tpm.y = utilities::random_INT(st_y_rnd_lmt, ed_y_rnd_lmt); tpm.symbol = 'o';
			Test_corner.insert(tpm);

			Dot tpm2; tpm2.x = -5; tpm2.y = 5; tpm2.symbol = '!';
			Dot tpm3; tpm3.x = 5; tpm3.y = -5; tpm3.symbol = '!';
			Test_corner_2.add_lines(tpm2, tpm3, true, '-');


			Dot tpm4; tpm4.x = -5; tpm4.y = -5; tpm4.symbol = '!';
			Dot tpm5; tpm5.x = 5; tpm5.y = 5; tpm5.symbol = '!';
			Test_corner_2.add_lines(tpm4, tpm5, true, '*');


			Corner Test_corner_3;
			Test_corner += Test_corner_2;
			Test_corner_3 += Test_corner;


			Test_axys += Test_corner_3;
			Corner Test_corner_4 = Test_corner_3;
			Test_axys.print();
			Test_corner_3.print();
			Test_corner_4.print();

			Corner Test_corner_0 = Test_corner_4;
			Test_corner_0 += Test_axys;
			Test_corner_0.print(1);
			std::cout << "\n";

			//std::cin.get();

			std::cout << "\t\n" << "is_cont" << "\n";
			std::cin >> is_cont;


			///std::cout << "\n";
			///			for (size_t i = 0; i < Test_corner.points_to_draw().size(); i++)
			///			{
			///				std::cout << Test_corner.points_to_draw()[i].x << "," << Test_corner.points_to_draw()[i].y << ";  ";
			///			}
			///std::cout << "\n";

			std::cout << "\n";



			std::ofstream outfile_corner("corner_path_out.txt");

			///Test_corner.print_to_file();

			///std::ofstream outfile_axys("axys_path_out.txt");
			///Test_axys.print_to_file(outfile_axys);
			std::cout << "end hello" << "\n";

		}

		std::cout << "end hello" << "\n";
	}
	catch (const std::runtime_error& exception)
	{
		std::cout << "\n\texception :  " << exception.what() << std::endl;
	}


	return 0;
}
