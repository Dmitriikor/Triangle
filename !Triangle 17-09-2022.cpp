// 14.09.22 H
//FLODER NAME "Tiangle_RE"
//
//#include <fstream>
//#include <iomanip>
//#include <iostream>
//
//std::streamsize MAX_STREAMSIZE = std::numeric_limits<std::streamsize>::max();
//
//#include <stdio.h>
//#include <conio.h>
//#include <windows.h>
//#include <wingdi.h>
//
//#include <ctime>
//
//
//using std::endl;
//
//
//#include <limits> // MAX_STREAMSIZE
//const int MIN_ = INT_MIN; 
//const int MAX_ = INT_MAX;
//
//#include "draw_line_2_test.h"
//#include "Point_test.h"
//#include "Matrix_test.h"
//#include "Ray_test.h"
//#include "Lines_draw_test.h"  
//#include "Triangle_test.h"
//#include "Switch_cls_clear_from_os_type_test.h"
//
///*
//	  { DELITE THIS 
//	int width_x = 0;
//	int x_axis_thickness() {  return 0;  } 
//	int indent = 0;
//	int y_axis_thickness = 0;
//	void goto_coords(Dot none) {  } ;
//	int shift = 0;
//	int shift_h = 0;
//	  } DELITE THIS  
//*/
// //main // main // main // main // main // main // main // main // main // main // main // main // main // main // main // main
// //main // main // main // main // main // main // main // main // main // main // main // main // main // main // main // main
//
//int main() { 
//
//	// {  test create & call base handwritten "libs"
//	Ray a;
//	Matrix b;
//	Dot c;
//	Triangle d;
//	//  }  test create & call base handwritten "libs"
//
//
//	// { start dialoge
//	int OS;
//	std::cout << "Choise OS:\n \t1 Win, \n \t2 Ubuntu: \n";
//	std::cin >> OS;
//	std::string path_in;
//	std::string path_out;
//
//	switch (OS) { 
//	case 1: { 
//		path_in = {  "points.txt"  } ;
//		path_out = {  "out2.txt"  } ;
//		break;
//	 } 
//	case 2: { 
//		path_in = {  "Tiangle_RE/points.txt"  } ;
//		path_out = {  "Tiangle_RE/out2.txt"  } ;
//		break;
//	 } 
//	default: { 
//		std::cout << "PROGRAM OVER\n";
//		return 0;
//	 } 
//	 } 
//
//	std::cout << "Choise mode:\n \t1 input on file, \n \t2 input manual: \n \t3 auto:\n";
//	int input_switch;
//	std::cin >> input_switch;
//	std::cin.ignore(MAX_STREAMSIZE, '\n');
//
//	if (input_switch != 1 && input_switch != 2 && input_switch != 3) { 
//		std::cout << "PROGRAM OVER\n";
//		return 0;
//	 } 
//
//	std::ifstream infile(path_in);
//	std::ofstream outfile(path_out);
//	size_t n_points;
//
//	std::istream& input = input_switch == 1 ? infile : std::cin;
//
//	if (input_switch == 2 || input_switch == 3)
//		std::cout << "Enter number of points:\n";
//
//	input >> n_points;
//
//	if (input_switch == 2)
//		std::cout << "Enter points:\n";
//
//	int max_x = MIN_;
//	int max_y = MIN_;
//	int min_x = MAX_;
//	int min_y = MAX_;
//
//	Dot* point_arr = new Dot[n_points];
//
//	for (size_t i = 0; i < n_points; i++) { 
//		Dot temp;
//
//		if (input_switch == 3) { 
//			//(rand()%range)±shift
//			srand(time(NULL) + (rand() % 225000));
//			temp.x = (rand() % 76) + (-38);  // 76 -38
//			//Sleep(1000);
//			srand(time(NULL) + (rand() % 155000));
//			temp.y = (rand() % 60) + (-30);  // 60 - 30
//			std::cout << temp.x << " " << temp.y << "\n";
//		 } 
//		else { 
//			input >> temp.x >> temp.y;
//		 } 
//
//		if (temp.x > max_x)
//			max_x = temp.x;
//		if (temp.y > max_y)
//			max_y = temp.y;
//
//		if (temp.x < min_x)
//			min_x = temp.x;
//		if (temp.y < min_y)
//			min_y = temp.y;
//
//		point_arr[i] = temp;
//	 } 
//	
//	clear_cls(OS);
//
//	//  } start dialoge
//
//
//	int t1 = clock();
//
//
//	// { work with Dot arr, to create triangle and find max insade point
//	Triangle* triangle_arr = new Triangle[1 * 2 * 3 * (n_points - 2) * (n_points - 1) * n_points];  // 1*2*3*(n_points-2)*(n_points-1)*n_points;
//	size_t n_triangles = 0;
//	for (size_t i = 0; i < n_points; i++) 
//	{
//		for (size_t j = i + 1; j < n_points; j++)  //!!! < n
//		{
//			for (size_t k = j + 1; k < n_points; k++)  //!!! < n
//			{
//				Triangle temp_abc = d.create_triangle(point_arr[i], point_arr[j], point_arr[k]);
//
//				if (isEqual(temp_abc.get_area(), 0))
//					break;
//
//				if (temp_abc.is_triangle()) { 
//					triangle_arr[n_triangles] = temp_abc;
//					++n_triangles;
//				 } 
//			 } 
//		 } 
//	 } 
//
//	Triangle* final_triangle_arr = new Triangle[n_triangles];
//	for (size_t i = 0; i < n_triangles; i++)
//		final_triangle_arr[i] = triangle_arr[i];
//	delete[] triangle_arr;
//
//	size_t hit = 0;
//	for (size_t i = 0; i < n_triangles; i++) { 
//		for (size_t j = 0; j < n_points; j++)
//			if (d.is_inside(point_arr[j], final_triangle_arr[i])) { 
//				final_triangle_arr[i].add_point_at_vector(point_arr[j]);
//			 } 
//	 } 
//
//	delete[] point_arr;
//	size_t max_dot = 0;
//	size_t max_dot_index;
//	for (size_t i = 0; i < n_triangles; i++) { 
//		if (final_triangle_arr[i].get_dot_counter() > max_dot) { 
//			max_dot = final_triangle_arr[i].get_dot_counter();
//			max_dot_index = i;
//		 } 
//		d.triangles_print_outfile(final_triangle_arr, n_triangles, path_out);
//	 } 
//	final_triangle_arr[max_dot_index].print();
//	size_t cout_cntr = 15;
//
//	// } work with Dot arr, to create triangle and find max insade point
//
//
//
//	//draw_line_2(final_triangle_arr[max_dot_index].get_A(), final_triangle_arr[max_dot_index].get_B(), ZERO);
//	//draw_line_2(final_triangle_arr[max_dot_index].get_B(), final_triangle_arr[max_dot_index].get_C(), ZERO);
//	//draw_line_2(final_triangle_arr[max_dot_index].get_C(), final_triangle_arr[max_dot_index].get_A(), ZERO);
//	//end.y += 17; // set cursor under y Axys
//	//goto_coords(end);
//	//std::cout << "\n";
//	//system("pause");
//	////std::cin.get();
//
//
//
//
//
//	//Dot ORIGIN;
//
//	//Dot point_1;
//	//Dot point_2;
//
//	//	/*Dot point_1;*/
//	//	//std::cin >> point_1.x >> point_1.y;
//	//	/*Dot point_2;*/
//	//	//std::cin >> point_2.x >> point_2.y;
//
//	//	point_1.x = max_x;
//	//	point_1.y = max_y;
//	//	point_2.x = min_x;
//	//	point_2.y = min_y;
//
//	//	double round_a_x = round(point_1.x, step_is(coefficient));
//	//	double round_a_y = round(point_1.y, step_is(coefficient));
//	//	double round_b_x = round(point_2.x, step_is(coefficient));
//	//	double round_b_y = round(point_2.y, step_is(coefficient));
//
//	//	ORIGIN.x = fabs(point_2.x) > fabs(point_1.x) ? fabs(point_2.x) : fabs(point_1.x);  // abs > fabs
//	//	ORIGIN.y = fabs(point_2.y) > fabs(point_1.y) ? fabs(point_2.y) : fabs(point_1.y);  // abs > fabs
//
//	//	ORIGIN.x = round(ORIGIN.x, step_is(coefficient())) / step_is(coefficient());
//	//	ORIGIN.y = round(ORIGIN.y, step_is(coefficient())) / step_is(coefficient());
//
//	//	if (coefficient() <= 2)
//	//		width_x(4);
//	//	else
//	//		width_x(7);
//	//	std::cout << std::fixed;
//
//	//	if (coefficient() >= 3)
//	//		std::cout << std::setprecision(2);
//	//	else
//	//		std::cout << std::setprecision(0);
//
//	//	
//	//	for (int j = -(ORIGIN.y); j < ORIGIN.y + 1; j++) 
//	//	{  // axis Y
//	//		setCursorPosition(set_pos_x(ORIGIN.x), ORIGIN.y + j);  //+2 äëÿ ïå÷àòè ïî öèôðå â setw
//	//		std::cout << fabs(j * step_is(coefficient())) << "\n";
//	//	 } 
//	//	for (int i = -(ORIGIN.x); i < ORIGIN.x + 1; i++)  // axis X
//	//	{
//	//		Dot pos;
//	//		pos.x = set_pos_x(ORIGIN.x+i);
//	//		pos.y = ORIGIN.y;
//	//		goto_coords_(pos);
//	//		std::cout << fabs(i * step_is(coefficient())) << "\n";
//	//	 } 
//	//	std::cout << "\n";
//
//
//	//end.y = (ORIGIN.y*2)+5; // set cursor under y Axys
//	//goto_coords(end);
//	//std::cout << "\n";
//	//system("pause");
//	//std::cin.get();
//	
//
//
//
//
//
//	try
//	{
//		std::cout << "\n";
//		Dot P_a; P_a.x = 10; P_a.y = -10;
//		Dot P_b; P_b.x = 3; P_b.y = 3;
//		Dot P_c; P_c.x = 10; P_c.y = -11;
//		Triangle test_Triangle_;
//		test_Triangle_ = test_Triangle_.create_triangle(P_a, P_b, P_c);
//
//		while (true) { 
//			Corner(test_Triangle_, 1, true, false);
//			std::cout << "\n";
//			std::cin.get();
//			clear_cls(OS);
//			Corner(test_Triangle_, 1, true, true);;
//			std::cout << "\n";
//			std::cin.get();
//			clear_cls(OS);
//			Axys(test_Triangle_, 1, true, true);
//			std::cout << "\n";
//			std::cin.get();
//			clear_cls(OS);
//			Axys(test_Triangle_, 1, true, false);
//			std::cout << "\n";
//			std::cin.get();
//			clear_cls(OS);
//		 } 
//	 } 
//	catch (const std::runtime_error& exception)
//	{
//		std::cout << "exception :  " << exception.what() << std::endl;
//	 } 
//
//
//	return 0;
// } 
