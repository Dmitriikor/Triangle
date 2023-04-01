#include "Interface.h"
HWND consoleWindow;


/**
	@fn    on_button_click
	@brief выводит в консоль текст
**/
void  Interface::on_button_click() const
{
	std::cout << "Button clicked!" << std::endl;
	
}

/**
	@fn    on_button_click_2
	@brief принимает по ссылке  nana::label и выводит в нем текст
	@param lbl_for_button_funct - ссылка на nana::label в котором будет выведено сообщение
**/
void Interface::on_button_click_2(nana::label& lbl_for_button_funct)
{
	lbl_for_button_funct.caption("Button was clicked");
	std::cout << "Button clicked-2!" << std::endl;
}


/**
    @fn    Interface
    @brief Interface object constructor  HWND_consoleWindow = GetConsoleWindow() - захватывает окно консоли в переменную consoleWindow, типа \a HWND 
**/
Interface::Interface()
{
	consoleWindow = GetConsoleWindow();
	n_points = -1;
}


/**
    @fn    hideConsoleWindow
    @brief ::ShowWindow(consoleWindow, SW_HIDE) - присваивает переменную консоли и скрывает ее 
**/
void Interface::HideConsoleWindow(/*HWND consoleWindow*/) {
	consoleWindow = GetConsoleWindow();
	::ShowWindow(consoleWindow, SW_HIDE);
}

/**
    @fn     ShowConsoleWindow
    @brief  ::ShowWindow(consoleWindow, SW_SHOW) - показывает консоль
**/
void Interface::ShowConsoleWindow(/*HWND consoleWindow*/) {
	::ShowWindow(consoleWindow, SW_SHOW); //! @param ShowWindow(consoleWindow, SW_SHOW) - на объекте \a consoleWindow меняем статус на \a SW_SHOW показывая скрытую консоль
}



//! \warning В param ЗАМЕНЯТЬ ПРОБЕЛЫ НА ALT+255 
void sleep(size_t num = 2000)
{
Sleep(num);		 //! @param Sleep() - стандартная функция сна
}

void cin_ignore()
{
std::cin.ignore(MAX_STREAMSIZE_2, '\n');								//! @param std::cin.ignore - игнорирует ранее введенные символы, требует действия
}

void clear_screen()
{
	system("cls");
}

