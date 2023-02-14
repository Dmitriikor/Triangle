//#pragma once

#ifndef Corner_H__

#define  Corner_H__

#include "Canvas_console.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>


class Corner : public Canvas_console
{
public:
	void fill(char fill_symbol);
	void change_file_path(const std::string& address);
	///void print() const;
	void print(std::ostream& output = std::cout) const;
	void print_to_file() const;
	void add_zero_point();
	void clear();

private:
	void prepare(std::ostream& output)const;

	friend void prepare_free(std::ostream& output, Corner& this_);
	
	std::string outfile_adress = "Corner_out.txt";

	void draw_points_or_line_corner() const; //not for public mb move to Canvas
	void add_points_to_corner() const;
	void create(char axys_arr_fill_symbol = ' ') const;
	void erase_point_from_corner(const Dot& err);
	Matrix<char>& corner_arr() 
	{
		return Canvas_Matrix;
	}
	///friend void print(Corner& this_);
};
#endif //!  Corner_H__
