#ifndef CANVAS_H__

#define CANVAS_H__

#include <limits>

#include "Ray.h"
#include "Point.h"
#include "Matrix.h"
#include "utilities.h"
#include "Is_equal_test.h"

#include <optional>

class Canvas
{
private:
	void max_min_init_();
	void update_min_max_by(const Dot& pt);

	Point MAX_VIRTUAL_;
	Point MIN_VIRTUAL_;

	///int coefficient_;
	Ray<Dot> points_to_draw_;

	//std::optional<size_t> search_point(const Dot& pt) const;
	size_t search_point(const Dot& pt) const;

	static const size_t NOT_POSITION = std::numeric_limits<size_t>::max();

	bool is_last_change_update_points_;  //Обновила ли массив точек (points_to_draw_) последняя попытка добавления или удаления?
	bool is_last_change_update_min_;		//Обновила ли минимум (MIN_VIRTUAL_) последняя попытка добавления или удаления?
	bool is_last_change_update_max_;		//Обновила ли максимум (MAX_VIRTUAL_) последняя попытка добавления или удаления?

protected:
	const Point& MAX_VIRTUAL() const;
	const Point& MIN_VIRTUAL() const;
	const Ray<Dot>& points_to_draw() const;

	bool is_last_change_update_points() const;
	bool is_last_change_update_min() const;
	bool is_last_change_update_max() const;

public:
	Canvas();

	Canvas& operator+=(const Canvas& other);
	//Canvas operator+(const Canvas& other) const;

	void insert(const Dot& pt);
	void insert(const Point& pt, char symbol = '.');

	void insert(const Ray<Point>& points, char symbol = '.');
	void insert(const Ray<Dot>& points);

	void remove(const Point& dl, bool isUpdateCanvasSizes = false);

	void insert_line(const Dot& A, const Dot& B, char symbol);

	void remove_line(const Dot& A, const Dot& B);

	void remove(const Ray<Point>& points);
	void remove(const Ray<Dot>& points);

	bool is_point(const Dot& pt) const;

	~Canvas() = default;
};

#endif //!  CANVAS_H__