#include "Canvas_console.h"



char Canvas_console::EMPTY() const
{
	return EMPTY_;
}


Matrix<char>& Canvas_console::Canvas_Matrix()
{
	return Canvas_Matrix_;
}

Matrix<char> Canvas_console::Canvas_Matrix() const
{
	return Canvas_Matrix_;
}

void Canvas_console::isMatrixCalculated(bool status) 
{
	 isMatrixCalculated_= status;
}

bool Canvas_console::isMatrixCalculated() const
{
	return isMatrixCalculated_;
}

int Canvas_console::width_x() const
{
	return width_x_;
}

int Canvas_console::width_y() const
{
	return width_y_;
}

int Canvas_console::width_x_with_indent() 
{
	return width_x_with_indent_ == width_x() + axis_x_indents_;
}

int Canvas_console::width_y_with_indent() 
{
	return width_y_with_indent_ = width_y() + indent;
	
}

int Canvas_console::axis_x_indents() const
{
	return axis_x_indents_;
}

int Canvas_console::axis_x_strings() const
{
	return axis_x_strings_;
}



void Canvas_console::check_after_insert()
{
	initialize_width();

	isMatrixCalculated_ = false;
}

void Canvas_console::insert_line(const Dot& A, const Dot& B, char symbol)
{
	Canvas::insert_line(A, B, symbol);
	if (is_last_change_update_points())
	{
		check_after_insert();
	}
}

void Canvas_console::remove_line(const Dot& A, const Dot& B)
{
	Canvas::remove_line(A, B);
	if (is_last_change_update_points())
	{
		check_after_insert();
	}
}


void Canvas_console::insert(const Dot& pt)
{
	Canvas::insert(pt);
	if (is_last_change_update_points())
	{
		check_after_insert();
	}
}

void Canvas_console::insert(const Ray<Point>& points, char symbol)
{
	Canvas::insert(points, symbol);
	if (is_last_change_update_points())
	{
		check_after_insert();
	}
}

void Canvas_console::insert(const Ray<Dot>& points)
{
	Canvas::insert(points);
	if (is_last_change_update_points())
	{
		check_after_insert();
	}
}

Canvas_console::Canvas_console() :Canvas()
{
	width_x_ = -1;
	width_y_ = -1;

	axis_x_indents_ = 1;
	axis_x_strings_ = 1;

	width_x_with_indent_ = -1;
	width_y_with_indent_ = -1;
	
	//old_max = MAX_VIRTUAL();
	//old_min = MIN_VIRTUAL();
	indent = 1;
}

size_t Canvas_console::get_digits_count(unsigned long long number)
{
	size_t count = 1;
	while (number >= 10)
	{
		++count;
		number /= 10;
	}
	return count;
}

//calculate width for printing numbers along axys
size_t Canvas_console::get_width(int min_coord, int max_coord)
{
	size_t width = 0;

	unsigned longest_coord = abs(max_coord) > abs(min_coord) ? abs(max_coord) : abs(min_coord);
	width += get_digits_count(longest_coord);

	if (min_coord < 0)
		++width;

	return width;
}

void Canvas_console::initialize_widthes()
{
	width_x_ = get_width(MIN_VIRTUAL().x, MAX_VIRTUAL().x);
	width_y_ = get_width(MIN_VIRTUAL().y, MAX_VIRTUAL().y);
}


void Canvas_console::initialize_width() {
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



void Canvas_console::x_axis_filling(size_t axis_length, int min_x, int axis_location)
{
	size_t N = axis_length;

	for (int i = 0; i < N; i++)
	{
		 int temp_x = min_x + i;

		 Canvas_Matrix().set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1u), '|');

		int abs_x = fabs(temp_x);
		int j;
		for (j = width_x_with_indent_ - 2; j >= 0; --j)
		{
			int digit = abs_x % 10;

			Canvas_Matrix().set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + j, '0' + digit);

			abs_x = abs_x / 10;

			if (abs_x == 0)
				break;
		}
		///Canvas_Matrix_().print();
		if (j == -1)
		{
			Canvas_Matrix().print();
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_X");
		}

		if (temp_x < 0)
			Canvas_Matrix().set_at(axis_location, (width_y_with_indent_ + (i * width_x_with_indent_) + j) - 1, '-');
	}
}

void Canvas_console::y_axis_filling(size_t axis_length, int start_i, int axis_location)
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
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_Y");

		if (temp_y < 0) {
			Canvas_Matrix().set_at(i, (0ll + axis_location + j) - 1, '-');
		}
	}
}


//! @todo void Axys::erase_point_from_axys(Dot& err) const
