#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <stdexcept>


#include "Ray.h"
#include "Point.h"
#include "Matrix.h"
#include "Is_equal_test.h"
#include "utilities.h"

class Canvas
{
public:
	Point MAX_VIRTUAL_;
	Point MIN_VIRTUAL_;

	Ray<Dot> points_to_draw_;		//free dots to draw

};




class Canvas_console : public Canvas
{
protected:

	Coordinates_TEMPLATE ORIGIN_;

	int width_x_;
	int width_y_;

	int axis_x_indents_;
	int axis_x_strings_;

	int width_x_with_indent_;
	int width_y_with_indent_;

	int coefficient;

	bool debug;

	void max_min_init();
	void initialize_width();

	void x_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;
	void y_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;
	int get_distance_between(int min_coord, int max_coord)const;
	void add_point_to_arr_for_print_line(const Dot& A, const Dot& B, bool is_round = true, char symbol = '+'); //add point to arr for print
	void update_min_max_by(const Dot& pt);
	void set_min_max();
	bool is_point_in_arr(const Dot& pt);

	void remove_no_rounding_line(const Dot& A, const Dot& B);
	void remove_rounding_line(const Dot& A, const Dot& B);

	Coordinates_TEMPLATE& ZERO() ///!!!
	{
		return ORIGIN_;
	}
	Ray<Dot> calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol = '+');
	Ray<Dot> calculate_line_swap(const Dot& A, const Dot& B, char symbol = '+');

public:
	Canvas_console();

	//Canvas_console(const Canvas_console& other) = default; //!!! system copy-constructor

	void operator+=(const Canvas_console& other)
	{

		for (size_t i = 0; i < other.points_to_draw_.size(); i++)
		{
		points_to_draw_.add_to_back(other.points_to_draw_[i]);
		}
		if (width_x_ < other.width_x_)
			width_x_ = other.width_x_;

		if (width_y_ < other.width_y_)
			width_y_ = other.width_y_;

		if (axis_x_indents_ < other.axis_x_indents_)
			axis_x_indents_ = other.axis_x_indents_;

		if (axis_x_strings_ < other.axis_x_strings_)
			axis_x_strings_ = other.axis_x_strings_;

		if (width_x_with_indent_ < other.width_x_with_indent_)
			width_x_with_indent_ = other.width_x_with_indent_;

		if (width_y_with_indent_ < other.width_y_with_indent_)
			width_y_with_indent_ = other.width_y_with_indent_;


		if (MAX_VIRTUAL_.x < other.MAX_VIRTUAL_.x)
			MAX_VIRTUAL_.x = other.MAX_VIRTUAL_.x;

		if (MAX_VIRTUAL_.y < other.MAX_VIRTUAL_.y)
			MAX_VIRTUAL_.y = other.MAX_VIRTUAL_.y;

		if (MIN_VIRTUAL_.x > other.MIN_VIRTUAL_.x)
			MIN_VIRTUAL_.x = other.MIN_VIRTUAL_.x;

		if (MIN_VIRTUAL_.y > other.MIN_VIRTUAL_.y)
			MIN_VIRTUAL_.y = other.MIN_VIRTUAL_.y;



		//!!! ONLY HERE (Canvas)
		//set_min_max(); //!!! max and min is from this or other (NOT checking ALL OF IT)
		//initialize_width(); //!!! same 
	}

	//!!! operator + 

	
	void insert(Ray<Dot> points); //!!! so it is possible, but it is not necessary here => overload
	void insert_l(Ray<Dot>& points);

	void insert(const Dot& pt)
	{
		update_min_max_by(pt); //!!! more effective
	}

	void check_and_insert_point(const Dot& pt);
	void add_lines(const Dot& A, const Dot& B, char symbol); //!!! is_round
	void remove_line_total(const Dot& A, const Dot& B);
	void remove_point(const Dot& dl);

	virtual void print() {}
	virtual void remove_line(const Dot& A, const Dot& B) {}

	void go_debug(bool is_debug = false);


	//~Canvas_console() = default; //!!! system
};







#endif //!  HELLO_H__