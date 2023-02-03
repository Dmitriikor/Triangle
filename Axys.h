#pragma once

#ifndef AXYS_H__

#define  AXYS_H__

#include "Canvas.h"
#include "Point.h"
#include "Ray.h"
#include "Matrix.h"

class Axys : public Canvas_console
{
public:
	///void set_at(Coordinate cell, char symbol);
	///void erase_point_from_axys(Dot& err) const;
	void create(char axys_arr_fill_symbol = ' ');
	void remove();
	void print() const;

private:
	friend void prepare(Axys & this_);
	void draw_points();
	std::string outfile_adress = "Axys_out.txt";
	Matrix<char> axys_arr_;

	template <typename T>
	void draw_points_or_line_axys(Ray<T>& loc_arr_to_draw, Matrix<char>& loc_arr);

	//friend void print_f_a(Axys& this_);
};

#endif //!  AXYS_H__


