
#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>
#include <limits>

#include "Ray_3_test.h"
#include "Point_test.h"
#include "Matrix_test.h"
#include "Is_equal_test.h"

#include "utilities.h"

class canvas
{
	friend class corner;
	friend class axys;
	class corner;
private:
	Point MAX_VIRTUAL;
	Point MIN_VIRTUAL;

	Coordinates ZERO;
	Coordinates ORIGIN;

	Ray_3_ points_to_draw;		//ñâîáîäíûå òî÷êè äëÿ ðèñîâàíèÿ
	Ray_3_ line_points_to_draw;	//òî÷êè ëèíèé äëÿ ðèñîâàíèÿ

	Matrix corner_arr;
	Matrix axys_arr;

	int width_x = -1;
	int width_y = -1;

	int axis_x_indents = 1;
	int axis_x_strings = 1;

	int width_x_with_indent;
	int width_y_with_indent;

	int coefficient = 1;

	bool debug;

	void set_at(Coordinates cell, char symbol )
	{
		axys_arr.set_at(cell.i, cell.j, symbol);
	}

	void max_min_init();
	void initialize_width();


	void x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	void y_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	int get_distance_between(int min_coord, int max_coord);
	void draw_points_(bool is_need_to_draw_line, bool is_axys, Matrix& TT);
	void add_point_to_arr_for_print_line(const Point& A, const Point& B, bool is_round = true, char symbol = '+'); //add point to arr for print
	void try_set_min_max_by(Point pt, bool save_point = true);



public:

	Ray_3_ calculate_line_round(const Point& A, const Point& B, char symbol = '+');
	Ray_3_ calculate_line_swap(const Point& A, const Point& B, char symbol = '+');

	// & initialize_min_max_points
	void add_points(const Ray_3_& points);
	void add_point(Point pt)
	{
		try_set_min_max_by(pt, true);
	}

	void erase_point(Point err);
	void delite_line(const Point& A, const Point& B);
	void delite_point(const Point& dl);

	void print_corner() 
	{
		//void max_min_init();
		//void initialize_width();


		corner_arr.Matrix_print();
	}
	void print_corner_to_file(std::ostream& output)
	{
		corner_arr.print_to_file(output);
	}


	void print_axys()
	{
		axys_arr.Matrix_print();
	}

	void go_debug(bool is_debug = false);
};

// try use it as anonymous object
class corner
{
	friend class canvas;

private:
	
public:
	void create_corner(canvas& this_, char axys_arr_fill_symbol= ' ');
	void delite_corner(canvas& this_);
	void print_corner(canvas& this_)
	{
		this_.corner_arr.Matrix_print();
	}
	void draw_lines(canvas& this_);

	void draw_lines(const Point& A, const Point& B, bool is_round, char symbol, canvas& this_);
	void draw_points(canvas& this_);
	void corner_print_zero(canvas& this_);
};


// try use it as anonymous object
class axys
{
	friend class canvas;

private:

public:
	void create_axys(canvas& this_, char axys_arr_fill_symbol = ' ');
	void delite_axys(canvas& this_)
	{
		this_.axys_arr.clear_matrix();
	}
	void print_axys(canvas& this_)
	{
		this_.axys_arr.Matrix_print();
	}
	void draw_lines(canvas& this_);
	void draw_points(canvas& this_);
};


#endif //!  HELLO_H__