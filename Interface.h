#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>


#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <functional>
#include <iomanip>
#include <fstream>

#include "utilities.h"
#include "Ray.h"
#include "Point.h"
std::streamsize static const MAX_STREAMSIZE = std::numeric_limits<std::streamsize>::max();

/**
* @file Windows.h
* @brief #include "Windows.h"
* только в конце, иначе портит max
*/
#include "Windows.h"

struct pos_elem
{
	//first
	int X_horizontal;

	//second
	int Y_vertical;

	//third
	int width_in_pixels;

	//fourth
	int height_in_pixels;
};


class Interface
{
	//! \warning В param ЗАМЕНЯТЬ ПРОБЕЛЫ НА ALT+255 

public:
	void HideConsoleWindow(/*HWND consoleWindow*/);
	void ShowConsoleWindow();
	static void on_button_click();
	void on_button_click_2(nana::label& lbl_for_button_funct)const;
	Ray<Dot> point_arr;
	size_t n_points ;										//! @param n_points - задаем количество точек из которых будем пытаться создать треугольники
	HWND consoleWindow;


	void test_nana()
	{

		
		nana::form form{ nana::API::make_center(960+40, 480+40) };
			nana::place layout(form);

			nana::button button1(form, "Button 1");
			nana::button button2(form, "Button 2");

		//nana::form form{ nana::size{ 960, 480 } };	//! @param nana::form form - создаем форму(окно)  \a form с помощью
		{
			RECT desktop_rect;
			SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop_rect, 0);

			RECT console_rect;
			GetWindowRect(consoleWindow, &console_rect);
			int console_width = console_rect.right - console_rect.left;
			int console_height = console_rect.bottom - console_rect.top;

			int x = (desktop_rect.right - console_width) / 2;
			int y = (desktop_rect.bottom - console_height) / 2;

			SetWindowPos(consoleWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}

		nana::label lbl{ form, nana::rectangle(10, 10, 100, 25) };
		nana::button button{ form, nana::rectangle(10, 10, 100, 25) };
		nana::textbox textbox{ form, nana::rectangle(10, 10, 100, 25) };
		pos_elem test;

		button.size(nana::size(100, 50));

		test.X_horizontal = 10;
		test.Y_vertical = 10;





		std::string input_to_string = "привет мир - 0";					//! @param std::string input_to_string = "привет мир" - инициализированная "привет мир" строка для использования в gui 
		
		
		
		
		form.caption(input_to_string);									//! @param form.caption(input_to_string) - захватывает 

		lbl.move(nana::rectangle(test.X_horizontal, test.Y_vertical, test.width_in_pixels = 200, test.height_in_pixels = 25)); // создание прямоугольника);
		lbl.caption(input_to_string);									//!  @param lbl.caption(input_to_string) - захватываем в  \a lbl данные из \a input_to_string 

		button.move(nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, test.width_in_pixels, test.height_in_pixels));										//! @param nana::button button - создаем с заданными размерами и местоположением
		button.caption("Нажми меня! дважды");							//! @param button.caption("Нажмя меня!")   захватываем в  \a button текст "Нажми меня!"  

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
		button.events().click(&Interface::on_button_click);				//! @param button.events().click(on_button_click) - @brief создаем эвент для отслеживания нажатия на кнопку \a button

