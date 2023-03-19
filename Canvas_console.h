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

	int width_x_;
	int width_y_;

	int axis_x_indents_;
	int axis_x_strings_;

	int indent;

	bool isMatrixCalculated_ = false;
	Matrix<char> Canvas_Matrix;

	static const char EMPTY_ = ' ';

	void check_after_insert();

	int width_x_with_indent_;
	int width_y_with_indent_;
protected:
	bool isMatrixCalculated() const;
	//void isMatrixCalculated(bool isMatrixCalculated);

	Matrix<char>& Canvas_Matrix();

	char EMPTY() const;

	

	//!!! not in the heirs?

	int width_x() const;

	int width_y() const;

	int width_x_with_indent();

	int width_y_with_indent();

	int axis_x_indents() const;

	int axis_x_strings() const;

	void initialize_width();

	void x_axis_filling(size_t axis_length, int min_x, int axis_location);
	void y_axis_filling(size_t axis_length, int min_x, int axis_location);

	//virtual void calculate_width_x_with_indent() = 0;
	//virtual void calculate_width_y_with_indent() = 0;

	virtual void calculate_matrix() = 0;

public:

	Canvas_console();

	Canvas_console& operator+=(const Canvas_console& other);

	void insert(const Dot& pt);
	void insert(const Ray<Point>& points, char symbol = '.');
	void insert(const Ray<Dot>& points);

	void insert_line(const Dot& A, const Dot& B, char symbol);
	void remove_line(const Dot& A, const Dot& B);

	virtual void render_matrix() = 0;
	virtual void print() const = 0;

	virtual ~Canvas_console() = default;
};

#endif //!CANVAS_CONSOLE_H__