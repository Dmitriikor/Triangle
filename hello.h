#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>

#include "Ray_3_test.h"
#include "Point_test.h"
#include "Matrix_test.h"
#include "Is_equal_test.h"

#include "utilities.h"

class Canvas
{
protected:
	Point MAX_VIRTUAL_;
	Point MIN_VIRTUAL_;


	Ray_3_ points_to_draw_;		//свободные точки для рисования
	//Ray_3_ line_points_to_draw_;	//точки линий для рисования

};



class Canvas_console : public Canvas
{
protected:
	Coordinates ZERO_;
	Coordinates ORIGIN_;

	int width_x_ = -1;
	int width_y_ = -1;

	int axis_x_indents_ = 1;
	int axis_x_strings_ = 1;

	int width_x_with_indent_;
	int width_y_with_indent_;

	int coefficient = 1;

	bool debug;


	void max_min_init();
	void initialize_width();


	void x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	void y_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location);
	int get_distance_between(int min_coord, int max_coord);
	//void draw_points_(bool is_need_to_draw_line, bool is_axys, Matrix& TT);
	void add_point_to_arr_for_print_line(const Dot& A, const Dot& B, bool is_round = true, char symbol = '+'); //add point to arr for print
	void update_min_max_by(const Dot& pt);
	void set_min_max();


	//--------------------------------------------------------------------------------------------


	//Ray_3_& line_points_to_draw()
	//{
	//	return line_points_to_draw_;
	//}

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
		return ORIGIN_;
	}

	Ray_3_& points_to_draw()			//  !!!!!!
	{									//  !!!!!!
		return 	points_to_draw_;		//  !!!!!!
	}									//  !!!!!!


	//--------------------------------------------------------------------------------------------

	Ray_3_ calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol = '+');
	Ray_3_ calculate_line_swap(const Dot& A, const Dot& B, char symbol = '+');

public:
	void insert(const Ray_3_& points);
	void insert(const Dot& pt)
	{
		update_min_max_by(pt);
	}
	void add_lines(const Dot& A, const Dot& B, bool is_round, char symbol/*, Canvas& this_*/); //!!! is_round
	void remove_line_(const Dot& A, const Dot& B);
	void remove_point(const Dot& dl);

	void print()
	{
		//void max_min_init();
		//void initialize_width();
		//

	}
	void go_debug(bool is_debug = false);


};



class Corner : public Canvas_console
{
	//friend class Canvas;

private:
	Matrix corner_arr_;
	std::string outfile_adress = "corner_path_out.txt";
	void draw_points_or_line_corner(Ray_3_& loc_arr_to_draw, Matrix& loc_arr); //not for public mb move to Canvas
	void add_points_to_corner(/*Canvas& this_*/);
	void add_lines_to_corner(/*Canvas& this_*/);
	void create(/*Canvas& this_,*/ char axys_arr_fill_symbol = ' ');
	void erase_point_from_corner(const Dot& err);

	Matrix& corner_arr()
	{
		return corner_arr_;
	}
public:
	void fill(char fill_symbol)
	{
		create(fill_symbol);
	}
	//void erase_point_from_corner(Dot& err);
	void print_all(/*Canvas& this_*/)
	{
		corner_arr().clear_matrix();
		create();
		add_points_to_corner();
		add_lines_to_corner();
		/*this_.*/corner_arr().Matrix_print();
	}
	void print_point(/*Canvas& this_*/)
	{
		corner_arr().clear_matrix();
		create();
		add_points_to_corner();
		/*this_.*/corner_arr().Matrix_print();
	}
	void print_line(/*Canvas& this_*/)
	{
		corner_arr().clear_matrix();
		create();
		add_lines_to_corner();
		/*this_.*/corner_arr().Matrix_print();
	}
	void print_zero(/*Canvas& this_*/);
	void remove(const Dot& dot_to_erase)
	{
		remove_line_(dot_to_erase, dot_to_erase);
		remove_point(dot_to_erase);
		erase_point_from_corner(dot_to_erase);
	}

	void remove_line(const Dot& A, const Dot& B)
	{
		remove_line_(A, B);
	}

	void change_file_path(std::string adress)
	{
		outfile_adress = adress;
	}
	void print_to_file()
	{
		std::ofstream outfile_corner(outfile_adress);
		corner_arr().print_to_file(outfile_corner);
	}
	void clear(/*Canvas& this_*/);
};



class Axys : protected Canvas_console
{
	//friend class Canvas;

private:
	Matrix axys_arr_;

	void draw_points_or_line_axys(Ray_3_& loc_arr_to_draw, Matrix& loc_arr);
public:
	Matrix& axys_arr()
	{
		return axys_arr_;
	}
	void set_at(Coordinates cell, char symbol)
	{
		axys_arr_.set_at(cell.i, cell.j, symbol);
	}
	void erase_point_from_axys(Dot& err);
	void create(/*Canvas& this_,*/ char axys_arr_fill_symbol = ' ');
	void remove(/*Canvas& this_*/)
	{
		/*this_.*/axys_arr().clear_matrix();
	}
	void print(/*Canvas& this_*/)
	{
		/*this_.*/axys_arr().Matrix_print();
	}
	void draw_lines(/*Canvas& this_*/);
	void draw_points(/*Canvas& this_*/);
	void print_to_file(std::ostream& output)
	{
		axys_arr().print_to_file(output);
	}
};


#endif //!  HELLO_H__