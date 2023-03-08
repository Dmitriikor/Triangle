#ifndef CANVAS_CONSOLE_H__

#define CANVAS_CONSOLE_H__

#include "Canvas.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdexcept>



class Canvas_console : public Canvas
{
private:
	static const char EMPTY = ' ';
protected:
	Matrix<char> Canvas_Matrix;
	bool isMatrixCalculated = false;

	//!!! не в наследниках ли?
	Coordinate ORIGIN_;

	int width_x_;
	int width_y_;

	int width_x_with_indent_;
	int width_y_with_indent_;

	int axis_x_indents_;
	int axis_x_strings_;

	//

	void initialize_width();

	void x_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;
	void y_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;

public:

	Canvas_console();

	Canvas_console& operator+=(const Canvas_console& other);

	void insert(const Dot& pt);
	void insert(const Ray<Point>& points, char symbol = '.');
	void insert(const Ray<Dot>& points);


	virtual void calculate_matrix() = 0;
	//{
	//	initialize_width();

	//	double max_value_x = std::max(std::abs(MAX_VIRTUAL().x), std::abs(MIN_VIRTUAL().x));
	//	double max_value_y = std::max(std::abs(MAX_VIRTUAL().y), std::abs(MIN_VIRTUAL().y));
	//	//double max_value_x = (((std::abs(MAX_VIRTUAL().x)) > (std::abs(MIN_VIRTUAL().x))) ? (std::abs(MAX_VIRTUAL().x)) : (std::abs(MIN_VIRTUAL().x))) + 1;
	//	//double max_value_y = (((std::abs(MAX_VIRTUAL().y)) > (std::abs(MIN_VIRTUAL().y))) ? (std::abs(MAX_VIRTUAL().y)) : (std::abs(MIN_VIRTUAL().y))) + 1;
	//	
	//	Canvas_Matrix.resize(max_value_y, max_value_x); //(std::abs(MAX_VIRTUAL().x) + std::abs(MIN_VIRTUAL().x), std::abs(MAX_VIRTUAL().y)+ std::abs(MIN_VIRTUAL().y));
	//	Canvas_Matrix.fill(EMPTY);

	//	Coordinate cell;

	//	for (int i = 0; i < points_to_draw().size(); ++i)
	//	{
	//		cell.j = std::abs(points_to_draw()[i].x);

	//		cell.i = std::abs(points_to_draw()[i].y);

	//		Canvas_Matrix.set_at(cell, points_to_draw()[i].symbol);
	//	}

	//	isMatrixCalculated = true;
	//}

	void print() const
	{
		//cout << ;
		Canvas_Matrix.print();
	}
};

#endif //!CANVAS_CONSOLE_H__