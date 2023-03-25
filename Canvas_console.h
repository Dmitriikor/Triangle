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

	bool isMatrixCalculated_ = false;
	Matrix<char> Canvas_Matrix_;

	static const char EMPTY_ = ' ';


protected:
	bool isMatrixCalculated() const;
	void isMatrixCalculated(bool isMatrixCalculated);

	Matrix<char>& Canvas_Matrix();
	Matrix<char> Canvas_Matrix() const;

	char EMPTY() const;

	

	//!!! not in the heirs?


	size_t get_width(int min_coord, int max_coord);

	//virtual void calculate_width_x_with_indent() = 0;
	//virtual void calculate_width_y_with_indent() = 0;

	virtual void calculate_matrix() = 0;

public:

	Canvas_console() = default;

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