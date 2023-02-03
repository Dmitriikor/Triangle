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

int get_distance_between(int min_coord, int max_coord);

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

	Coordinate ORIGIN_;

	int width_x_;
	int width_y_;

	int axis_x_indents_;
	int axis_x_strings_;

	int width_x_with_indent_;
	int width_y_with_indent_;

	int coefficient;

	void max_min_init();
	void initialize_width();

	void x_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;
	void y_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;

	void add_line_points_to_arr_(const Dot& A, const Dot& B, bool is_round = true, char symbol = '+'); //add point to arr for print
	void update_min_max_by(const Dot& pt);
	//void set_min_max(size_t from, size_t to);
	//bool is_point_in_arr(const Dot& pt);

	void remove_no_rounding_line(const Dot& A, const Dot& B);
	void remove_rounding_line(const Dot& A, const Dot& B);

	Ray<Dot> calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol = '+');
	Ray<Dot> calculate_line_swap(const Dot& A, const Dot& B, char symbol = '+');

	bool check_and_insert_point(const Dot& pt);

public:
	Canvas_console();

	Canvas_console& operator+=(const Canvas_console& other);
	Canvas_console operator+(const Canvas_console& other) const;

	void insert(const Dot& pt);
	void insert(const Ray<Point>& points, char symbol = '.');
	void insert(const Ray<Dot>& points); //!!! so it is possible, but it is not necessary here => overload

	void add_line(const Dot& A, const Dot& B, char symbol); //!!! is_round

	void remove_line(const Dot& A, const Dot& B);
	void remove_point(const Dot& dl);

	//!!! TO DO: добавить обычную печать
	void print() const {}
};







#endif //!  HELLO_H__