
#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>
#include <limits>

#include "Ray_3_test.h"
#include "Point_test.h"
#include "Matrix_test.h"
#include "Is_equal_test.h"

#include "utilities.h"

void go_debug(bool is_debug = false);




void initialize_min_max_points(const Ray_3_& points);
void initialize_width();
void hello_try_set_min_max_by(Point pt, bool save_point = true);

void create_corner();
void canvas_print_zero();
void canvas_clear();

void draw_points_(bool is_need_to_draw_line = false, bool is_axys = false);




void draw_points();
void draw_line();

 
void erase_point(Point err);
void delite_line(const Point& A, const Point& B);
void delite_point(const Point& dl);
 

 
Ray_3_ calculate_line_round(const Point& A, const Point& B,  char symbol = '+');
Ray_3_ calculate_line_swap(const Point& A, const Point& B,  char symbol = '+');


void draw_line_1_(const Point& A, const Point& B, bool is_round = true,  char symbol = '+');


void create_axys(char axys_arr_fill_symbol = ' ');
//void draw_points_for_axys(bool is_need_to_draw_line);

void max_min_init();


void print_arr();

void draw_points_(bool is_need_to_draw_line, bool is_axys, canvas_axys&);

class canvas_axys
{
	friend void draw_points_(bool is_need_to_draw_line, bool is_axys, canvas_axys&);
	friend void draw_points_(bool is_need_to_draw_line, bool is_axys);
	friend void x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	friend void y_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);

public:

	void create_axys(char axys_arr_fill_symbol);

	void delite_axys()
	{
		axys_arr.clear_matrix();
	}

	void print_axys()
	{
		axys_arr.Matrix_print();
	}

	void draw_axys_lines()
	{
		draw_points_(true, true);
	}

	void draw_axys_points()
	{
		draw_points_(false, true);
	}
 
private:

	Matrix axys_arr;

	void set_at(Coordinates cell, char symbol) 
	{ 
		axys_arr.set_at(cell.i, cell.j, symbol); 
	}

};


#endif //!  HELLO_H__