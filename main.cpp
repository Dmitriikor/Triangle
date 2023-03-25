/**

    @file      Main.cpp
    @brief     
    @details   ~
    @author    Dmitrii
    @date      19.03.2023
    @copyright © Dmitrii, 2023. All right reserved.

**/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <exception>
#include <utility>

/**
 * @brief Глобальная переменная, инициализирующаяся до функции main.
 *
 * Данная переменная используется для хранения настроек приложения.
 */
std::streamsize static const MAX_STREAMSIZE = std::numeric_limits<std::streamsize>::max();

#include "Canvas.h"
#include "Point.h"
#include "Triangle.h"
#include "utilities.h"
#include "Ray.h"
#include "Matrix.h"
#include "Find_Triangle.h"
#include "Corner.h"
#include "Axys.h"
#include "Direct_draw.h"

#include <codecvt>
#include <string>
#include <locale>

#pragma execution_character_set("utf-8")

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>


/**
* @file Windows.h
* @brief #include "Windows.h" 
* только в конце, иначе портит max
*/
#include "Windows.h"



/**
    @fn    on_button_click
    @brief выводит в консоль текст
**/
void on_button_click()
{
	std::cout << "Button clicked!" << std::endl;
}

/**
    @fn    on_button_click_2
    @brief принимает по ссылке  nana::label и выводит в нем текст
    @param lbl_for_button_funct - ссылка на nana::label в котором будет выведено сообщение
**/
void on_button_click_2(nana::label &lbl_for_button_funct)
{
	lbl_for_button_funct.caption("Button was clicked");
	std::cout << "Button clicked-2!" << std::endl;
}





