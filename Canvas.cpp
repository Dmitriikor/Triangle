#include "Canvas.h"
#include <string>
#include <float.h>



Canvas_console::Canvas_console()
{
	ORIGIN_.i = 0;
	ORIGIN_.j = 0;
	width_x_ = -1;
	width_y_ = -1;

	axis_x_indents_ = 1;
	axis_x_strings_ = 1;

	width_x_with_indent_ = -1;
	width_y_with_indent_ = -1;

	coefficient = 1;
	debug = false;
}


void Canvas_console::max_min_init()
{
	MAX_VIRTUAL_.x = DBL_MIN;
	MAX_VIRTUAL_.y = DBL_MIN;

	MIN_VIRTUAL_.x = DBL_MAX;
	MIN_VIRTUAL_.y = DBL_MAX;
}

void Canvas_console::go_debug(bool is_debug)
{
	debug = is_debug;
}



void Canvas_console::insert(Ray<Dot> points)
{
	size_t length_arr = points.size();
	for (size_t i = 0; i < length_arr; i++)
	{
		check_and_insert_point(points[i]);
	}

	set_min_max(); //!!! max and min is from this or other (NOT checking ALL OF IT)

	initialize_width(); //!!! same 
}

////void Canvas_console::insert_l(Ray<Dot>& points)
////{
////	size_t length_arr = points.size();
////	for (size_t i = 0; i < length_arr; i++)
////	{
////		check_and_insert_point(points[i]);
////	}
////
////	set_min_max(); //!!! max and min is from this or other (NOT checking ALL OF IT)
////
////	initialize_width(); //!!! same 
////}

void Canvas_console::update_min_max_by(const Dot& pt)
{
	size_t old_long = points_to_draw_.size();

	check_and_insert_point(pt);
	if (old_long == points_to_draw_.size())
		return;

	bool is_update = false;
	if (pt.x > MAX_VIRTUAL_.x) {
		MAX_VIRTUAL_.x = pt.x;
		is_update = true;
	}
	if (pt.y > MAX_VIRTUAL_.y) {
		MAX_VIRTUAL_.y = pt.y;
		is_update = true;
	}
	if (pt.x < MIN_VIRTUAL_.x) {
		MIN_VIRTUAL_.x = pt.x;
		is_update = true;
	}
	if (pt.y < MIN_VIRTUAL_.y) {
		MIN_VIRTUAL_.y = pt.y;
		is_update = true;
	}
	if (is_update == true){
		initialize_width();
	}
}

void Canvas_console::check_and_insert_point(const Dot& pt)
{
	size_t length = points_to_draw_.size();
	for (size_t i = 0; i < length; i++)
	{
		if (points_to_draw_[i] == pt)
		{
			return;
		}
	}

	points_to_draw_.add_to_back(pt);
}

bool Canvas_console::is_point_in_arr(const Dot& pt)
{
	size_t length = points_to_draw_.size();
	for (size_t i = 0; i < length; i++)
	{
		if (points_to_draw_[i] == pt)
		{
			return true;
		}
	}
	return false;
}

void Canvas_console::initialize_width() {
	width_x_ = 1;
	width_y_ = 1;

	if (MIN_VIRTUAL_.y < 0)
		width_y_++;

	if (MIN_VIRTUAL_.x < 0)
		width_x_++;

	int x = abs(MAX_VIRTUAL_.x) > abs(MIN_VIRTUAL_.x) ? abs(MAX_VIRTUAL_.x) : abs(MIN_VIRTUAL_.x);
	while (x >= 10) {
		x = x / 10;
		width_x_++;
	}

	int y = abs(MAX_VIRTUAL_.y) > abs(MIN_VIRTUAL_.y) ? abs(MAX_VIRTUAL_.y) : abs(MIN_VIRTUAL_.y);
	while (y >= 10) {
		width_y_++;
		y = y / 10;
	}

}

