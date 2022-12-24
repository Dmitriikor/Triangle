#include "hello.h"
#include <string>

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
	debug = false;
}

Canvas_console::Canvas_console(const Canvas_console& other) : Canvas_console()
{
	insert(other.points_to_draw_);
}

void Canvas_console::max_min_init()
{
	MAX_VIRTUAL_.x = DBL_MIN;
	MAX_VIRTUAL_.y = DBL_MIN;

	MIN_VIRTUAL_.x = DBL_MAX;
	MIN_VIRTUAL_.y = DBL_MAX;
}

void Canvas_console::go_debug(bool is_debug)
{
	debug = is_debug;
}


template <typename T_temp>
void Canvas_console::insert(const Ray_template<T_temp>& points)
{
	size_t length_arr = points.size();
	for (size_t i = 0; i < length_arr; i++)
	{
		check_and_insert_point(points[i]);
	}

	set_min_max();

	initialize_width();
}

void Canvas_console::update_min_max_by(const Dot& pt)
{
	check_and_insert_point(pt);
	set_min_max();
	initialize_width();
}

void Canvas_console::check_and_insert_point(const Dot& pt)
{
	size_t length = points_to_draw_.size();
	for (size_t i = 0; i < length; i++)
	{
		if (points_to_draw_[i] == pt)
		{
			return;
		}
	}

	points_to_draw_.add_to_back(pt);
}


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

	/*std::cout << std::endl << width_x_ << std::endl;
	std::cout << std::endl << width_y_ << std::endl;*/

}

int Canvas_console::get_distance_between(int min_coord, int max_coord)
{
	if (min_coord >= 0 && max_coord >= 0)
		return abs(max_coord);

	if (min_coord <= 0 && max_coord <= 0)
		return abs(min_coord);

	return abs(max_coord) + abs(min_coord);
}

void Canvas_console::x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location)
{
	size_t N = axis_length;

	for (size_t i = 0; i < N; i++)
	{
		int temp_x = min_x + i;

		//!!!
		//arr[axis_location][width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1)] = '|';
		arr.set_at(axis_location, width_y_with_indent_ + (i * width_x_with_indent_) + (width_x_with_indent_ - 1), '|');

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
			throw std::exception("hello.cpp -> create -> WRONG WIDTH_X");
		}


		if (temp_x < 0)
			arr.set_at(axis_location, (width_y_with_indent_ + (i * width_x_with_indent_) + j) - 1, '-'); //!!! here was [i][1]
	}
}

void Canvas_console::y_axis_filling(Matrix& arr, size_t axis_length, int start_i, int axis_location)
{
	for (size_t i = 0; i < axis_length; ++i)
	{
		int temp_y = start_i - i;

		int abs_y = fabs(temp_y);
		int j;
		for (j = width_y_with_indent_ - 1; j >= 0; --j)
		{
			int digit = abs_y % 10;

			//arr[i][axis_location + j] = '0' + digit;
			arr.set_at(i, axis_location + j, '0' + digit);

			abs_y = abs_y / 10;
			if (abs_y == 0)
				break;
		}

		if (j == -1)
			throw std::exception("hello.cpp -> create -> WRONG WIDTH_Y");

		if (temp_y < 0) {
			//arr[i][(axis_location + j) - 1] = '-'; //!!! here was [i][1]
			arr.set_at(i, (axis_location + j) - 1, '-'); //!!! here was [i][1]
		}

		//else
			//corner_arr()[i][j - 1] = ' '; //!!! here was [i][1]
	}
}




//!!! module sub-functions
void Corner::create( char axys_arr_fill_symbol)
{
	// insert( points_to_draw_);

	//!!! Coordinates

	int max_y =  MAX_VIRTUAL_.y;
	int min_y =  MIN_VIRTUAL_.y;

	int max_x =  MAX_VIRTUAL_.x;
	int min_x =  MIN_VIRTUAL_.x;
	//std::cout << "\n" << max_y<< " " << min_y << " ; " << max_x << " " << min_x;


	{
		size_t N, M;

		N =  get_distance_between(min_y, max_y) + 1;
		M =  get_distance_between(min_x, max_x) + 1;

		N = N +  axis_x_strings_;
		M =  width_y_ + (M * ( width_x_ +  axis_x_indents_)) + ( width_x_ +  axis_x_indents_);

		if (N >  corner_arr().get_N() || M >  corner_arr().get_M())
		{
			 corner_arr() = Matrix(N, M);
			 corner_arr().fill(axys_arr_fill_symbol);
		}
	}

	// {print y axis
	int start_i = max_y > 0 ? max_y : 0;

	 width_y_with_indent_ =  width_y_;
	{
		int N =  corner_arr().get_N() -  axis_x_strings_;

		 y_axis_filling( corner_arr(), N, start_i, 0); //???????
	}
	// }end print y axis

	//{find actual console point of start coodrs
	//zero is shifted by max_y from top
	 ZERO().i = start_i;// +width_x_; //!x_axis_thickness
	//}find actual console point of start coodrs

	// {print x Axys
	{
		int start_x = min_x < 0 ? min_x : 0;


		int N__;
		if (min_x == max_x)
		{
			N__ = abs(min_x) + 1;
		}
		else if (min_x < 0)
			N__ = abs(min_x) + abs(max_x) + 1;
		else
			N__ = max_x + 1;

		int i_for_x =  corner_arr().get_N() -  axis_x_strings_;

		 width_x_with_indent_ =  width_x_ +  axis_x_indents_;

		 x_axis_filling( corner_arr(), N__, start_x, i_for_x);

		// }end print x axis

		//{find actual console point of start coodrs
		 ZERO().j = ((abs(start_x *  width_x_with_indent_)) +  width_y_ + ( width_x_with_indent_ - 1));
	}
	//}find actual console point of start coodrs
	// 
	//}end of work wich axis 
}


