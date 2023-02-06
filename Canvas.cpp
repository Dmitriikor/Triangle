#include "Canvas.h"
#include <string>
#include <float.h>

int get_distance_between(int min_coord, int max_coord)
{
	if (min_coord >= 0 && max_coord >= 0)
		return abs(max_coord);

	if (min_coord <= 0 && max_coord <= 0)
		return abs(min_coord);

	return abs(max_coord) + abs(min_coord);
}

Canvas_console::Canvas_console()
{
	ORIGIN_.i = 0;
	ORIGIN_.j = 0;
	width_x_ = -1;
	width_y_ = -1;

	axis_x_indents_ = 1;
	axis_x_strings_ = 1;

	width_x_with_indent_ = -1;
	width_y_with_indent_ = -1;

	coefficient = 1;

	max_min_init();
}

Canvas_console& Canvas_console::operator+=(const Canvas_console& other)
{
	insert(other.points_to_draw_);

	return *this;
}

Canvas_console Canvas_console::operator+(const Canvas_console& other) const
{
	Canvas_console temp = *this;

	temp += other;

	return temp;
}


void Canvas_console::max_min_init()
{
	MAX_VIRTUAL_.x = -DBL_MAX;
	MAX_VIRTUAL_.y = -DBL_MAX;

	MIN_VIRTUAL_.x = DBL_MAX;
	MIN_VIRTUAL_.y = DBL_MAX;
}


void Canvas_console::insert(const Dot& pt)
{
	if (check_and_insert_point(pt))
	{
		update_min_max_by(pt);
		initialize_width(); 
		isMatrixCalculated = false;
	}
}

void Canvas_console::insert(const Ray<Point>& points, char symbol)
{
	bool isInserted = false;

	size_t length_arr = points.size();
	for (size_t i = 0; i < length_arr; i++)
		if (check_and_insert_point(Dot(points[i], symbol)))
		{
			update_min_max_by(points[i]);
			isInserted = true;
		}

	if (isInserted) 
	{
		initialize_width();
		isMatrixCalculated = false;
	}
}

void Canvas_console::insert(const Ray<Dot>& points)
{
	bool isInserted = false;

	size_t length_arr = points.size();
	for (size_t i = 0; i < length_arr; i++)
		if (check_and_insert_point(points[i]))
		{
			update_min_max_by(points[i]);
			isInserted = true;
		}

	if (isInserted)
	{
		initialize_width();
		isMatrixCalculated = false;
	}
}



void Canvas_console::update_min_max_by(const Dot& pt)
{
	bool is_update = false;
	if (pt.x > MAX_VIRTUAL_.x) {
		MAX_VIRTUAL_.x = pt.x;
		is_update = true;
	}
	if (pt.y > MAX_VIRTUAL_.y) {
		MAX_VIRTUAL_.y = pt.y;
		is_update = true;
	}
	if (pt.x < MIN_VIRTUAL_.x) {
		MIN_VIRTUAL_.x = pt.x;
		is_update = true;
	}
	if (pt.y < MIN_VIRTUAL_.y) {
		MIN_VIRTUAL_.y = pt.y;
		is_update = true;
	}
	if (is_update == true) {
		initialize_width();
	}
}

/// <summary>
/// вставка без повторений
/// </summary>
/// <param name="pt"> точка для отрисовки</param>
/// <returns>
/// true - вставка осуществлена, false - элемент уже был добавлен </returns>
bool Canvas_console::check_and_insert_point(const Dot& pt)
{
	size_t length = points_to_draw_.size();
	for (size_t i = 0; i < length; i++)
	{
		if (points_to_draw_[i] == pt)
		{
			points_to_draw_[i].symbol = pt.symbol; //!!! перерисовывается ли
			return false;
		}
	}

	points_to_draw_.add_to_back(pt);
	return true;
}

//bool Canvas_console::is_point_in_arr(const Dot& pt)
//{
//	size_t length = points_to_draw_.size();
//	for (size_t i = 0; i < length; i++)
//	{
//		if (points_to_draw_[i] == pt)
//		{
//			return true;
//		}
//	}
//	return false;
//}

void Canvas_console::initialize_width() {
	width_x_ = 1;
	width_y_ = 1;

	if (MIN_VIRTUAL_.y < 0)
		width_y_++;

	if (MIN_VIRTUAL_.x < 0)
		width_x_++;

	int x = abs(MAX_VIRTUAL_.x) > abs(MIN_VIRTUAL_.x) ? abs(MAX_VIRTUAL_.x) : abs(MIN_VIRTUAL_.x);
	while (x >= 10) {
		x = x / 10;
		width_x_++;
	}

	int y = abs(MAX_VIRTUAL_.y) > abs(MIN_VIRTUAL_.y) ? abs(MAX_VIRTUAL_.y) : abs(MIN_VIRTUAL_.y);
	while (y >= 10) {
		width_y_++;
		y = y / 10;
	}

}