int Canvas_console::get_distance_between(int min_coord, int max_coord) const
{
	if (min_coord >= 0 && max_coord >= 0)
		return abs(max_coord);

	if (min_coord <= 0 && max_coord <= 0)
		return abs(min_coord);

	return abs(max_coord) + abs(min_coord);
}

void Canvas_console::x_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const 
{
	size_t N = axis_length;

	for (size_t i = 0; i < N; i++)
	{
		int temp_x = min_x + i;

		//!!!
		///arr[axis_location][width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1)] = '|';
		arr.set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1Ui64), '|');

		int abs_x = fabs(temp_x);
		int j;
		for (j = width_x_with_indent_ - 2; j >= 0; --j)
		{
			int digit = abs_x % 10;


			arr.set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + j, '0' + digit);

			abs_x = abs_x / 10;

			if (abs_x == 0)
				break;
		}

		if (j == -1)
		{
			arr.print();
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_X");
		}


		if (temp_x < 0)
			arr.set_at(axis_location, (width_y_with_indent_ + (i * width_x_with_indent_) + j) - 1, '-'); //!!! here was [i][1]
	}
}

void Canvas_console::y_axis_filling(Matrix<char>& arr, size_t axis_length, int start_i, int axis_location) const 
{
	for (size_t i = 0; i < axis_length; ++i)
	{
		int temp_y = start_i - i;

		int abs_y = fabs(temp_y);
		int j;
		for (j = width_y_with_indent_ - 1; j >= 0; --j)
		{
			int digit = abs_y % 10;

			//arr[i][axis_location + j] = '0' + digit;
			arr.set_at(i, axis_location + j, '0' + digit);

			abs_y = abs_y / 10;
			if (abs_y == 0)
				break;
		}

		if (j == -1)
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_Y");

		if (temp_y < 0) {
			//arr[i][(axis_location + j) - 1] = '-'; //!!! here was [i][1]
			arr.set_at(i, (0ll + axis_location + j) - 1, '-'); //!!! here was [i][1]
		}

		//else
			//corner_arr()[i][j - 1] = ' '; //!!! here was [i][1]
	}
}


void Canvas_console::add_lines(const Dot& A, const Dot& B, char symbol)
{
	update_min_max_by(A);
	update_min_max_by(B);

	add_point_to_arr_for_print_line(A, B, true, symbol);
}

void Canvas_console::set_min_max()
{
	size_t length = points_to_draw_.size();
	MAX_VIRTUAL_ = static_cast<Point>(points_to_draw_[0]);	 
									 

	MIN_VIRTUAL_ = static_cast<Point>(points_to_draw_[0]);  
										 

	for (size_t i = 1; i < length; i++)
	{
		// TO DO
		// 
		//points_to_draw_[i].symbol = '+'; // Kostilvaniay to do


		if (points_to_draw_[i].x > MAX_VIRTUAL_.x)
			MAX_VIRTUAL_.x = points_to_draw_[i].x;
		else if (points_to_draw_[i].x < MIN_VIRTUAL_.x)
			MIN_VIRTUAL_.x = points_to_draw_[i].x;

		if (points_to_draw_[i].y > MAX_VIRTUAL_.y)
			MAX_VIRTUAL_.y = points_to_draw_[i].y;
		else if (points_to_draw_[i].y < MIN_VIRTUAL_.y)
			MIN_VIRTUAL_.y = points_to_draw_[i].y;
	}
}






// TO DO
////void Axys::erase_point_from_axys(Dot& err) const
////{
////	//erase_point(err, axys_arr_);
////}


double get_step(unsigned coefficient)
{
	double step = 1.0 / coefficient;
	return step;
}


void Canvas_console::remove_point(const Dot& dot)
{
	//!!! REMOVE_FIRST_POINT_FROM_RAY(dot, line_points_to_draw()); -- NO CLASS MEMBER
	for (size_t i = 0; i < points_to_draw_.size(); i++)
	{
		if (dot == points_to_draw_[i])
		{
			points_to_draw_.remove(i);
			break;
		}
	}
}

