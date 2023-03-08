#include "Canvas_console.h"



char Canvas_console::EMPTY() const
{
	return EMPTY_;
}


Matrix<char>& Canvas_console::Canvas_Matrix_()
{
	return Canvas_Matrix;
}

Matrix<char> Canvas_console::Canvas_Matrix_() const
{
	return Canvas_Matrix;
}

void Canvas_console::isMatrixCalculated(bool isMatrixCalculated) 
{
	 isMatrixCalculated_= isMatrixCalculated;
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
	if (((old_max.x < MAX_VIRTUAL().x) || (old_max.y < MAX_VIRTUAL().y)) || ((old_min.y > MIN_VIRTUAL().y) || (old_min.y > MIN_VIRTUAL().y)))
	{
		initialize_width();

		old_max = MAX_VIRTUAL();
		old_min = MIN_VIRTUAL();
	}

	isMatrixCalculated(false) ; //!!!
}

void Canvas_console::insert_line(const Dot& A, const Dot& B, char symbol)
{
	if (Canvas::insert_line(A, B, symbol))
	{
		check_after_insert();
	}
}

void Canvas_console::remove_line(const Dot& A, const Dot& B)
{
	if (Canvas::remove_line(A, B))
	{
		check_after_insert();
	}
}


void Canvas_console::insert(const Dot& pt)
{
	if (Canvas::insert(pt))
	{
		check_after_insert();
	}
}

void Canvas_console::insert(const Ray<Point>& points, char symbol)
{
	if (Canvas::insert(points, symbol))
	{
		check_after_insert();
	}
}

void Canvas_console::insert(const Ray<Dot>& points)
{
	if (Canvas::insert(points))
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
	
	old_max = MAX_VIRTUAL();
	old_min = MIN_VIRTUAL();
	indent = 1;
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

		 Canvas_Matrix_().set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1u), '|');

		int abs_x = fabs(temp_x);
		int j;
		for (j = width_x_with_indent_ - 2; j >= 0; --j)
		{
			int digit = abs_x % 10;

			Canvas_Matrix_().set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + j, '0' + digit);

			abs_x = abs_x / 10;

			if (abs_x == 0)
				break;
		}
		///Canvas_Matrix_().print();
		if (j == -1)
		{
			Canvas_Matrix_().print();
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_X");
		}

		if (temp_x < 0)
			Canvas_Matrix_().set_at(axis_location, (width_y_with_indent_ + (i * width_x_with_indent_) + j) - 1, '-');
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

			Canvas_Matrix_().set_at(i, axis_location + j, '0' + digit);

			abs_y = abs_y / 10;
			if (abs_y == 0)
				break;
		}

		if (j == -1)
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_Y");

		if (temp_y < 0) {
			Canvas_Matrix_().set_at(i, (0ll + axis_location + j) - 1, '-');
		}
	}
}










// TO DO
////void Axys::erase_point_from_axys(Dot& err) const
////{
////	//erase_point(err, Canvas_Matrix);
////}
