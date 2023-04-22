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

void Canvas_console::insert_line(const Dot& A, const Dot& B, char symbol)
{
	Canvas::insert_line(A, B, symbol);
	if (is_last_change_update_points())
	{
		isMatrixCalculated_ = false;
	}
}

void Canvas_console::remove_line(const Dot& A, const Dot& B)
{
	Canvas::remove_line(A, B);
	if (is_last_change_update_points())
	{
		isMatrixCalculated_ = false;
	}
}


Canvas_console& Canvas_console::operator+=(const Canvas_console& other)
{
	Canvas::operator+=(other);
	isMatrixCalculated_ = false;
	return *this;
	//! TODO: вставьте здесь оператор return
}

void Canvas_console::insert(const Dot& pt)
{
	Canvas::insert(pt);
	if (is_last_change_update_points())
	{
		isMatrixCalculated_ = false;
	}
}

void Canvas_console::insert(const Ray<Point>& points, char symbol)
{
	Canvas::insert(points, symbol);
	if (is_last_change_update_points())
	{
		isMatrixCalculated_ = false;
	}
}

void Canvas_console::insert(const Ray<Dot>& points)
{
	Canvas::insert(points);
	if (is_last_change_update_points())
	{
		isMatrixCalculated_ = false;
	}
}

	/*
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
	*/

