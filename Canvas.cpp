#include "Canvas.h"

///static double get_step(double coefficient);
static Ray<Dot> calculate_line_with_rounding_(const Dot& A, const Dot& B, char symbol = '+', double coefficient = 1.0);
static Ray<Dot> calculate_line_swap_(const Dot& A, const Dot& B, char symbol = '+', double coefficient = 1.0);


void Canvas::max_min_init_()
{
	MAX_VIRTUAL_.x = std::numeric_limits<double>::lowest();
	MAX_VIRTUAL_.y = std::numeric_limits<double>::lowest();

	MIN_VIRTUAL_.x = std::numeric_limits<double>::max();
	MIN_VIRTUAL_.y = std::numeric_limits<double>::max();
}

bool Canvas::update_min_max_by(const Dot& pt)
{
	bool is_update = false; // return 
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

	return is_update;
}

bool Canvas::remove_rounding_line_(const Dot& A, const Dot& B)
{
	bool isRemoved = false;

	Ray<Dot> erase_line_arr = calculate_line_with_rounding_(A, B);

	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		if (remove(erase_line_arr[i]))
			isRemoved = true;

	return isRemoved;
}

bool Canvas::remove_no_rounding_line_(const Dot& A, const Dot& B)
{
	bool isRemoved = false;

	Ray<Dot> erase_line_arr = calculate_line_swap_(A, B);

	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		if (remove(erase_line_arr[i]))
			isRemoved = true;

	return isRemoved;
}


/// <summary>
/// вставка без повторений
/// </summary>
/// <param name="pt"> точка для отрисовки</param>
/// <returns>
/// true - вставка осуществлена, false - элемент уже был добавлен </returns>
size_t Canvas::search_point(const Dot& pt) const
{
	for (size_t i = 0; i < points_to_draw_.size(); i++)
		if (points_to_draw_[i] == pt)
			return i;

	return NOT_POSITION;
}


const Point& Canvas::MAX_VIRTUAL() const
{
	return MAX_VIRTUAL_;
}

const Point& Canvas::MIN_VIRTUAL() const
{
	return MIN_VIRTUAL_;
}

const Ray<Dot>& Canvas::points_to_draw() const
{
	return points_to_draw_;
}

Canvas::Canvas()
{
	max_min_init_();
}

Canvas& Canvas::operator+=(const Canvas& other)
{
	insert(other.points_to_draw_);

	return *this;
}

////Canvas Canvas::operator+(const Canvas& other) const
////{
////	Canvas temp = *this;
////
////	temp += other;
////
////	return temp;
////}


bool Canvas::insert(const Dot& pt)
{
	size_t pos = search_point(pt);

	if (pos == NOT_POSITION)
	{
		points_to_draw_.add_to_back(pt);
		update_min_max_by(pt);
		return true;
	}

	if ((pos < points_to_draw_.size()) && points_to_draw_[pos].symbol != pt.symbol) //перерисовывается точка
	{
		points_to_draw_[pos].symbol = pt.symbol; 
		return true;
	}

	return false;
}

bool Canvas::insert(const Ray<Point>& points, char symbol)
{
	bool isInserted = false;

	for (size_t i = 0; i < points.size(); i++)
		if (insert(Dot(points[i], symbol)))
			isInserted = true;

	return isInserted;
}

bool Canvas::insert(const Ray<Dot>& points)
{
	bool isInserted = false;

	for (size_t i = 0; i < points.size(); i++)
		if (insert(points[i]))
			isInserted = true;

	return isInserted;
}


bool Canvas::insert_line(const Dot& A, const Dot& B, char symbol)
{
	bool isInserted = false;

#ifdef SWAP
	isInserted = insert(calculate_line_swap_(A, B, symbol));
#elif ROUND
	isInserted = insert(calculate_line_with_rounding_(A, B, symbol));
#else
	isInserted = insert(calculate_line_swap_(A, B, symbol));
	isInserted = insert(calculate_line_with_rounding_(A, B, symbol)) || isInserted;
#endif

	return isInserted;
}


