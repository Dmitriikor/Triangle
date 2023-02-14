#include "Canvas.h"


double get_step(double coefficient)
{
	double step = 1.0 / coefficient;
	return step;
}


void Canvas::max_min_init()
{
	MAX_VIRTUAL_.x = std::numeric_limits<double>::lowest();
	MAX_VIRTUAL_.y = std::numeric_limits<double>::lowest();

	MIN_VIRTUAL_.x = std::numeric_limits<double>::max();
	MIN_VIRTUAL_.y = std::numeric_limits<double>::max();
}



void Canvas::update_min_max_by(const Dot& pt)
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
	//if (is_update == true) { //!!!
	//	initialize_width();
	//}
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



/// <summary>
/// Добавление линии (точек линии) в массив точек (points_to_draw_).
/// Точки А и B должны быть добавлены на холст!
/// </summary>
/// <param name="A">Точка начала (уже должна быть на холсте) </param>
/// <param name="B">Точка конца (уже должна быть на холсте)</param>
/// <param name="is_round">Округляем ли</param>
/// <param name="symbol">Символ для отрисовки</param>
void Canvas::add_line_points_to_arr_(const Dot& A, const Dot& B, bool is_round, char symbol)
{
	//const Ray<Dot>& lockal_draw_line_arr = is_round ? calculate_line_with_rounding(A, B, symbol) : calculate_line_swap(A, B, symbol);

	//const Ray<Dot>& lockal_draw_line_arr_1 = calculate_line_with_rounding(A, B, symbol);
	const Ray<Dot>& lockal_draw_line_arr_2 = calculate_line_swap(A, B, symbol);

	//size_t length_1 = lockal_draw_line_arr.size();
	//for (size_t i = 0; i < length_1; i++)
	//{
	//	points_to_draw_.add_to_back(lockal_draw_line_arr[i]);
	//}

	size_t length_2 = lockal_draw_line_arr_2.size();
	for (size_t i = 0; i < length_2; i++)
	{
		points_to_draw_.add_to_back(lockal_draw_line_arr_2[i]);
	}
}


void Canvas::remove_rounding_line(const Dot& A, const Dot& B)
{
	Ray<Dot> erase_line_arr;

	erase_line_arr = calculate_line_with_rounding(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}

void Canvas::remove_no_rounding_line(const Dot& A, const Dot& B)
{
	Ray<Dot> erase_line_arr;

	erase_line_arr = calculate_line_swap(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}


Ray<Dot> Canvas::calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol, double coefficient)
{
	Ray<Dot> lockal_line_arr;

	Dot coords;

	double min = A.x;
	double max = B.x;
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
}


Ray<Dot> Canvas::calculate_line_swap(const Dot& A, const Dot& B, char symbol, double coefficient)
{
	Ray<Dot> lockal_line_arr;

	if (A.x == B.x && A.y == B.y)
	{
		lockal_line_arr.add_to_back(A);
		return lockal_line_arr;
	}

	double x1, y1, x2, y2;
	x1 = A.x;
	y1 = A.y;
	x2 = B.x;
	y2 = B.y;

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
		double k = ((double)x - x1) / (double)(x2 - x1);
		double y = y1 * (1.0 - k) + y2 * k;


		double step = get_step(coefficient);
		//y = (int)utilities::round_by_step(y, step);

		Dot coords;
		coords.symbol = symbol;

		if (is_swap)
		{
			coords.x = (int)utilities::round_by_step(y, step);
			coords.y = (int)utilities::round_by_step(x, step);
			//std::cout << y << x << "\n";
			lockal_line_arr.add_to_back(coords);
		}
		else
		{
			coords.x = (int)utilities::round_by_step(x, step);
			coords.y = (int)utilities::round_by_step(y, step);
			//std::cout << y << x << "\n";
			lockal_line_arr.add_to_back(coords);
		}
	}
	return lockal_line_arr;
}







/// <summary>
/// вставка без повторений
/// </summary>
/// <param name="pt"> точка для отрисовки</param>
/// <returns>
/// true - вставка осуществлена, false - элемент уже был добавлен </returns>
bool Canvas::check_and_insert_point(const Dot& pt)
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




Canvas::Canvas()
{
	max_min_init();
}

Canvas& Canvas::operator+=(const Canvas& other)
{
	insert(other.points_to_draw_);

	return *this;
}

//Canvas Canvas::operator+(const Canvas& other) const
//{
//	Canvas temp = *this;
//
//	temp += other;
//
//	return temp;
//}


void Canvas::insert(const Dot& pt)
{
	if (check_and_insert_point(pt))
	{
		update_min_max_by(pt);
		//initialize_width(); //!!!
		//isMatrixCalculated = false; //!!!
	}
}

void Canvas::insert(const Ray<Point>& points, char symbol)
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
		//initialize_width(); //!!!
		//isMatrixCalculated = false; //!!!
	}
}

void Canvas::insert(const Ray<Dot>& points)
{
	bool isInserted = false; //!!! return true / false

	size_t length_arr = points.size();
	for (size_t i = 0; i < length_arr; i++)
		if (check_and_insert_point(points[i]))
		{
			update_min_max_by(points[i]);
			isInserted = true;
		}

	if (isInserted)
	{
		/*initialize_width(); //!!!
		isMatrixCalculated = false;*/
	}
}


void Canvas::add_line(const Dot& A, const Dot& B, char symbol)
{
	Dot temp_A = A;
	temp_A.symbol = symbol;
	insert(temp_A);

	Dot temp_B = B;
	temp_B.symbol = symbol;
	insert(temp_B);

	add_line_points_to_arr_(temp_A, temp_B, false, symbol);
}


void Canvas::remove_line(const Dot& A, const Dot& B)
{

	remove_no_rounding_line(A, B);
	remove_rounding_line(A, B);
	//isMatrixCalculated = false; //!!!
}

void Canvas::remove_point(const Dot& dot)
{
	for (size_t i = 0; i < points_to_draw_.size(); i++)
	{
		if (dot == points_to_draw_[i])
		{
			points_to_draw_.remove(i);
			//isMatrixCalculated = false; //!!!

			//можно обновить MIN, MAX, width
			//для уменьшения размера холста
			break;
		}
	}
}