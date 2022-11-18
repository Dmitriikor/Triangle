
#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>
#include <limits>

#include "Ray_3_test.h"
#include "Point_test.h"
#include "Matrix_test.h"
#include "Is_equal_test.h"

#include "utilities.h"

 class  canvas
{
	//friend class corner;
	//friend class axys;
	//class corner;

protected:
	Point MAX_VIRTUAL_;
	Point MIN_VIRTUAL_;

	Coordinates ZERO_;
	Coordinates ORIGIN_;

	Ray_3_ points_to_draw_;		//свободные точки для рисования
	Ray_3_ line_points_to_draw_;	//точки линий для рисования

	Matrix corner_arr_;
	Matrix axys_arr_;

	int width_x_ = -1;
	int width_y_ = -1;

	int axis_x_indents_ = 1;
	int axis_x_strings_ = 1;

	int width_x_with_indent_;
	int width_y_with_indent_;

	int coefficient = 1;

	bool debug;
	void set_at(Coordinates cell, char symbol )
	{
		axys_arr_.set_at(cell.i, cell.j, symbol);
	}

	void max_min_init();
	void initialize_width();


	void x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	void y_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	int get_distance_between(int min_coord, int max_coord);
	//void draw_points_(bool is_need_to_draw_line, bool is_axys, Matrix& TT);
	void add_point_to_arr_for_print_line(const Point& A, const Point& B, bool is_round = true, char symbol = '+'); //add point to arr for print
	void update_min_max_by(Point pt);
	void set_min_max();


	//--------------------------------------------------------------------------------------------
	Ray_3_& points_to_draw()
	{
		return 	points_to_draw_;
	}

	Ray_3_& line_points_to_draw()
	{
		return 	line_points_to_draw_;
	}

	Point& MAX_VIRTUAL()
	{
		return MAX_VIRTUAL_;
	}

	Point& MIN_VIRTUAL()
	{
		return MIN_VIRTUAL_;
	}

	int& width_x()
	{
		return width_x_;
	}

	int& width_y()
	{
		return width_y_;
	}

	int& width_x_with_indent()
	{
		return width_x_with_indent_;
	}

	int& width_y_with_indent()
	{
		return width_y_with_indent_;
	}

	int& axis_x_indents()
	{
		return axis_x_indents_;
	}


	int& axis_x_strings()
	{
		return axis_x_strings_;
	}

	Coordinates& ZERO()
	{
		return ZERO_;
	}
	Coordinates& ORIGIN()
	{
		return  ORIGIN_;
	}

	Matrix& axys_arr()
	{
		return axys_arr_;
	}

	Matrix& corner_arr()
	{
		return corner_arr_;
	}

	//--------------------------------------------------------------------------------------------

	Ray_3_ calculate_line_round(const Point& A, const Point& B, char symbol = '+');
	Ray_3_ calculate_line_swap(const Point& A, const Point& B, char symbol = '+');

public:

	void add_points(const Ray_3_& points);
	void insert(Point& pt)
	{
		update_min_max_by(pt);
	}

	void erase_point(Point& err);
	void delite_line(const Point& A, const Point& B);
	void delite_point(const Point& dl);

	void print()
	{
		//void max_min_init();
		//void initialize_width();
		//

	}
	void go_debug(bool is_debug = false);
};




class corner : protected canvas
{
	//friend class canvas;

private:
	void draw_points_or_line_corner(Ray_3_& loc_arr_to_draw, Matrix& loc_arr);
	void add_points_to_corner(/*canvas& this_*/);
	void add_lines_to_corner(/*canvas& this_*/);
	
public:
	void create(/*canvas& this_,*/ char axys_arr_fill_symbol= ' ');
	void delite(/*canvas& this_*/);
	void print(/*canvas& this_*/)
	{
		/*this_.*/corner_arr().Matrix_print();
	}

	void add_lines(const Point& A, const Point& B, bool is_round, char symbol/*, canvas& this_*/);
	void print_zero(/*canvas& this_*/);
	void print_to_file(std::ostream& output)
	{
		corner_arr().print_to_file(output);
	}
};


 
class axys : protected canvas
{
	//friend class canvas;

private:

	void draw_points_or_line_axys(Ray_3_& loc_arr_to_draw, Matrix& loc_arr);
public:
	void create(/*canvas& this_,*/ char axys_arr_fill_symbol = ' ');
	void delite(/*canvas& this_*/)
	{
		/*this_.*/axys_arr().clear_matrix();
	}
	void print(/*canvas& this_*/)
	{
		/*this_.*/axys_arr().Matrix_print();
	}
	void draw_lines(/*canvas& this_*/);
	void draw_points(/*canvas& this_*/);
	void print_to_file(std::ostream& output)
	{
		axys_arr().print_to_file(output);
	}
};


#endif //!  HELLO_H__