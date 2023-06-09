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

 /**
	 @brief  main главная функция
	 @param  argc - none
	 @param  argv - none
	 @retval      -  при успехе вернет 0
 **/
int main(int argc, char const* argv[])
{
	setlocale(LC_ALL, "Russian");	//! @param setlocale(LC_ALL, "Russian") - принудительно устанавливает локаль

	Array<int> q;

	q.add_to_Array(9);
	q.add_to_Array(8);
	q.add_to_Array(7);
	q.add_to_Array(6);
	q.add_to_Array(5);
	q.add_to_Array(4);
	q.add_to_Array(3);
	q.add_to_Array(2);
	q.add_to_Array(1);
	q.add_to_Array(0);
	q.printArray();
	q.remove_from_Array(1);
	q.printArray();
	q.add_to_Array(-999);
	q.printArray();

	return 1;

	std::cout << "\n" << "2" << "\n";

	/**
	 * @brief Объявление интерфейса
	 */
	 //Interface window;
	 /**
	  * @brief скрытие консоли
	  */

	Ray<int> empty0;

	if (empty0.empty() == true)
		std::cout << "empty0 start= " << empty0.empty() << "\n";

	empty0.add_to_back(0);

	if (empty0.empty() == false)
		std::cout << "empty0 add_to_back= " << empty0.empty() << "\n";

	empty0.remove(0);

	if (empty0.empty() == true)
		std::cout << "empty0 remove= " << empty0.empty() << "\n";

	empty0.add_to_first(0);

	if (empty0.empty() != true)
		std::cout << "empty0 add_to_first= " << empty0.empty() << "\n";

	std::cout << "\ntest_START\n";
	TEST::test_0();
	TEST::test_1();
	TEST::test_2();
	TEST::test_3();
	TEST::test_4();
	TEST::test_5();
	//TEST::test_6();
	//TEST::test_7();
	TEST::test_9();
	std::cout << "\ntest_END\n";

	/**///window.HideConsoleWindow();

	/**
	 * @brief запуск тестовой функции
	 */
	 //window.test_nana();
	 //window.ShowConsoleWindow();
	 //window.st_diag();

	 /**
	 * @brief запуск таймера
	 *
	 */
	 //time_t t1 = clock();													//! @param time_t t1 - запуск таймера, засекаем время

	 //Triangle_hi Fin_Triangle;
	 //Fin_Triangle = Find_Triangle(point_arr, n_points);

	 //Ray<Dot> copy_to_print;
	 //if (Find_Triangle.get_dot_counter() != 0)
	 //{
	 //	Corner out_print;

	 //	out_print.insert(Fin_Triangle.get_point_array(), '*');

	 //	//  for (size_t i = 0; i < Fin_Triangle.size_point_array(); i++)
	 //	//	copy_to_print.add_to_back(Fin_Triangle.get_point(i));

	 //	out_print.insert(copy_to_print);
	 //	out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_b(), '*');
	 //	out_print.insert_line(Fin_Triangle.get_b(), Fin_Triangle.get_c(), '*');
	 //	out_print.insert_line(Fin_Triangle.get_c(), Fin_Triangle.get_a(), '*');
	 //	out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_a(), '+');
	 //	out_print.render_matrix();
	 //	out_print.print();
	 //	out_print.print_to_file();

	 //	Axys a_out_print;
	 //	a_out_print += out_print;
	 //	a_out_print.render_matrix();
	 //	a_out_print.print();
	 //	a_out_print.insert_line({ 10,10 }, { -10,-10 }, '*');
	 //	a_out_print.render_matrix();
	 //	a_out_print.print();
	 //	a_out_print.remove_line({ 10,10 }, { -10,-10 });
	 //	a_out_print.render_matrix();
	 //	a_out_print.print();

	 //	Direct_draw ttst;
	 //	ttst.insert_line({ 0,0 }, { 0,0 }, '&');
	 //	ttst.insert_line({ 1,1 }, { 1,1 }, '/');
	 //	ttst.insert_line({ 3,1 }, { 3, 1 }, '\\');
	 //	ttst.insert_line({ 0,10 }, { 10, 0 }, '&');
	 //	ttst += out_print;
	 //	ttst.render_matrix();
	 //	ttst.print();
	 //}

	 ///**
	 // * @brief запуск второго таймера
	 // */
	 //time_t t2 = clock();
	 //std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;

	 //int AV2;
	 //std::cin >> AV2;
	return 0;
}