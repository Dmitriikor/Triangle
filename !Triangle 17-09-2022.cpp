// 14.09.22 H
//FLODER NAME "Tiangle_RE"

#include <fstream>
#include <iomanip>
#include <iostream>

std::streamsize MAX_STREAMSIZE = std::numeric_limits<std::streamsize>::max();

#include <stdio.h>
#include <conio.h>
#include <windows.h>
//#include <wingdi.h>

#include <ctime>
#include <exception>

using std::endl;

const int MIN_ = -2147483648;
const int MAX_ = 2147483647;

#include <limits>

#include "draw_line_2_test.h"
#include "Point_test.h"
#include "Matrix_test.h"
#include "Ray_test.h"
#include "Lines_draw_test.h"  
#include "Triangle_test.h"


void goto_coords(Point a) {

	COORD b;
	b.X = a.x;
	b.Y = a.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
}


// main // main // main // main // main // main // main // main // main // main // main // main // main // main // main // main
// main // main // main // main // main // main // main // main // main // main // main // main // main // main // main // main

int main() {

	Ray a;
	Matrix b;
	Point c;
	Triangle d;

	int OS;
	std::cout << "Choise OS:\n \t1 Win, \n \t2 Ubuntu: \n";
	std::cin >> OS;
	std::string path_in;
	std::string path_out;

	switch (OS) {
	case 1: {
		path_in = { "points.txt" };
		path_out = { "out2.txt" };
		break;
	}
	case 2: {
		path_in = { "Tiangle_RE/points.txt" };
		path_out = { "Tiangle_RE/out2.txt" };
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
	size_t n_points;

	std::istream& input = input_switch == 1 ? infile : std::cin;
	bool loop = true;
	if (input_switch == 2 || input_switch == 3)
		std::cout << "Enter number of points:\n";

	input >> n_points;

	if (input_switch == 2)
		std::cout << "Enter points:\n";



	if (input_switch != 3)
		loop = false;

	int max_x = MIN_;
	int max_y = MIN_;
	int min_x = MAX_;
	int min_y = MAX_;

	Point* point_arr = new Point[n_points];

	for (size_t i = 0; i < n_points; i++) {
		Point temp;

		if (input_switch == 3) {
			//(rand()%range)±shift
			srand(time(NULL) + (rand() % 225000));
			temp.x = (rand() % 76) + (-38);  // 76 -38
			//Sleep(1000);
			srand(time(NULL) + (rand() % 155000));
			temp.y = (rand() % 60) + (-30);  // 60 - 30
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

	switch (OS) {
	case 1:
		system("cls");
		break;
	case 2:
		system("clear");
		break;
	}

	int t1 = clock();

	size_t N;
	size_t M;

	if (min_y == max_y)
		N = abs(max_y) + 1;
	else
		if (min_y >= 0 && max_y >= 0)
			N = abs(max_y) + 1;
		else if (min_y <= 0 && max_y <= 0)
			N = abs(min_y) + 1;
		else
			N = abs(max_y) + abs(min_y) + 1;

	if (max_x == min_x)
		M = abs(max_x) + 1;
	else if (max_x >= 0 && min_x >= 0)
		M = abs(max_x) + 1;
	else if (max_x <= 0 && min_x <= 0)
		M = abs(min_x) + 1;
	else
		M = abs(max_x) + abs(min_x) + 1;

	std::cout << "\n";

	int start_y = max_y > 0 ? max_y : 0;
	for (size_t i = 0; i < N; i++)
		std::cout << std::setw(shift_w()) << start_y - (int)i << " " << "\n";

	indent_print();
	Point ZERO;
	ZERO.y = start_y + x_axis_thickness(); //!!!!!SHIFT

	int start_x = min_x > 0 ? 0 : min_x;
	for (size_t i = 0; i < M; i++)
		std::cout << std::setw(shift_w()) << start_x + (int)i;
	std::cout << "\n";
	ZERO.x = ((abs(start_x)) * shift_w()) + indent() + y_axis_thickness(); //!!!!!SHIFT

	std::cout << "\n";
	
	goto_coords(ZERO);
	std::cout << "0";

	for (size_t j = 0; j < n_points; j++) {
		Point coord;
		coord.x = ZERO.x + (point_arr[j].x * shift_w());
		coord.y = ZERO.y - point_arr[j].y;
		goto_coords(coord);
		std::cout << "x";
	}

	Point end;
	end.x = 0;
	end.y = N + (N * shift()) + x_axis_thickness() + shift_h();
	goto_coords(end);
	std::cout << "\n";
	std::cout << "END\n";

	std::cout << "min_x " << min_x << "\n";
	std::cout << "max_x " << max_x << "\n";
	std::cout << "max_y " << max_y << "\n";
	std::cout << "min_y " << min_y << "\n";

	Triangle* triangle_arr = new Triangle[1 * 2 * 3 * (n_points - 2) * (n_points - 1) * n_points];  // 1*2*3*(n_points-2)*(n_points-1)*n_points;
	size_t n_triangles = 0;
	for (size_t i = 0; i < n_points; i++) {
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


	draw_line_2(final_triangle_arr[max_dot_index].get_A(), final_triangle_arr[max_dot_index].get_B(), ZERO);
	draw_line_2(final_triangle_arr[max_dot_index].get_B(), final_triangle_arr[max_dot_index].get_C(), ZERO);
	draw_line_2(final_triangle_arr[max_dot_index].get_C(), final_triangle_arr[max_dot_index].get_A(), ZERO);


	system("pause");
	std::cin.get();


	draw_line_4(final_triangle_arr[max_dot_index].get_A(), final_triangle_arr[max_dot_index].get_B(), ZERO, 1);
	draw_line_4(final_triangle_arr[max_dot_index].get_B(), final_triangle_arr[max_dot_index].get_C(), ZERO, 1);
	draw_line_4(final_triangle_arr[max_dot_index].get_C(), final_triangle_arr[max_dot_index].get_A(), ZERO, 1);

	return 0;
}
