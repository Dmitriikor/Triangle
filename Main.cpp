/**

	@file      Main.cpp
	@brief
	@details   ~
	@author    Dmitrii
	@date      19.03.2023
	@copyright © Dmitrii, 2023. All right reserved.

**/

#include <iostream>
#include <limits>
#include <exception>

/**
 * @brief Глобальная переменная, инициализирующаяся до функции main.
 *
 * Данная переменная используется для хранения настроек приложения.
 */

#include "Canvas.h"

#include "Triangle.h"
#include "utilities.h"
#include "Ray.h"
#include "Matrix.h"
#include "Find_Triangle.h"
#include "Corner.h"
#include "Axys.h"
#include "Direct_draw.h"
#include "Array.h"

#pragma execution_character_set("utf-8")

#include "TESTS.h"
#include "Interface.h"
#include "panel_scrolled.h"
 /**
	 @brief  main главная функция
	 @param  argc - none
	 @param  argv - none
	 @retval      -  при успехе вернет 0
 **/
int main(int argc, char const* argv[])
{

	setlocale(LC_ALL, "Russian");
	std::locale::global(std::locale("en_US.utf8"));

	Interface in_use;
	in_use.HideConsoleWindow();
	auto gets = in_use.test_nana();
	if (gets.size() == 0)
		return -99;

	//Ray<Dot> point_arr;
	//size_t n_points;
	time_t P_start;
	time_t P_end;
	time_t t_launch = clock();
	time_t t1 = clock();

	Triangle_hi Fin_Triangle;
	Fin_Triangle = Find_Triangle(gets);

	time_t t2 = clock();
	std::chrono::seconds print_to_file_timer;
	Ray<Dot> copy_to_print;
	if (Fin_Triangle.get_dot_counter() != 0)
	{
		Corner out_print;
		out_print.insert(Fin_Triangle.get_point_array(), '*');
		out_print.insert(copy_to_print);
		out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_b(), '+');
		out_print.insert_line(Fin_Triangle.get_b(), Fin_Triangle.get_c(), '+');
		out_print.insert_line(Fin_Triangle.get_c(), Fin_Triangle.get_a(), '+');
		out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_a(), '+');
		out_print.render_matrix();
		out_print.print();


		P_start = clock();
		out_print.print_to_file();
		nana_extra::test_ex corner_wind;
		corner_wind.test(out_print);
		P_end = clock();


		Axys a_out_print;
		a_out_print += out_print;
		a_out_print.render_matrix();
		a_out_print.print();
		//a_out_print.print_to_file();

		Direct_draw ttst;
		ttst += out_print;
		ttst.render_matrix();
		ttst.print();
	}
	time_t t_end = clock();
	in_use.ShowConsoleWindow();
	std::cout << "timer SE= \t" << double(t_end - t_launch) / CLOCKS_PER_SEC << std::endl;
	std::cout << "timer FT = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;
	std::cout << "timer FP = \t" << double(P_end - P_start) / CLOCKS_PER_SEC << std::endl;
	int AV2;
	std::cin >> AV2;
	return 0;
}