void Canvas_console::add_lines(const Dot& A, const Dot& B, bool is_round, char symbol/*, Canvas_console& this_*/)
{
	 update_min_max_by(A);
	 update_min_max_by(B);

	 add_point_to_arr_for_print_line(A, B, true, symbol);
}

void Corner::add_points_to_corner( )
{
	draw_points_or_line_corner(points_to_draw_, corner_arr());
}

void Corner::print_zero( )
{
	 corner_arr().set_at( ZERO().i,  ZERO().j -  axis_x_indents_, '0'); //!!!
}

void Corner::clear( )
{
	 corner_arr().clear();

	 initialize_width();

	/*?*/  create(/*this_*/);  ///?
}

void Canvas_console::set_min_max()
{
	size_t length = points_to_draw_.size();
	MAX_VIRTUAL_ = points_to_draw_[0];	//Серьезность	Код	Описание	Проект	Файл	Строка	Состояние подавления
										//Предупреждение	C26437	Не используйте срезы(es.63).matrix	Z : \с++\Triangle\hello.cpp	347

	MIN_VIRTUAL_ = points_to_draw_[0]; //Серьезность	Код	Описание	Проект	Файл	Строка	Состояние подавления
										//Предупреждение	C26437	Не используйте срезы(es.63).matrix	Z : \с++\Triangle\hello.cpp	347

	for (size_t i = 1; i < length; i++)
	{
		// TO DO
		// 
		//points_to_draw_[i].symbol = '+'; // Kostilvaniay to do


		if (points_to_draw_[i].x > MAX_VIRTUAL_.x)
			MAX_VIRTUAL_.x = points_to_draw_[i].x;
		else if (points_to_draw_[i].x < MIN_VIRTUAL_.x)
			MIN_VIRTUAL_.x = points_to_draw_[i].x;

		if (points_to_draw_[i].y > MAX_VIRTUAL_.y)
			MAX_VIRTUAL_.y = points_to_draw_[i].y;
		else if (points_to_draw_[i].y < MIN_VIRTUAL_.y)
			MIN_VIRTUAL_.y = points_to_draw_[i].y;
	}
}

template <typename T>
   void Corner::draw_points_or_line_corner(Ray_template<T>& loc_arr_to_draw, Matrix& loc_arr) //, Matrix & loc_arr
{
	size_t length;

	length = loc_arr_to_draw.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinates cell;

		cell.i = ZERO().i - loc_arr_to_draw[i].y;
		cell.j = (ZERO().j + (loc_arr_to_draw[i].x * (width_x_ + axis_x_indents_))) - axis_x_indents_;
		if (cell.i >= loc_arr.get_N() || cell.j >= loc_arr.get_M())
			throw std::exception("exception in hello.cpp -> metod draw_points : cell >= corner_arr()");
		loc_arr.set_at(cell.i, cell.j, loc_arr_to_draw[i].symbol); //@symbol

	}
}


/// <summary>
/// 
/// </summary>
/// <param name="loc_arr_to_draw"></param>
/// <param name="loc_arr"></param>
/// 

 template <typename T>
void Axys::draw_points_or_line_axys(Ray_template<T>& loc_arr_to_draw, Matrix& loc_arr) //, Matrix & loc_arr
{

	size_t length;

	length = loc_arr_to_draw.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinates cell;


		cell.i = ORIGIN_.i - loc_arr_to_draw[i].y;
		cell.j = (ORIGIN_.j + (loc_arr_to_draw[i].x * (width_x_ + axis_x_indents_ + 1))) + axis_x_indents_;

		if (cell.i >= loc_arr.get_N() || cell.j >= loc_arr.get_M()) //loc_arr.get_M()
			throw std::exception("exception in hello.cpp  -> metod draw_points_ is_axys");

		loc_arr.set_at(cell.i, cell.j, loc_arr_to_draw[i].symbol);
	}
}

void Corner::erase_point_from_corner(const Dot& dot)
{
	Coordinates cell;

	cell.i = ZERO().i - dot.y;
	cell.j = (ZERO().j + (dot.x * (width_x_ + axis_x_indents_))) - axis_x_indents_;

	if (cell.i < corner_arr().get_N() - axis_x_indents_ && (cell.j > width_y_ && cell.j < corner_arr().get_M()))
		corner_arr().set_at(cell.i, cell.j, 'E');
	else
		throw std::exception("exception in hello.cpp -> metod erase_point : cell coord");
}


