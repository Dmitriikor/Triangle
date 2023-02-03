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
	void change_file_path(const std::string& adress);
	void print() const;
	void print(std::ostream& output) const;
	void print_zero();
	void clear();

private:
	mutable Matrix<char> corner_arr_;
	mutable bool isMatrixCalculated;

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
	friend void print(Corner& this_);
};
