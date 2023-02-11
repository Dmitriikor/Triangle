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

	mutable Ray<Dot> points_to_draw_;		//free dots to draw

};




class Canvas_console : public Canvas
{
protected:

	mutable Coordinate ORIGIN_;
	mutable Matrix<char> Canvas_Matrix ; 
	mutable bool isMatrixCalculated = false;

	 int width_x_;
	 int width_y_;

	 int axis_x_indents_;
	 int axis_x_strings_;

	mutable int width_x_with_indent_;
	mutable int width_y_with_indent_;

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


	void prepare()
	{
		max_min_init();

		for(int i = 0; i<points_to_draw_.size();++i)
		update_min_max_by(points_to_draw_[i]);

		Canvas_Matrix.resize(((std::abs(MAX_VIRTUAL_.x) + std::abs(MIN_VIRTUAL_.x)) * 2)+1, ((std::abs(MAX_VIRTUAL_.y)+ std::abs(MIN_VIRTUAL_.y))* 2)+1); //(std::abs(MAX_VIRTUAL_.x) + std::abs(MIN_VIRTUAL_.x), std::abs(MAX_VIRTUAL_.y)+ std::abs(MIN_VIRTUAL_.y));
		Canvas_Matrix.fill('.');

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

			Canvas_Matrix.set_at(Test.j, Test.i, points_to_draw_[i].symbol);
		}

		isMatrixCalculated = true;
		print();
	}

	void print() const
	{
		if (!isMatrixCalculated)
			const_cast<Canvas_console*>(this)->prepare();
			//prepare();
		else
			Canvas_Matrix.print();
	}


};







#endif //!  HELLO_H__