// TO DO
void Axys::erase_point_from_axys(Dot& err)
{
	//erase_point(err, axys_arr_);
}


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
			break;
		}
	}
}

void Canvas_console::remove_rounding_line(const Dot& A, const Dot& B)
{
	Ray_template<Dot> erase_line_arr;

	erase_line_arr = calculate_line_with_rounding(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}

void Canvas_console::remove_no_rounding_line(const Dot& A, const Dot& B)
{
	Ray_template<Dot> erase_line_arr;

	erase_line_arr = calculate_line_swap(A, B);
	for (size_t i = 0; i < erase_line_arr.size(); ++i)
		remove_point(erase_line_arr[i]);
}


void Canvas_console::remove_line_total(const Dot& A, const Dot& B)
{
	remove_no_rounding_line(A,B);
	remove_rounding_line(A,B);
}

void Canvas_console::add_point_to_arr_for_print_line(const Dot& A, const Dot& B, bool is_round, char symbol)
{
	const Ray_template<Dot>& lockal_draw_line_arr = is_round ? calculate_line_with_rounding(A, B, symbol) : calculate_line_swap(A, B, symbol);

	size_t length = lockal_draw_line_arr.size();

	for (size_t i = 0; i < length; i++)
	{
		points_to_draw_.add_to_back(lockal_draw_line_arr[i]);
	}
}

Ray_template<Dot> Canvas_console::calculate_line_with_rounding(const Dot& A, const Dot& B, char symbol)
{
	Ray_template<Dot> lockal_line_arr;

	Dot coords;

	double min = A.x;
	double max = B.x;
	if (A.x > B.x) {
		min = B.x;
		max = A.x;
	}

	if (isEqual(min, max))
	{
		double start = A.y;
		double end = B.y;
		if (A.y < B.y) {
			start = B.y;
			end = A.y;
		}
		double step = get_step(coefficient);  // 1.0 / coefficient;
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

	double step = get_step(coefficient);  // 1.0 / coefficient;

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

	return lockal_line_arr;

	lockal_line_arr.clear();

	if (debug) {
		size_t length = points_to_draw_.size();
		for (size_t i = 0; i < length; i++)
		{
			std::cout << "\n" << points_to_draw_[i].x << " : " << points_to_draw_[i].y;
		}
	}
}


Ray_template<Dot> Canvas_console::calculate_line_swap(const Dot& A, const Dot& B, char symbol)
{
	Ray_template<Dot> lockal_line_arr;

	if (A.x == B.x && A.y == B.y)
	{
		return calculate_line_with_rounding(A, B);
	}

	int x1, y1, x2, y2;
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
		float y = y1 * (1. - k) + y2 * k;


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


void Axys::create( char axys_arr_fill_symbol)
{

	 insert( points_to_draw_);

	int max_y =  MAX_VIRTUAL_.y;
	int min_y =  MIN_VIRTUAL_.y;

	int max_x =  MAX_VIRTUAL_.x;
	int min_x =  MIN_VIRTUAL_.x;

	/// <Костыльвания>
	if ((min_x < 0 || min_y < 0) && (fabs(min_x) >= 10 || fabs(min_y) >= 10))
	{
		 width_x_ =  width_x_ - 1;
	}
	 width_y_ =  width_x_;
	/// </Костыльвания>

	int N, M;
	int size_N, size_M;
	size_N = fabs(min_y) > fabs(max_y) ?  get_distance_between(min_y, 0) :  get_distance_between(0, max_y);
	size_M = fabs(min_x) > fabs(max_x) ?  get_distance_between(min_x, 0) :  get_distance_between(0, max_x);

	if (fabs(min_y) == fabs(max_y))
		size_N = fabs(max_y);
	if (fabs(min_x) == fabs(max_x))
		size_M = fabs(max_x);

	int loc_width_x =  width_x_ +  axis_x_indents_ + 1; //+1 
	int loc_width_y =  width_y_ + 1;


	 width_x_with_indent_ = loc_width_x;
	 width_y_with_indent_ = loc_width_y;


	N = (size_N * 2) +  axis_x_strings_;
	M = (size_M * loc_width_x) + (loc_width_y);
	int M_ = M;
	M = M * 2 + (loc_width_y);

	if ( axys_arr_.is_empty()) {
		 axys_arr_ = Matrix(N, M);
		 axys_arr_.fill(axys_arr_fill_symbol);
	}

	int or_x = size_N;
	int or_y = M_ +  width_x_ - 1;

	 x_axis_filling( axys_arr_, size_M * 2 + 1, -size_M, size_N);
	 y_axis_filling( axys_arr_, N, size_N, M_); //- (loc_width_x + 1) -1, -1,


	 ORIGIN_.i = or_x;
	 ORIGIN_.j = or_y;

}


void Axys::draw_points( )
{
	draw_points_or_line_axys(points_to_draw_, axys_arr_);
	// draw_points_(false, true,  axys_arr_);
}