/**
    @brief  main
    @param  argc - none
    @param  argv - none
    @retval      -  при успехе вернет 0
**/
int main(int argc, char const* argv[])
{

																		//! \warning В param ЗАМЕНЯТЬ ПРОБЕЛЫ НА ALT+255 

	setlocale(LC_ALL, "Russian");										//! @param setlocale(LC_ALL, "Russian") - принудительно устанавливает локаль 
	HWND consoleWindow = GetConsoleWindow();							//! @param HWND_consoleWindow = GetConsoleWindow() - захватывает окно консоли в переменную consoleWindow, типа \a HWND 
	::ShowWindow(consoleWindow, SW_HIDE);								//! @param ::ShowWindow(consoleWindow, SW_HIDE) - принимает переменную консоли и скрывает ее 
						 
	try
		{
		std::string input_to_string = "привет мир";						//! @param std::string input_to_string = "привет мир" - инициализированная "привет мир" строка для использования в gui 
		nana::form form;												//! @param nana::form form - создаем форму(окно)  \a form с помощью
		form.caption(input_to_string);									//! @param form.caption(input_to_string) - захватывает 
		nana::label lbl(form, nana::rectangle(10, 10, 200, 25));		//! @param nana::label lbl(form, nana::rectangle(10, 10, 200, 25)) - @brief создает \a nana::label \a lbl с заданными размерами и местоположением 
		lbl.caption(input_to_string);									//!  @param lbl.caption(input_to_string) - захватываем в  \a lbl данные из \a input_to_string 
		nana::button button(form, nana::rectangle(10, 40, 200, 25));	//! @param nana::button button - создаем с заданными размерами и местоположением
		button.caption("Нажми меня!");									//! @param button.caption("Нажмя меня!")   захватываем в  \a button текст "Нажми меня!"  
		button.events().click(on_button_click);							//! @param button.events().click(on_button_click) - @brief создаем эвент для отслеживания нажатия на кнопку \a button
		nana::label lbl_for_button (form, nana::rectangle(10, 70, 200, 25));  //! @param nana::label lbl_for_button - @brief \a lbl_for_button
		button.events().click([&]() 
			{
				lbl_for_button.caption("Button was clicked");			 
			});

		nana::label lbl_for_button_funct(form, nana::rectangle(100, 10, 200, 25)); //! @param nana::rectangle(100, 10, 200, 25) - создаем квадрат, задаем размер и положение
		/*
			std::bind позволяет создавать новый функциональный объект, который принимает меньше аргументов, чем исходная функция. 
			Функция-адаптер std::bind позволяет привязать аргументы к вызову функции, сохраняя свободные аргументы, 
			которые можно передать позже.
		
			std::bind_front - это новая функция в стандарте C++20. Она работает похоже на std::bind, но в отличие от std::bind, 
			привязывает аргументы к началу списка аргументов функции, а не к концу. Это позволяет создавать функциональные объекты с
			фиксированными значениями начальных аргументов, оставляя свободными только конечные аргументы.

			Порядок привязки аргументов в std::bind и std::bind_front имеет значение. 
			В std::bind порядок привязанных аргументов соответствует порядку передачи аргументов при вызове функции. 
			В std::bind_front порядок привязанных аргументов соответствует порядку перечисления аргументов функции в определении.

			std::bind принимает все аргументы по значению, в то время как std::bind_front принимает аргументы по ссылке. 
			Кроме того, в std::bind_front можно передавать только первые аргументы функции, а остальные будут переданы при вызове связанной функции. 
			Это может быть полезно, если вы хотите задать значения для некоторых параметров функции заранее, а остальные параметры будут переданы при выполнении.

			foo(int a, int b, int c)

			auto func = std::bind_front(&foo, 1, 2, 3);

			auto func = std::bind(&foo, 3, std::placeholders::_1, 2, std::placeholders::_2, 1);
		*/
		button.events().click(std::bind_front(on_button_click_2, std::ref(lbl_for_button_funct)));  //! @param button.events().click(std::bind_front(on_button_click_2, std::ref(lbl_for_button_funct))) - создаем эвент который по клику вызывает функцию и передает в нее ссылку \a nana::label

		form.show();
		nana::exec();

	} catch (const std::runtime_error& exception)
		{
			std::cout << "\n\texception :  " << exception.what() << std::endl;
		}

		Sleep(2000);														//! @param Sleep(2000) - стандартная функция сна
		::ShowWindow(consoleWindow, SW_SHOW);								//! @param ShowWindow(consoleWindow, SW_SHOW) - на объекте \a consoleWindow меняем статус на \a SW_SHOW показывая скрытую консоль
		std::cin.ignore(MAX_STREAMSIZE, '\n');								//! @param std::cin.ignore - игнорирует ранее введенные символы, требует действия

	
	while (true) { 

		time_t t1;															//! @param time_t t1 - запуск таймера, засекаем время

		try
		{
			/**
			* @brief n_points для создания треугольников
			* @details задаем количество точек из которых будем пытаться создать треугольники 
			* 
			*/
			size_t n_points = 0;											//! @param n_points - задаем количество точек из которых будем пытаться создать треугольники

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

			////case_to_output_file_patch_switch = 1;

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
				//std::getline (std::cin,name);
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
			//input_switch = 3;

			std::cin >> input_switch;


			std::cin.ignore(MAX_STREAMSIZE, '\n');

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
				out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_b(), '*');
				out_print.insert_line(Fin_Triangle.get_b(), Fin_Triangle.get_c(), '*');
				out_print.insert_line(Fin_Triangle.get_c(), Fin_Triangle.get_a(), '*');

				out_print.insert_line(Fin_Triangle.get_a(), Fin_Triangle.get_a(),'+');

				out_print.render_matrix();
				out_print.print();
				out_print.print_to_file();

				//out_print.clear();
				//out_print.insert(Fin_Triangle.get_point_array(), '+');
				//out_print.clear();



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
				//ttst.insert_line({ 0,0 }, { 0,0 }, '&');
				//ttst.insert_line({ 1,1 }, { 1,1  }, '/');
				//ttst.insert_line({ 3,1 }, { 3, 1 }, '\\');
				//ttst.insert_line({ 0,10 }, { 10, 0 }, '&');
				ttst += out_print;
				ttst.render_matrix();
				ttst.print();
			}
			int t2;
			std::cin >> t2;
		}
		catch (const std::runtime_error& exception)
		{
			std::cout << "\n\texception :  " << exception.what() << std::endl;
		}

		time_t t2 = clock();
		std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;

	int t2pause;
	////std::cin >> t2pause;
	}

	return 0;
}
