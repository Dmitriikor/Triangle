#pragma once
#include "Canvas.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>


class Corner : public Canvas_console
{
public:
	void fill(char fill_symbol);
	void remove(const Dot& dot_to_erase);
	void remove_line(const Dot& A, const Dot& B);
	void change_file_path(std::string& adress);
	void print();
	void print_zero();
	void clear();

private:
	Matrix<char> corner_arr_;
	std::string outfile_adress = "Corner_out.txt";
	template <typename T>
	void draw_points_or_line_corner(Ray<T>& loc_arr_to_draw, Matrix<char>& loc_arr); //not for public mb move to Canvas
	void add_points_to_corner();
	void create(char axys_arr_fill_symbol = ' ');
	void erase_point_from_corner(const Dot& err);
	Matrix<char>& corner_arr() 
	{
		return corner_arr_;
	}
	friend void print_f(Corner& this_);
};