void Canvas_console::remove_rounding_line(const Dot& A, const Dot& B)
{
	Ray<Dot> erase_line_arr;

	erase_line_arr = calculate_line_with_rounding(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}

void Canvas_console::remove_no_rounding_line(const Dot& A, const Dot& B)
{
	Ray<Dot> erase_line_arr;

	erase_line_arr = calculate_line_swap(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}


void Canvas_console::remove_line_total(const Dot& A, const Dot& B)
{
	remove_no_rounding_line(A, B);
	remove_rounding_line(A, B);
}

void Canvas_console::add_point_to_arr_for_print_line(const Dot& A, const Dot& B, bool is_round, char symbol)
{
	const Ray<Dot>& lockal_draw_line_arr = is_round ? calculate_line_with_rounding(A, B, symbol) : calculate_line_swap(A, B, symbol);

	size_t length = lockal_draw_line_arr.size();

	for (size_t i = 0; i < length; i++)
	{
		points_to_draw_.add_to_back(lockal_draw_line_arr[i]);
	}
}

Ray<Dot> Canvas_console::calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol)
{
	Ray<Dot> lockal_line_arr;

	Dot coords;

	double min = A.x;
	double max = B.x;
	if (A.x > B.x) {
		min = B.x;
		max = A.x;
	}

	if (utilities::isEqual(min, max))
	{
		double start = A.y;
		double end = B.y;
		if (A.y < B.y) {
			start = B.y;
			end = A.y;
		}
		double step = get_step(coefficient);  /// 1.0 / coefficient;
		Dot point;
		point.x = A.x;
		for (double y = start; y >= end; y -= step)
		{
			point.y = y;

			point.x = (int)utilities::round_by_step(point.x, step);
			point.y = (int)utilities::round_by_step(point.y, step);


			point.symbol = symbol;
			lockal_line_arr.add_to_back(point);
		}
		return lockal_line_arr;
	}

	double k = (B.y - A.y) / (B.x - A.x);
	double b_ = k * A.x;
	double b = A.y - b_;

	double step = get_step(coefficient);  /// 1.0 / coefficient;

	double rounded_min = utilities::round_by_step(min, step);
	double rounded_max = utilities::round_by_step(max, step);

	unsigned N = (rounded_max - rounded_min) / step + 1;

	for (int i = 0; i < N; ++i)
	{
		Dot point;
		point.x = rounded_min + i * step;
		point.y = k * point.x + b;

		point.x = (int)utilities::round_by_step(point.x, step);
		point.y = (int)utilities::round_by_step(point.y, step);

		point.symbol = symbol;
		lockal_line_arr.add_to_back(point);
	}

	return lockal_line_arr;

	lockal_line_arr.clear(); //!!! unreachable code

	if (debug) {
		size_t length = points_to_draw_.size();
		for (size_t i = 0; i < length; i++)
		{
			std::cout << "\n" << points_to_draw_[i].x << " : " << points_to_draw_[i].y;
		}
	}
}


Ray<Dot> Canvas_console::calculate_line_swap(const Dot& A, const Dot& B, char symbol)
{
	Ray<Dot> lockal_line_arr;

	if (A.x == B.x && A.y == B.y)
	{
		return calculate_line_with_rounding(A, B);
	}

	int x1, y1, x2, y2;
	x1 = A.x;
	y1 = A.y;
	x2 = B.x;
	y2 = B.y;

	bool is_swap = false;
	if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
		std::swap(x1, y1);
		std::swap(x2, y2);
		is_swap = true;
	}
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	for (int x = x1; x <= x2; x++) {
		float k = (x - x1) / (float)(x2 - x1);
		float y = y1 * (1. - k) + y2 * k;


		double step = get_step(coefficient);
		y = (int)utilities::round_by_step(y, step);

		Dot coords;
		coords.symbol = symbol;

		if (is_swap) {
			coords.x = y;
			coords.y = x;

			lockal_line_arr.add_to_back(coords);
		}
		else {
			coords.x = x;
			coords.y = y;
			lockal_line_arr.add_to_back(coords);
		}
	}
	return lockal_line_arr;
}


