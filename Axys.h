#pragma once

#ifndef AXYS_H__

#define  AXYS_H__

#include "Canvas.h"
#include "Point.h"
#include "Ray.h"
#include "Matrix.h"

class  Axys : public Canvas_console
{
public:

	void create(char axys_arr_fill_symbol = ' ');
	void remove();
	void print() const;

private:

	friend void prepare_(Axys & this_);

	void draw_points();
	std::string outfile_adress = "Axys_out.txt";
	//mutable Matrix<char> Canvas_Matrix;

	 
	void draw_points_or_line_axys(Ray<Dot>& loc_arr_to_draw, Matrix<char>& loc_arr);

	//friend void print_f_a(Axys& this_);
};

#endif //!  AXYS_H__


