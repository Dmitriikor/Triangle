#include "Canvas_console.h"


void Canvas_console::update_min_max_by(const Dot& pt)
{
	bool is_update = Canvas::update_min_max_by(pt);

	if (is_update == true) {
	initialize_width();
	}
}


void Canvas_console::insert(const Dot& pt)
{
	if (check_and_insert_point(pt))
	{
		update_min_max_by(pt);
		////initialize_width(); //!!!
		isMatrixCalculated = false; //!!!
	}
}

void Canvas_console::insert(const Ray<Point>& points, char symbol)
{
	bool isInserted = false;

	size_t length_arr = points.size();
	for (size_t i = 0; i < length_arr; i++)
		if (Canvas::check_and_insert_point(Dot(points[i], symbol)))
		{
			update_min_max_by(points[i]);

			isInserted = true;
		}

	if (isInserted)
	{
		////initialize_width(); //!!!
		isMatrixCalculated = false; //!!!
	}
}

void Canvas_console::insert(const Ray<Dot>& points)
{
	bool isInserted = false; //!!! return true / false

	size_t length_arr = points.size();
	for (size_t i = 0; i < length_arr; i++)
		if (Canvas::check_and_insert_point(points[i]))
		{
			update_min_max_by(points[i]);
			isInserted = true;
		}

	if (isInserted)
	{
		////initialize_width(); //!!!
		isMatrixCalculated = false;
	}
}

Canvas_console& Canvas_console::operator+=(const Canvas_console& other)
{
	Canvas_console::insert(other.points_to_draw_);

	return *this;
}














int get_distance_between(int min_coord, int max_coord)
{
	if (min_coord >= 0 && max_coord >= 0)
		return abs(max_coord);

	if (min_coord <= 0 && max_coord <= 0)
		return abs(min_coord);

	return abs(max_coord) + abs(min_coord);
}

Canvas_console::Canvas_console() :Canvas()
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



void Canvas_console::x_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const
{
	size_t N = axis_length;

	for (size_t i = 0; i < N; i++)
	{
		int temp_x = min_x + i;

		arr.set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1u), '|');

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
			arr.set_at(axis_location, (width_y_with_indent_ + (i * width_x_with_indent_) + j) - 1, '-');
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

			arr.set_at(i, axis_location + j, '0' + digit);

			abs_y = abs_y / 10;
			if (abs_y == 0)
				break;
		}

		if (j == -1)
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_Y");

		if (temp_y < 0) {
			arr.set_at(i, (0ll + axis_location + j) - 1, '-');
		}
	}
}










// TO DO
////void Axys::erase_point_from_axys(Dot& err) const
////{
////	//erase_point(err, Canvas_Matrix);
////}
