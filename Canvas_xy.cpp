﻿#include "Canvas_xy.h"


int Canvas_xy::width_x() const
{
	return width_x_;
}

int Canvas_xy::width_y() const
{
	return width_y_;
}

int Canvas_xy::width_x_with_indent()
{
	return  width_x() + axis_x_indents_;
}

void Canvas_xy::width_x_with_indent(size_t size)
{
	width_x_with_indent_ = size;
}

int Canvas_xy::width_y_with_indent()
{
	return width_y() + indent;

}

void Canvas_xy::width_y_with_indent(size_t size)
{
	 width_y_with_indent_ = size;

}

int Canvas_xy::axis_x_indents() const
{
	return axis_x_indents_;
}

int Canvas_xy::axis_x_strings() const
{
	return axis_x_strings_;
}

//calculate width for printing numbers along axys
size_t Canvas_xy::get_width(int min_coord, int max_coord)
{
	size_t width = 0;

	unsigned longest_coord = abs(max_coord) > abs(min_coord) ? abs(max_coord) : abs(min_coord);
	width += get_digits_count(longest_coord);

	if (min_coord < 0)
		++width;

	return width;
}

void Canvas_xy::initialize_widthes()
{
	width_x_ = get_width(MIN_VIRTUAL().x, MAX_VIRTUAL().x);
	width_y_ = get_width(MIN_VIRTUAL().y, MAX_VIRTUAL().y);
}


void Canvas_xy::initialize_width() {
	width_x_ = 1;
	width_y_ = 1;

	if (MIN_VIRTUAL().y < 0)
		width_y_++;

	if (MIN_VIRTUAL().x < 0)
		width_x_++;

	int x = abs(MAX_VIRTUAL().x) > abs(MIN_VIRTUAL().x) ? abs(MAX_VIRTUAL().x) : abs(MIN_VIRTUAL().x);
	while (x >= 10) {
		x = x / 10;
		width_x_++;
	}

	int y = abs(MAX_VIRTUAL().y) > abs(MIN_VIRTUAL().y) ? abs(MAX_VIRTUAL().y) : abs(MIN_VIRTUAL().y);
	while (y >= 10) {
		width_y_++;
		y = y / 10;
	}

}


size_t Canvas_xy::get_digits_count(unsigned long long number)
{
	size_t count = 1;
	while (number >= 10)
	{
		++count;
		number /= 10;
	}
	return count;
}

void Canvas_xy::x_axis_filling(size_t axis_length, int min_x, int axis_location)
{
	size_t N = axis_length;

	for (int i = 0; i < N; i++)
	{
		int temp_x = min_x + i;

		Canvas_Matrix().set_at(axis_location, width_y_with_indent() + (i * width_x_with_indent()) + (width_x_with_indent() - 1u), '|');

		int abs_x = fabs(temp_x);
		int j;
		for (j = width_x_with_indent() - 2; j >= 0; --j)
		{
			int digit = abs_x % 10;

			Canvas_Matrix().set_at(axis_location, width_y_with_indent() + (i * width_x_with_indent()) + j, '0' + digit);

			abs_x = abs_x / 10;

			if (abs_x == 0)
				break;
		}

		if (j == -1)
		{
			Canvas_Matrix().print();
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_X");
		}

		if (temp_x < 0)
			Canvas_Matrix().set_at(axis_location, (width_y_with_indent() + (i * width_x_with_indent()) + j) - 1, '-');
	}
}

void Canvas_xy::y_axis_filling(size_t axis_length, int start_i, int axis_location)
{

	for (size_t i = 0; i < axis_length; ++i)
	{
		int temp_y = start_i - i;

		int abs_y = fabs(temp_y);
		int j;

		for (j = width_y_with_indent() - 1; j >= 0; --j)
		{
			int digit = abs_y % 10;

			Canvas_Matrix().set_at(i, axis_location + j, '0' + digit);

			abs_y = abs_y / 10;

			if (abs_y == 0)
				break;
		}

		if (j == -1) 
		{
			Canvas_Matrix().print();
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_Y");
		}

		if (temp_y < 0) {
			Canvas_Matrix().set_at(i, (0ll + axis_location + j) - 1, '-');
		}
	}
}


void Canvas_xy::set_indent(size_t new_indent)
{
	if (new_indent > 0)
		indent = new_indent;

}