#ifndef CANVAS_H__

#define CANVAS_H__

#include <limits>

#include "Ray.h"
#include "Point.h"
#include "Matrix.h"
#include "utilities.h"
#include "Is_equal_test.h"

double get_step(double coefficient);

class Canvas
{
private:
	void max_min_init();
	void update_min_max_by(const Dot& pt);

	//void set_min_max(size_t from, size_t to);
	//bool is_point_in_arr(const Dot& pt);

	void add_line_points_to_arr_(const Dot& A, const Dot& B, bool is_round = true, char symbol = '+'); //add point to arr for print

	void remove_no_rounding_line(const Dot& A, const Dot& B);
	void remove_rounding_line(const Dot& A, const Dot& B);

	Ray<Dot> calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol = '+', double coefficient = 1.0);
	Ray<Dot> calculate_line_swap(const Dot& A, const Dot& B, char symbol = '+', double coefficient = 1.0);

	bool check_and_insert_point(const Dot& pt);
protected:

	Point MAX_VIRTUAL_;
	Point MIN_VIRTUAL_;

	Ray<Dot> points_to_draw_;		//free dots to draw

public:
	Canvas();

	Canvas& operator+=(const Canvas& other);
	//Canvas operator+(const Canvas& other) const;

	void insert(const Dot& pt);
	void insert(const Ray<Point>& points, char symbol = '.');
	void insert(const Ray<Dot>& points); //!!! so it is possible, but it is not necessary here => overload

	void add_line(const Dot& A, const Dot& B, char symbol); //!!! is_round

	void remove_line(const Dot& A, const Dot& B);
	void remove_point(const Dot& dl);
};











#endif //!  CANVAS_H__