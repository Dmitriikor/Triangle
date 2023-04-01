#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <functional>
#include <iomanip>
#include <fstream>
std::streamsize static const MAX_STREAMSIZE_2 = std::numeric_limits<std::streamsize>::max();

#include "utilities.h"
#include "Ray.h"
#include "Point.h"

/**
* @file Windows.h
* @brief #include "Windows.h"
* только в конце, иначе портит max
*/
#include "Windows.h"


class Interface
{
	//! \warning В param ЗАМЕНЯТЬ ПРОБЕЛЫ НА ALT+255 

public:
	void HideConsoleWindow(/*HWND consoleWindow*/);
	void ShowConsoleWindow();
	void on_button_click()const;
	void on_button_click_2(nana::label& lbl_for_button_funct)const;
	Ray<Dot> point_arr;
	size_t n_points;										//! @param n_points - задаем количество точек из которых будем пытаться создать треугольники




	void test_nana()
	{
		std::string input_to_string = "привет мир";						//! @param std::string input_to_string = "привет мир" - инициализированная "привет мир" строка для использования в gui 
		nana::form form;												//! @param nana::form form - создаем форму(окно)  \a form с помощью
		form.caption(input_to_string);									//! @param form.caption(input_to_string) - захватывает 
		nana::label lbl(form, nana::rectangle(10, 10, 200, 25));		//! @param nana::label lbl(form, nana::rectangle(10, 10, 200, 25)) - @brief создает \a nana::label \a lbl с заданными размерами и местоположением 
		lbl.caption(input_to_string);									//!  @param lbl.caption(input_to_string) - захватываем в  \a lbl данные из \a input_to_string 
		nana::button button(form, nana::rectangle(10, 40, 200, 25));					//! @param nana::button button - создаем с заданными размерами и местоположением
		button.caption("Нажми меня!");									//! @param button.caption("Нажмя меня!")   захватываем в  \a button текст "Нажми меня!"  
		
		/*
		Основная принципиальная разница между подходами заключается в том, что лямбда-выражение может захватывать контекст, 
		в котором оно было создано, включая локальные переменные и this-указатель, в то время как функция-член класса не может этого делать. 
		В вашем случае, вероятно, функция-член класса on_button_click() не может быть связана с событием, потому что она не имеет доступа к this-указателю.
		При использовании лямбда-выражения для связывания функции-члена класса с событием, лямбда-выражение захватывает указатель на объект класса, 
		через который было вызвано лямбда-выражение, и использует этот указатель для вызова функции-члена. Это позволяет лямбда-выражению вызывать 
		функцию-член класса с правильным this-указателем.
		С другой стороны, когда вы передаете указатель на функцию-член класса непосредственно в метод connect(), этот указатель на функцию не 
		может захватить this-указатель, поскольку он не имеет контекста, в котором был создан. Поэтому, когда этот указатель на функцию будет вызван в 
		ответ на событие, он не сможет получить доступ к членам класса через this-указатель.
		Кроме того, при использовании лямбда-выражения для связывания функции-члена класса с событием, вы можете не использовать указатель на 
		функцию-член класса напрямую, что может сделать код более понятным и удобочитаемым.
		В целом, использование лямбда-выражения для связывания функции-члена класса с событием является более гибким подходом, 
		который позволяет захватывать контекст и делать код более понятным, поэтому он может быть предпочтительнее в некоторых случаях. 
		Однако, в некоторых ситуациях, использование указателей на функции-члены класса может быть более удобным и подходящим.
		*/
		button.events().click([this]() { on_button_click(); });
		//button.events().click(&Interface::on_button_click);				//! @param button.events().click(on_button_click) - @brief создаем эвент для отслеживания нажатия на кнопку \a button
		
		
		
		nana::label lbl_for_button(form, nana::rectangle(10, 70, 200, 25));  //! @param nana::label lbl_for_button - @brief \a lbl_for_button


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
		//button.events().click(std::bind(on_button_click_2, std::ref(lbl_for_button_funct)));  //! @param button.events().click(std::bind_front(on_button_click_2, std::ref(lbl_for_button_funct))) - создаем эвент который по клику вызывает функцию и передает в нее ссылку \a nana::label
		button.events().click([this, &lbl_for_button_funct](){ on_button_click_2(lbl_for_button_funct);});
		form.show();
		nana::exec();

	}

	Interface();


	void st_diag()
	{
		while (true)
		{
			if (n_points == -1)
			{
				std::cout << "Enter number of points:\n";
				std::cin >> n_points;
			}
			if (n_points >= 3)
				break;
			else {
				Sleep(1500);
				system("cls");
				std::cout << "The number of points to build a triangle must be at least 3 \n";
				std::cin >> n_points;
			}

		}

		std::cout << "Choose mode:\n";
		std::cout << "\t 1 input on file, \n";
		std::cout << "\t 2 input manual,  \n";
		std::cout << "\t 3 automatically generate random points \n";

		std::string path_in = { "points.txt" };							//! @param path_in - выбираем откуда будем брать список точек
		std::string path_out = { "out.txt" };							//! @param path_out - выбираем путь сохранения для треугольника

		int input_switch;
		//input_switch = 3;

		std::cin >> input_switch;

		std::cin.ignore(MAX_STREAMSIZE_2, '\n');

		if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
			std::cout << "PROGRAM OVER\n";
			return;
		}

		std::ifstream infile(path_in);
		std::ofstream outfile(path_out);

		std::istream& input = input_switch == 1 ? infile : std::cin;

		if (input_switch == 2)
			std::cout << "Enter points:\n";



		if (input_switch == 1)
			std::cout << "\n \tAttention! Only the above quantity will be taken from the file \n\n";

		for (size_t i = 0; i < n_points; i++) {							//! @param for temp - Генерируем точки с помощью функции utilities::random_INT
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


		int case_to_output_file_patch_switch;							//! @param case_to_output_file_patch_switch - выбираем путь откуда будем брать список точек и куда сохраним выходные треугольники
		std::cout << "Choise input and output file settings:\n";
		std::cout << "\t 1 Take file from root folder, \n";
		std::cout << "\t 2 Or inter manual path : \n";

		//case_to_output_file_patch_switch = 1;

		std::cin >> case_to_output_file_patch_switch;

		switch (case_to_output_file_patch_switch)
		{
		case 1:
		{
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
			return;
		}
		}

	}

private:


};