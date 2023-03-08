#ifndef CANVAS_H__

#define CANVAS_H__

#include <limits>

#include "Ray.h"
#include "Point.h"
#include "Matrix.h"
#include "utilities.h"
#include "Is_equal_test.h"

class Canvas
{
private:
	void max_min_init_();
	bool update_min_max_by(const Dot& pt);

	bool remove_no_rounding_line_(const Dot& A, const Dot& B);
	bool remove_rounding_line_(const Dot& A, const Dot& B);

private:
	Point MAX_VIRTUAL_;
	Point MIN_VIRTUAL_;

	//int coefficient_;
	Ray<Dot> points_to_draw_;

	size_t search_point(const Dot& pt) const;

	static const size_t NOT_POSITION = -1;

protected:
	const Point& MAX_VIRTUAL() const;
	const Point& MIN_VIRTUAL() const;
	const Ray<Dot>& points_to_draw() const;

public:
	Canvas();

	Canvas& operator+=(const Canvas& other);
	//Canvas operator+(const Canvas& other) const;

	bool insert(const Dot& pt);
	bool insert(const Ray<Point>& points, char symbol = '.');
	bool insert(const Ray<Dot>& points);

	bool remove(const Dot& dl);

	bool insert_line(const Dot& A, const Dot& B, char symbol);

	bool remove_line(const Dot& A, const Dot& B);

	bool is_point(const Dot& pt) const;
};

#endif //!  CANVAS_H__