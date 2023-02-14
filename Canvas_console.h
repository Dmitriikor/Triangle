#ifndef CANVAS_CONSOLE_H__

#define CANVAS_CONSOLE_H__

#include "Canvas.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdexcept>

int get_distance_between(int min_coord, int max_coord);

class Canvas_console : public Canvas
{
protected:
	mutable Matrix<char> Canvas_Matrix;
	mutable bool isMatrixCalculated = false;

	//!!! не в наследниках ли?
	mutable Coordinate ORIGIN_;

	int width_x_;
	int width_y_;

	mutable int width_x_with_indent_;
	mutable int width_y_with_indent_;

	int axis_x_indents_;
	int axis_x_strings_; 

	//

	void initialize_width();

	void x_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;
	void y_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const;

public:
	Canvas_console();

	void calculate_matrix() const
	{
		//max_min_init();

		//for (int i = 0; i < points_to_draw_.size(); ++i)
			//update_min_max_by(points_to_draw_[i]);

		Canvas_Matrix.resize(((std::abs(MAX_VIRTUAL_.x) + std::abs(MIN_VIRTUAL_.x)) * 2) + 1, ((std::abs(MAX_VIRTUAL_.y) + std::abs(MIN_VIRTUAL_.y)) * 2) + 1); //(std::abs(MAX_VIRTUAL_.x) + std::abs(MIN_VIRTUAL_.x), std::abs(MAX_VIRTUAL_.y)+ std::abs(MIN_VIRTUAL_.y));
		Canvas_Matrix.fill(char(46));

		Coordinate Test;

		for (int i = 0; i < points_to_draw_.size(); ++i)
		{
			if (points_to_draw_[i].x < 0)
				Test.i = std::abs(points_to_draw_[i].x);
			else
				Test.i = std::abs(MAX_VIRTUAL_.x) + std::abs(points_to_draw_[i].x);

			if (points_to_draw_[i].y < 0)
				Test.j = std::abs(MAX_VIRTUAL_.y) + std::abs(points_to_draw_[i].y);
			else
				Test.j = std::abs(points_to_draw_[i].y);

			Canvas_Matrix.set_at(Test.i, Test.j, points_to_draw_[i].symbol);
		}

		isMatrixCalculated = true;
	}

	void print() const
	{
		if (!isMatrixCalculated)
			calculate_matrix();

		Canvas_Matrix.print();
	}
};

#endif //!CANVAS_CONSOLE_H__