void Canvas_console::x_axis_filling(Matrix<char>& arr, size_t axis_length, int min_x, int axis_location) const
{
	size_t N = axis_length;

	for (size_t i = 0; i < N; i++)
	{
		int temp_x = min_x + i;

		arr.set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1u), '|');

		int abs_x = fabs(temp_x);
		int j;
		for (j = width_x_with_indent_ - 2; j >= 0; --j)
		{
			int digit = abs_x % 10;

			arr.set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + j, '0' + digit);

			abs_x = abs_x / 10;

			if (abs_x == 0)
				break;
		}

		if (j == -1)
		{
			arr.print();
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_X");
		}

		if (temp_x < 0)
			arr.set_at(axis_location, (width_y_with_indent_ + (i * width_x_with_indent_) + j) - 1, '-');
	}
}

void Canvas_console::y_axis_filling(Matrix<char>& arr, size_t axis_length, int start_i, int axis_location) const
{
	for (size_t i = 0; i < axis_length; ++i)
	{
		int temp_y = start_i - i;

		int abs_y = fabs(temp_y);
		int j;
		for (j = width_y_with_indent_ - 1; j >= 0; --j)
		{
			int digit = abs_y % 10;

			arr.set_at(i, axis_location + j, '0' + digit);

			abs_y = abs_y / 10;
			if (abs_y == 0)
				break;
		}

		if (j == -1)
			throw std::runtime_error("hello.cpp -> create -> WRONG WIDTH_Y");

		if (temp_y < 0) {
			arr.set_at(i, (0ll + axis_location + j) - 1, '-'); 
		}
	}
}

void Canvas_console::add_line(const Dot& A, const Dot& B, char symbol)
{
	insert(A);
	insert(B);

	add_line_points_to_arr_(A, B, false, symbol);
}

//void Canvas_console::set_min_max(size_t from, size_t to)
//{
//	MAX_VIRTUAL_ = static_cast<Point>(points_to_draw_[from]);
//
//	MIN_VIRTUAL_ = static_cast<Point>(points_to_draw_[from]);
//
//	for (size_t i = from + 1; i < to; i++)
//	{
//		if (points_to_draw_[i].x > MAX_VIRTUAL_.x)
//			MAX_VIRTUAL_.x = points_to_draw_[i].x;
//		else if (points_to_draw_[i].x < MIN_VIRTUAL_.x)
//			MIN_VIRTUAL_.x = points_to_draw_[i].x;
//
//		if (points_to_draw_[i].y > MAX_VIRTUAL_.y)
//			MAX_VIRTUAL_.y = points_to_draw_[i].y;
//		else if (points_to_draw_[i].y < MIN_VIRTUAL_.y)
//			MIN_VIRTUAL_.y = points_to_draw_[i].y;
//	}
//}






// TO DO
////void Axys::erase_point_from_axys(Dot& err) const
////{
////	//erase_point(err, axys_arr_);
////}


double get_step(unsigned coefficient)
{
	double step = 1.0 / coefficient;
	return step;
}


void Canvas_console::remove_point(const Dot& dot)
{
	//!!! REMOVE_FIRST_POINT_FROM_RAY(dot, line_points_to_draw()); -- NO CLASS MEMBER
	for (size_t i = 0; i < points_to_draw_.size(); i++)
	{
		if (dot == points_to_draw_[i])
		{
			points_to_draw_.remove(i);
			isMatrixCalculated = false;
			//можно обновить MIN, MAX, width
			//для уменьшения размера холста
			break;
		}
	}
}

