#pragma once


#include "Canvas.h"
#include "Canvas_console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdexcept>


class Canvas_xy : public Canvas_console
{
	int width_x_with_indent_;
	int width_y_with_indent_;

	int width_x_;
	int width_y_;

	int axis_x_indents_ = 1;
	int axis_x_strings_ = 1;

	int indent = 1;

protected:
	int width_x() const;

	int width_y() const;

	int width_x_with_indent();

	int width_y_with_indent();

	void width_x_with_indent(size_t size);

	void width_y_with_indent(size_t size);

	int axis_x_indents() const;

	int axis_x_strings() const;

	void initialize_widthes();  //! @todo доработать перенос и подсчет

	size_t get_width(int min_coord, int max_coord);

	void initialize_width();

	size_t get_digits_count(unsigned long long number);

	void x_axis_filling(size_t axis_length, int min_x, int axis_location);
	void y_axis_filling(size_t axis_length, int min_x, int axis_location);

	void set_indent(size_t new_indent);


};