bool Canvas::remove_line(const Dot& A, const Dot& B)
{
	bool isRemoved = false;

	isRemoved = remove_no_rounding_line_(A, B);
	isRemoved = remove_rounding_line_(A, B) || isRemoved;

	return isRemoved;

}

//!!! СКОПИРОВАТЬ В КОНСОЛЬНЫЙ
bool Canvas::remove(const Dot& dot)
{
	size_t pos = search_point(dot);

	if (pos != NOT_POSITION)
	{
		points_to_draw_.remove(pos);

		//можно обновить MIN, MAX, width
		//для уменьшения размера холста
		return true;
	}

	return false;
}

bool Canvas::is_point(const Dot& pt) const
{
	if (search_point(pt) != NOT_POSITION)
		return true;
	return false;
}



// Повторное объявление функции с внутренней связью в другом файле ->
// необходимо указать static перед объявлением функции
// static void get_step();
double get_step(double coefficient)
{
	double step = 1.0 / coefficient;
	return step;
}

// Повторное объявление функции с внутренней связью в другом файле ->
// необходимо указать static перед объявлением функции
// static void calculate_line_swap_();
Ray<Dot> calculate_line_swap_(const Dot& A, const Dot& B, char symbol, double coefficient)
{
	Ray<Dot> lockal_line_arr;

	if (A.x == B.x && A.y == B.y)
	{
		Dot temp_A = A;
		temp_A.symbol = symbol;

		lockal_line_arr.add_to_back(temp_A);
		return lockal_line_arr;
	}

	double	x1 = A.x, 
			y1 = A.y, 
			x2 = B.x, 
			y2 = B.y;

	////x1 = A.x;
	////y1 = A.y;
	////x2 = B.x;
	////y2 = B.y;

	bool is_swap = false;
	if (std::abs(x1 - x2) < std::abs(y1 - y2))
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
		is_swap = true;
	}
	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	for (double x = x1; x <= x2; x += 1.0) // 0.50 
	{
		double k = (x - x1) / (x2 - x1);
		double y = y1 * (1.0 - k) + y2 * k;


		double step = get_step(coefficient);
		///y = (int)utilities::round_by_step(y, step);

		Dot coords(0, 0, symbol);

		if (is_swap)
		{
			coords.x = (int)utilities::round_by_step(y, step);
			coords.y = (int)utilities::round_by_step(x, step);
			///std::cout << y << x << "\n";
			lockal_line_arr.add_to_back(coords);
		}
		else
		{
			coords.x = (int)utilities::round_by_step(x, step);
			coords.y = (int)utilities::round_by_step(y, step);
			///std::cout << y << x << "\n";
			lockal_line_arr.add_to_back(coords);
		}
	}
	return lockal_line_arr;
}

// Повторное объявление функции с внутренней связью в другом файле ->
// необходимо указать static перед объявлением функции
// static void calculate_line_with_rounding_();
Ray<Dot> calculate_line_with_rounding_(const Dot& A, const Dot& B, char symbol, double coefficient)
{
	Ray<Dot> lockal_line_arr;

	double min = A.x;
	double max = B.x;
	if (A.x > B.x) {
		min = B.x;
		max = A.x;
	}

	////double siz_x;

	////if ((min < 0 && max < 0) || (min > 0 && max > 0))
	////	siz_x = std::abs(max) - std::abs(min);
	////if ((min <= 0 && max >= 0) || (min >= 0 && max <= 0))
	////	siz_x = std::abs(max) + std::abs(min);

	if (utilities::isEqual(min, max))
	{
		double start = A.y;
		double end = B.y;
		if (A.y < B.y) {
			start = B.y;
			end = A.y;
		}

		double step = get_step(coefficient);  /// 1.0 / coefficient;

		Dot coords(0, 0, symbol);
		coords.x = A.x;
		for (double y = start; y >= end; y -= step)
		{
			coords.y = y;

			coords.x = (int)utilities::round_by_step(coords.x, step);
			coords.y = (int)utilities::round_by_step(coords.y, step);

			lockal_line_arr.add_to_back(coords);
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

		////unsigned N = (rounded_max - rounded_min) / step + 1;
		double N = (rounded_max - rounded_min) / step + 1;
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
}
