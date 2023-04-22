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

#pragma execution_character_set("utf-8")


#include "TESTS.h"
#include "Interface.h"


/**
	@brief  main главная функция
	@param  argc - none
	@param  argv - none
	@retval      -  при успехе вернет 0
**/
int main(int argc, char const* argv[])
{
	setlocale(LC_ALL, "Russian");	//! @param setlocale(LC_ALL, "Russian") - принудительно устанавливает локаль 





	std::cout << "\n" << "2" << "\n";





	/**
	 * @brief Объявление интерфейса
	 */
	Interface window;
	/**
	 * @brief скрытие консоли
	 */

	std::cout << "\ntest_START\n";
	TEST t_1;
	t_1.test_0();
	t_1.test_1();
	t_1.test_2();
	t_1.test_3();
	t_1.test_4();
	t_1.test_5();
	//t_1.test_6();
	//t_1.test_7();
	std::cout << "\ntest_END\n";
	/**///window.HideConsoleWindow();

	/**
	 * @brief запуск тестовой функции
	 */
	window.test_nana();
	window.ShowConsoleWindow();
	window.st_diag();

	/**
 	* @brief запуск таймера
 	* 
 	*/
	time_t t1 = clock();													//! @param time_t t1 - запуск таймера, засекаем время

	Triangle_hi Fin_Triangle;
	Fin_Triangle = Find_Triangle(window.point_arr, window.n_points);


	Ray<Dot> copy_to_print;
	if (Fin_Triangle.get_dot_counter() != 0)
	{
		Corner out_print;

		out_print.insert(Fin_Triangle.get_point_array(), '*');

		//  for (size_t i = 0; i < Fin_Triangle.size_point_array(); i++)
		//	copy_to_print.add_to_back(Fin_Triangle.get_point(i));

		out_print.insert(copy_to_print);
		out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_b(), '*');
		out_print.insert_line(Fin_Triangle.get_b(), Fin_Triangle.get_c(), '*');
		out_print.insert_line(Fin_Triangle.get_c(), Fin_Triangle.get_a(), '*');
		out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_a(), '+');
		out_print.render_matrix();
		out_print.print();
		out_print.print_to_file();

		Axys a_out_print;
		a_out_print += out_print;
		a_out_print.render_matrix();
		a_out_print.print();
		a_out_print.insert_line({ 10,10 }, { -10,-10 }, '*');
		a_out_print.render_matrix();
		a_out_print.print();
		a_out_print.remove_line({ 10,10 }, { -10,-10 });
		a_out_print.render_matrix();
		a_out_print.print();


		Direct_draw ttst;
		ttst.insert_line({ 0,0 }, { 0,0 }, '&');
		ttst.insert_line({ 1,1 }, { 1,1 }, '/');
		ttst.insert_line({ 3,1 }, { 3, 1 }, '\\');
		ttst.insert_line({ 0,10 }, { 10, 0 }, '&');
		ttst += out_print;
		ttst.render_matrix();
		ttst.print();
	}

	/**
	 * @brief запуск второго таймера
	 */
	time_t t2 = clock();
	std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;

	int AV2;
	std::cin >> AV2;
	return 0;
}
