#pragma once

#include "nana/gui.hpp"
#include "nana/gui/widgets/label.hpp"
#include "nana/gui/widgets/button.hpp"
#include "nana/gui/widgets/checkbox.hpp"
#include "nana/gui/widgets/textbox.hpp"
#include "nana/gui/place.hpp"


#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
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

struct r_data
{
	Ray<Dot> arrs;
	size_t points;
};

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
	void  win_cl(nana::form& form);
	void on_button_click_2(nana::label& lbl_for_button_funct)const;
	//! @param n_points - задаем количество точек из которых будем пытаться создать треугольники
	HWND consoleWindow;
	Ray<Dot> point_arr;
	size_t n_points;
	bool checkbox_bool;
	int input_switch = -1;



	r_data test_nana()
	{


		nana::form form{ nana::API::make_center(350, 430) };
		nana::place layout(form);

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

		nana::label lbl0{ form, nana::rectangle(10, 10, 200, 50) };
		nana::label lbl{ form, nana::rectangle(10, 10, 100, 25) };
		//nana::button button{ form, nana::rectangle(10, 10, 100, 25) };
		nana::button button2{ form, nana::rectangle(10, 10, 100, 25) };
		nana::textbox textbox{ form, nana::rectangle(10, 10, 100, 25) };
		pos_elem test;

		//button.size(nana::size(100, 50));
		button2.size(nana::size(100, 50));
		test.X_horizontal = 10;
		test.Y_vertical = 10;

		//счет запусков, неважно
		char str[100];
		{
			FILE* fp;
			int num;
			fp = fopen("FILE", "r");

			if (fp == NULL) {
				fp = fopen("FILE", "w");
				fprintf(fp, "%d", 0);
				fclose(fp);
				fp = fopen("FILE", "r");
			}
			fgets(str, 100, fp);
			num = atoi(str);
			num++;
			fclose(fp);
			fp = fopen("FILE", "w");
			fprintf(fp, "%d", num);
			fclose(fp);
		}
		std::cout << "\n" << str << " ";
		{
			const std::string FILENAME = "FILE_2";
			int number;

			std::ifstream input(FILENAME);
			if (input.is_open()) { // проверяем, удалось ли открыть файл
				input >> number; // считываем число из файла
				input.close();
			}

			std::ofstream output(FILENAME);
			if (output.is_open()) { // проверяем, удалось ли открыть файл
				output << number + 1; // записываем увеличенное значение числа в файл
				output.close();
			}
			std::cout << "\n" << number << "\n";
			if (number != std::stoi(str))
				std::cout << "\nerror num != std::stoi(str)\n" << number << "\n" << std::stoi(str) << "\n";
		}

		std::string input_to_string = "привет мир - ";					//! @param std::string input_to_string = "привет мир" - инициализированная "привет мир" строка для использования в gui 
		input_to_string += str;
		form.caption(input_to_string);									//! @param form.caption(input_to_string) - захватывает 

		lbl0.move(nana::rectangle(test.X_horizontal, test.Y_vertical, test.width_in_pixels = 250, test.height_in_pixels = 50)); // создание прямоугольника);
		lbl0.caption("Введите в textbox значение количества точек и нажмите Enter"); //!  @param lbl.caption(input_to_string) - захватываем в  \a lbl данные из \a input_to_string 
		//button.move(nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, test.width_in_pixels, test.height_in_pixels));										//! @param nana::button button - создаем с заданными размерами и местоположением
		//button.caption("Нажми меня! дважды");							//! @param button.caption("Нажмя меня!")   захватываем в  \a button текст "Нажми меня!"  
		//button.events().click([this]() { on_button_click(); });
		//button.events().click(&Interface::on_button_click);				//! @param button.events().click(on_button_click) - @brief создаем эвент для отслеживания нажатия на кнопку \a button
		//nana::label lbl_for_button(form, nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, test.width_in_pixels, test.height_in_pixels));  //! @param nana::label lbl_for_button - @brief \a lbl_for_button
		//button.events().click([&]()
		//	{
		//		lbl_for_button.caption("Button was clicked");
		//	});

		nana::label lbl_for_button_funct(form, nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, test.width_in_pixels, test.height_in_pixels)); //! @param nana::rectangle(100, 10, 200, 25) - создаем квадрат, задаем размер и положение

		//button.events().click(std::bind(on_button_click_2, std::ref(lbl_for_button_funct)));  //! @param button.events().click(std::bind_front(on_button_click_2, std::ref(lbl_for_button_funct))) - создаем эвент который по клику вызывает функцию и передает в нее ссылку \a nana::label
		//button.events().click([this, &lbl_for_button_funct]() { on_button_click_2(lbl_for_button_funct); });
		nana::checkbox checkbox{ form, "Редактировать" };
		textbox.move(nana::rectangle(test.X_horizontal, test.Y_vertical += test.height_in_pixels, 180, 40));
		checkbox.move(nana::rectangle(test.X_horizontal + 190, test.Y_vertical += 10, test.width_in_pixels, test.height_in_pixels));
		checkbox.events().click([&] {
			std::cout << "The checkbox is " << (checkbox.checked() ? "checked" : "unchecked") << std::endl;
			checkbox_bool = checkbox.checked();
			});



		caption_text(form, textbox, test);

		r_data get_b;
		get_b.points = -1;
		//n_points = n;

		test.Y_vertical = test.Y_vertical + 50;
		// Создание группы 1
		nana::checkbox checkbox1(form, nana::rectangle(test.X_horizontal, test.Y_vertical + test.height_in_pixels + 10, 150, 25));
		nana::checkbox checkbox2(form, nana::rectangle(test.X_horizontal, test.Y_vertical + test.height_in_pixels + 40, 150, 25));
		nana::checkbox checkbox3(form, nana::rectangle(test.X_horizontal, test.Y_vertical + test.height_in_pixels + 70, 150, 25));
		// Создание группы 2
		nana::checkbox checkbox4(form, nana::rectangle(test.X_horizontal + 200, test.Y_vertical + test.height_in_pixels + 10, 150, 25));
		nana::checkbox checkbox5(form, nana::rectangle(test.X_horizontal + 200, test.Y_vertical + test.height_in_pixels + 40, 150, 25));
		nana::checkbox checkbox6(form, nana::rectangle(test.X_horizontal + 200, test.Y_vertical + test.height_in_pixels + 70, 150, 25));
		// Подписи
		lbl.move(nana::rectangle(test.X_horizontal, test.Y_vertical, test.width_in_pixels = 200, test.height_in_pixels = 25));
		lbl.caption("Выберите режим:");

		nana::radio_group group;
		group.add(checkbox1);
		group.add(checkbox2);
		group.add(checkbox3);
		group.add(checkbox4);
		group.add(checkbox5);
		group.add(checkbox6);
		checkbox1.caption("input on file");
		checkbox2.caption("generate random");
		checkbox3.caption("Checkbox 3");
		checkbox4.caption("Checkbox 4");
		checkbox5.caption("Checkbox 5");
		checkbox6.caption("Checkbox 6");
		// Переменные состояний для каждого чекбокса
		bool state1 = false;
		bool state2 = false;
		bool state3 = false;
		bool state4 = false;
		bool state5 = false;
		bool state6 = false;
		// Привязка состояний к переменным
		checkbox1.check(state1);
		checkbox2.check(state2);
		checkbox3.check(state3);
		checkbox4.check(state4);
		checkbox5.check(state5);
		checkbox6.check(state6);
		// Функции обратного вызова для каждого чекбокса
		checkbox1.events().click([&]() {
			state1 = checkbox1.checked();
			input_switch = 1;
			});

		checkbox2.events().click([&]() {
			state2 = checkbox2.checked();
			input_switch = 3;
			});

		checkbox3.events().click([&]() {
			state3 = checkbox3.checked();
			});

		checkbox4.events().click([&]() {
			state4 = checkbox4.checked();
			});

		checkbox5.events().click([&]() {
			state5 = checkbox5.checked();
			});

		checkbox6.events().click([&]() {
			state6 = checkbox6.checked();
			});
		//кнопка запуска
		button2.move(nana::rectangle(test.X_horizontal, test.Y_vertical + test.height_in_pixels + 150, test.width_in_pixels, test.height_in_pixels));										//! @param nana::button button - создаем с заданными размерами и местоположением
		button2.caption("Выполнить");
		button2.events().click([&]()
			{
				std::string text_value;
				text_value = textbox.caption();
				n_points = std::stoi(text_value);
				if (input_switch != -1 && n_points >= 3)
				{
					get_b = st_diag();
					win_cl(form);
					system("cls");
				}
			});

		form.show();
		nana::exec();
		return get_b;
	}

	Interface();

	void caption_text(nana::form& form, nana::textbox& textbox, struct pos_elem test)
	{
		textbox.multi_lines(false);

		textbox.events().key_press([&](const nana::arg_keyboard& arg)
			{
				if (checkbox_bool)
				{
					textbox.editable(true);
				}
				if (arg.key == nana::keyboard::enter)
				{
					std::string text = textbox.caption();

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
					else
						textbox.editable(false);
				}
			});
	}

	r_data st_diag()
	{
		r_data back;
		back.points = 0;
		//std::cout << "\t input n_points \n";
		//std::cin >> n_points;
		//std::cout << n_points << std::endl;
		//	std::cout << "Choose mode:\n";
		//std::cout << "\t 1 input on file, \n";
		//std::cout << "\t 2 input manual,  \n";
		//std::cout << "\t 3 automatically generate random points \n";
		std::string path_in = { "points.txt" };							//! @param path_in - выбираем откуда будем брать список точек
		std::string path_out = { "out.txt" };							//! @param path_out - выбираем путь сохранения для треугольника
		//input_switch = 3;
		//std::cin >> input_switch;
		//std::cin.ignore(MAX_STREAMSIZE, '\n');
		if (input_switch != 1 && input_switch != 2 && input_switch != 3) {
			std::cout << "PROGRAM OVER\n";
			return back;
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

		case_to_output_file_patch_switch = 1;

		//std::cin >> case_to_output_file_patch_switch;

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
			return back;
		}
		}

		back.arrs = point_arr;
		back.points = n_points;
		return back;
	}

private:


};