void Canvas_console::remove_rounding_line(const Dot& A, const Dot& B)
{
	Ray<Dot> erase_line_arr;

	erase_line_arr = calculate_line_with_rounding(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}

void Canvas_console::remove_no_rounding_line(const Dot& A, const Dot& B)
{
	Ray<Dot> erase_line_arr;

	erase_line_arr = calculate_line_swap(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}

void Canvas_console::remove_line(const Dot& A, const Dot& B)
{

	remove_no_rounding_line(A, B);
	remove_rounding_line(A, B);
	isMatrixCalculated = false;
}

/// <summary>
/// Добавление линии (точек линии) в массив точек (points_to_draw_).
/// Точки А и B должны быть добавлены на холст!
/// </summary>
/// <param name="A">Точка начала (уже должна быть на холсте) </param>
/// <param name="B">Точка конца (уже должна быть на холсте)</param>
/// <param name="is_round">Округляем ли</param>
/// <param name="symbol">Символ для отрисовки</param>
void Canvas_console::add_line_points_to_arr_(const Dot& A, const Dot& B, bool is_round, char symbol)
{
	const Ray<Dot>& lockal_draw_line_arr = is_round ? calculate_line_with_rounding(A, B, symbol) : calculate_line_swap(A, B, symbol);
	
	//const Ray<Dot>& lockal_draw_line_arr_1 = calculate_line_with_rounding(A, B, symbol);
	//const Ray<Dot>& lockal_draw_line_arr_2 = calculate_line_swap(A, B, symbol);

	size_t length_1 = lockal_draw_line_arr.size();
	for (size_t i = 0; i < length_1; i++)
	{
		points_to_draw_.add_to_back(lockal_draw_line_arr[i]);
	}

	//size_t length_2 = lockal_draw_line_arr_2.size();
	//for (size_t i = 0; i < length_2; i++)
	//{
	//	points_to_draw_.add_to_back(lockal_draw_line_arr_2[i]);
	//}
}

Ray<Dot> Canvas_console::calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol)
{
	Ray<Dot> lockal_line_arr;

	Dot coords;

	double min =A.x;
	double max =B.x;
	if (A.x > B.x) {
		min = B.x;
		max = A.x;
	}

	//double siz_x;

	//if ((min < 0 && max < 0) || (min > 0 && max > 0))
	//	siz_x = std::abs(max) - std::abs(min);
	//if ((min <= 0 && max >= 0) || (min >= 0 && max <= 0))
	//	siz_x = std::abs(max) + std::abs(min);

	if (utilities::isEqual(min, max))
	{
		double start = A.y;
		double end = B.y;
		if (A.y < B.y) {
			start = B.y;
			end = A.y;
		}
		double step = get_step(coefficient);  /// 1.0 / coefficient;
		Dot point;
		point.x = A.x;
		for (double y = start; y >= end; y -= step)
		{
			point.y = y;

			point.x = (int)utilities::round_by_step(point.x, step);
			point.y = (int)utilities::round_by_step(point.y, step);


			point.symbol = symbol;
			lockal_line_arr.add_to_back(point);
		}
		return lockal_line_arr;
	}

	double k = (B.y - A.y) / (B.x - A.x);
	double b_ = k * A.x;
	double b = A.y - b_;

	double step = get_step(coefficient);  /// 1.0 / coefficient;
	{
		double rounded_min = utilities::round_by_step(min, step);
		double rounded_max = utilities::round_by_step(max, step);

		unsigned N = (rounded_max - rounded_min) / step + 1;

		for (int i = 0; i < N; ++i)
		{
			
				Dot point;
				point.x = rounded_min + i * step;
				point.y = k * point.x + b;
			
				point.x = (int)utilities::round_by_step(point.x, step);
				point.y = (int)utilities::round_by_step(point.y, step);

				point.symbol = symbol;
				lockal_line_arr.add_to_back(point);
			

		}
	}
	return lockal_line_arr;

	///lockal_line_arr.clear(); //!!! unreachable code

	/*if (debug) {
		size_t length = points_to_draw_.size();
		for (size_t i = 0; i < length; i++)
		{
			std::cout << "\n" << points_to_draw_[i].x << " : " << points_to_draw_[i].y;
		}
	}*/
}


Ray<Dot> Canvas_console::calculate_line_swap(const Dot& A, const Dot& B, char symbol)
{
	Ray<Dot> lockal_line_arr;

	if (A.x == B.x && A.y == B.y)
	{
		return calculate_line_with_rounding(A, B);
	}

	double x1, y1, x2, y2;
	x1 = A.x;
	y1 = A.y;
	x2 = B.x;
	y2 = B.y;

	bool is_swap = false;
	if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
		std::swap(x1, y1);
		std::swap(x2, y2);
		is_swap = true;
	}
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	for (int x = x1; x <= x2; x++) {
		float k = (x - x1) / (float)(x2 - x1);
		float y = y1 * (1.0 - k) + y2 * k;


		double step = get_step(coefficient);
		y = (int)utilities::round_by_step(y, step);

		Dot coords;
		coords.symbol = symbol;

		if (is_swap) {
			coords.x = y;
			coords.y = x;

			lockal_line_arr.add_to_back(coords);
		}
		else {
			coords.x = x;
			coords.y = y;
			lockal_line_arr.add_to_back(coords);
		}
	}
	return lockal_line_arr;
}