		nana::label lbl_for_button(form, nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, test.width_in_pixels, test.height_in_pixels));  //! @param nana::label lbl_for_button - @brief \a lbl_for_button


		button.events().click([&]()
			{
				lbl_for_button.caption("Button was clicked");
			});

		nana::label lbl_for_button_funct(form, nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, test.width_in_pixels, test.height_in_pixels)); //! @param nana::rectangle(100, 10, 200, 25) - создаем квадрат, задаем размер и положение

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
		button.events().click([this, &lbl_for_button_funct]() { on_button_click_2(lbl_for_button_funct); });

		nana::checkbox checkbox{ form, "Checkbox" };

		checkbox.move(nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, test.width_in_pixels, test.height_in_pixels));


		checkbox.events().click([&] {
			std::cout << "The checkbox is " << (checkbox.checked() ? "checked" : "unchecked") << std::endl;
			});

		textbox.move(nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, 500, 40));

		//size_t n;

		caption_text(form, textbox, test);



		//n_points = n;

		layout.div(
			"vert margin=10 gap=10 <weight=90>"
			"<weight=20><hight=10><button>"
			"<weight=20> <button1>"
			"<weight=20> <button2>"
		);
		layout["button"] << button1;
		layout["button1"] << button2;
		layout["button2"] << button;
		layout.collocate();

		std::cout << "+-+\n";
		form.show();
		nana::exec();
	}

	Interface();

	void caption_text(nana::form& form, nana::textbox& textbox, struct pos_elem test)
	{
		textbox.events().text_changed([&](const nana::arg_textbox& arg)
			{
				try
				{
					std::string text = arg.widget.caption();

					if (text == "")
						return;

					n_points = std::stoi(text);

					if (std::to_string(n_points) != text)
						throw std::invalid_argument("Wrong characters!");

					std::cout << n_points << std::endl;

					if (n_points < 3)
					{
						textbox.tip_string("The number of points to build a triangle must be at least 3");
						textbox.reset();
					}

				}
				catch (const std::invalid_argument& err)
				{
					n_points = 0;
					std::cerr << "Invalid argument: " << err.what() << std::endl;
				}
			});
		textbox.caption(std::to_string(n_points));
	}


	void st_diag()
	{
	//	std::cout << "Choose mode:\n";
	//	std::cout << "\t 1 input on file, \n";
	//	std::cout << "\t 2 input manual,  \n";
	//	std::cout << "\t 3 automatically generate random points \n";

	//	std::string path_in = { "points.txt" };							//! @param path_in - выбираем откуда будем брать список точек
	//	std::string path_out = { "out.txt" };							//! @param path_out - выбираем путь сохранения для треугольника

	//	int input_switch;
	//	//input_switch = 3;

	//	std::cin >> input_switch;

	//	std::cin.ignore(MAX_STREAMSIZE, '\n');

	//	if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
	//		std::cout << "PROGRAM OVER\n";
	//		return;
	//	}

	//	std::ifstream infile(path_in);
	//	std::ofstream outfile(path_out);

	//	std::istream& input = input_switch == 1 ? infile : std::cin;

	//	if (input_switch == 2)
	//		std::cout << "Enter points:\n";



	//	if (input_switch == 1)
	//		std::cout << "\n \tAttention! Only the above quantity will be taken from the file \n\n";

	//	for (size_t i = 0; i < n_points; i++) {							//! @param for temp - Генерируем точки с помощью функции utilities::random_INT
	//		Dot temp;

	//		if (input_switch == 3) {
	//			temp.x = utilities::random_INT(-20, 20);
	//			temp.y = utilities::random_INT(-20, 20);
	//		}
	//		else {
	//			input >> temp.x >> temp.y;
	//		}
	//		point_arr.add_to_back(temp);
	//	}


	//	int case_to_output_file_patch_switch;							//! @param case_to_output_file_patch_switch - выбираем путь откуда будем брать список точек и куда сохраним выходные треугольники
	//	std::cout << "Choise input and output file settings:\n";
	//	std::cout << "\t 1 Take file from root folder, \n";
	//	std::cout << "\t 2 Or inter manual path : \n";

	//	//case_to_output_file_patch_switch = 1;

	//	std::cin >> case_to_output_file_patch_switch;

	//	switch (case_to_output_file_patch_switch)
	//	{
	//	case 1:
	//	{
	//		break;
	//	}
	//	case 2:
	//	{
	//		//std::getline (std::cin,name);
	//		std::cout << "\n Enter path_in \n\t";
	//		std::getline(std::cin, path_in);
	//		std::cout << "\n Enter path_out \n\t";
	//		std::getline(std::cin, path_out);
	//		break;
	//	}
	//	default:
	//	{
	//		std::cout << "PROGRAM OVER\n";
	//		return;
	//	}
	//	}

	}

private:


};
