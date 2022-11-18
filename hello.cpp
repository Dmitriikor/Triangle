#include "hello.h"
#include <string>;


void canvas::max_min_init()
{
	MAX_VIRTUAL.x = DBL_MIN;
	MAX_VIRTUAL.y = DBL_MIN;

	MIN_VIRTUAL.x = DBL_MAX;
	MIN_VIRTUAL.y = DBL_MAX;
}

void canvas::go_debug(bool is_debug)
{
	debug = is_debug;
}

void canvas::add_points(const Ray_3_& points)
{
	points_to_draw = points;

	//if (is_need_to_copy_array)
		//copy_arr(points);

	size_t length = points.size();
	MAX_VIRTUAL = points[0];
	MIN_VIRTUAL = points[0];

	for (size_t i = 1; i < length; i++)
	{
		//to do
		points_to_draw[i].symbol = '+'; // Kostilvaniay to do


		if (points[i].x > MAX_VIRTUAL.x)
			MAX_VIRTUAL.x = points[i].x;
		else if (points[i].x < MIN_VIRTUAL.x)
			MIN_VIRTUAL.x = points[i].x;

		if (points[i].y > MAX_VIRTUAL.y)
			MAX_VIRTUAL.y = points[i].y;
		else if (points[i].y < MIN_VIRTUAL.y)
			MIN_VIRTUAL.y = points[i].y;

		//hello_try_set_min_max_by(points[i], true);
	}

	/*std::cout << std::endl << MAX_VIRTUAL.x << " : " << MAX_VIRTUAL.y << std::endl;
	std::cout << std::endl << MIN_VIRTUAL.x << " : " << MIN_VIRTUAL.y << std::endl;*/

	initialize_width();
}

void canvas::initialize_width() {
	width_x = 1;
	width_y = 1;

	if (MIN_VIRTUAL.y < 0)
		width_y++;

	if (MIN_VIRTUAL.x < 0)
		width_x++;

	int x = abs(MAX_VIRTUAL.x) > abs(MIN_VIRTUAL.x) ? abs(MAX_VIRTUAL.x) : abs(MIN_VIRTUAL.x);
	while (x >= 10) {
		x = x / 10;
		width_x++;
	}

	int y = abs(MAX_VIRTUAL.y) > abs(MIN_VIRTUAL.y) ? abs(MAX_VIRTUAL.y) : abs(MIN_VIRTUAL.y);
	while (y >= 10) {
		width_y++;
		y = y / 10;
	}

	/*std::cout << std::endl << width_x << std::endl;
	std::cout << std::endl << width_y << std::endl;*/

}

int canvas::get_distance_between(int min_coord, int max_coord)
{
	if (min_coord >= 0 && max_coord >= 0)
		return abs(max_coord);

	if (min_coord <= 0 && max_coord <= 0)
		return abs(min_coord);

	return abs(max_coord) + abs(min_coord);
}

void canvas::x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location)
{
	size_t N = axis_length;

	for (size_t i = 0; i < N; i++)
	{
		int temp_x = min_x + i;

		//!!!
		//arr[axis_location][width_y_with_indent + (i * width_x_with_indent) + (width_x_with_indent - 1)] = '|';
		arr.set_at(axis_location, width_y_with_indent + (i * width_x_with_indent) + (width_x_with_indent - 1), '|');

		//std::cout << "\n"<< "min_x = " << min_x << "\n";
		//arr.Matrix_print();
		//std::cout << "\n";

		int abs_x = fabs(temp_x);
		int j;
		for (j = width_x_with_indent - 2; j >= 0; --j)
		{
			int digit = abs_x % 10;

			//arr[axis_location][width_y_with_indent + (i * width_x_with_indent) + j] = '0' + digit;

			arr.set_at(axis_location, width_y_with_indent + (i * width_x_with_indent) + j, '0' + digit);

			//std::cout << "\n";
			//arr.Matrix_print();
			//std::cout << "\n";

			abs_x = abs_x / 10;

			if (abs_x == 0)
				break;
		}

		if (j == -1)
		{
			arr.Matrix_print();
			throw std::exception("hello.cpp -> create_corner -> WRONG WIDTH_X");
		}


		if (temp_x < 0)
			//arr[axis_location][(width_y_with_indent + (i * width_x_with_indent) + j) - 1] = '-'; //!!! here was [i][1]
			arr.set_at(axis_location, (width_y_with_indent + (i * width_x_with_indent) + j) - 1, '-'); //!!! here was [i][1]
		//else
			//corner_arr[i][j - 1] = ' '; //!!! here was [i][1]
	}
}

void canvas::y_axis_filling(Matrix& arr, size_t axis_length, int start_i, int axis_location)
{
	for (size_t i = 0; i < axis_length; ++i)
	{
		int temp_y = start_i - i;

		int abs_y = fabs(temp_y);
		int j;
		for (j = width_y_with_indent - 1; j >= 0; --j)
		{
			int digit = abs_y % 10;

			//arr[i][axis_location + j] = '0' + digit;
			arr.set_at(i, axis_location + j, '0' + digit);

			abs_y = abs_y / 10;
			if (abs_y == 0)
				break;
		}

		if (j == -1)
			throw std::exception("hello.cpp -> create_corner -> WRONG WIDTH_Y");

		if (temp_y < 0) {
			//arr[i][(axis_location + j) - 1] = '-'; //!!! here was [i][1]
			arr.set_at(i, (axis_location + j) - 1, '-'); //!!! here was [i][1]
		}

		//else
			//corner_arr[i][j - 1] = ' '; //!!! here was [i][1]
	}
}




//!!! module sub-functions
void corner::create_corner(canvas& this_, char axys_arr_fill_symbol)
{
	this_.add_points(this_.points_to_draw);
	int max_y = this_.MAX_VIRTUAL.y;
	int min_y = this_.MIN_VIRTUAL.y;

	int max_x = this_.MAX_VIRTUAL.x;
	int min_x = this_.MIN_VIRTUAL.x;



	{
		size_t N, M;

		N = this_.get_distance_between(min_y, max_y) + 1;
		M = this_.get_distance_between(min_x, max_x) + 1;

		N = N + this_.axis_x_strings;
		M = this_.width_y + (M * (this_.width_x + this_.axis_x_indents)) + (this_.width_x + this_.axis_x_indents);

		if (N > this_.corner_arr.get_N() || M > this_.corner_arr.get_M())
		{
			this_.corner_arr.create_matrix(N, M);
			this_.corner_arr.fill(axys_arr_fill_symbol);
		}
	}

	// {print y axis
	int start_i = max_y > 0 ? max_y : 0;

	this_.width_y_with_indent = this_.width_y;
	{
		int N = this_.corner_arr.get_N() - this_.axis_x_strings;

		this_.y_axis_filling(this_.corner_arr, N, start_i, 0); //???????
	}
	// }end print y axis

	//{find actual console point of start coodrs
	//zero is shifted by max_y from top
	this_.ZERO.i = start_i;// +width_x; //!x_axis_thickness
	//}find actual console point of start coodrs

	// {print x axys
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

		int i_for_x = this_.corner_arr.get_N() - this_.axis_x_strings;

		this_.width_x_with_indent = this_.width_x + this_.axis_x_indents;

		//std::cout <<"\n corner_arr = " << corner_arr.get_M() <<" N__ = " << N__ << " start_x = " << start_x << " i_for_x = " << i_for_x << "\n";
		this_.x_axis_filling(this_.corner_arr, N__, start_x, i_for_x);

		// }end print x axis

		//{find actual console point of start coodrs
		this_.ZERO.j = ((abs(start_x * this_.width_x_with_indent)) + this_.width_y + (this_.width_x_with_indent - 1));
	}
	//}find actual console point of start coodrs



	//std::cout << "\n" << "\t" << "ZERO.j = " << ZERO.j << " : ZERO.i = " << ZERO.i << "\n";

	//corner_arr[ZERO.i][ZERO.j - axis_x_indents] = 'o';

	//}end of work wich axis 
}


void corner::draw_lines(const Point& A, const Point& B, bool is_round, char symbol, canvas& this_)
{
	this_.try_set_min_max_by(A);
	this_.try_set_min_max_by(B);

	delite_corner(this_);
	
	this_.add_point_to_arr_for_print_line(A, B, is_round, symbol);
	this_.draw_points_(true, false, this_.corner_arr);
}

void corner::draw_lines(canvas& this_)
{
		this_.draw_points_(true, false, this_.corner_arr);
}

void corner::draw_points(canvas& this_)
{
	this_.draw_points_(false, false, this_.corner_arr);
}

void corner::corner_print_zero(canvas& this_)
{
	this_.corner_arr.set_at(this_.ZERO.i, this_.ZERO.j - this_.axis_x_indents, '0'); //!!!
}

void corner::delite_corner(canvas& this_)
{
	this_.corner_arr.clear_matrix();

	this_.initialize_width();

	/*?*/  create_corner(this_);  ///?
}



void canvas::try_set_min_max_by(Point pt, bool save_point)
{
	save_point = true; ///////////!!!!!!!!!!!!!!!!!!!!!!! to do
	if (save_point)
	{
		points_to_draw.add_to_back(pt);
		add_points(points_to_draw);
	}
	if (!save_point)
	{
		Ray_3_ pt_tmp;
		pt_tmp.add_to_back(pt);
		pt_tmp.print();
		add_points(pt_tmp);
	}
}



void canvas::draw_points_(bool is_need_to_draw_line, bool is_axys, Matrix& TT) //, Matrix & TT
{
	//if (TT.is_empty())
		//throw std::exception("!!!!");


	size_t length;

	const Ray_3_& arr = is_need_to_draw_line ? line_points_to_draw : points_to_draw;
	length = arr.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinates cell;

		if (is_axys)
		{
			cell.i = ORIGIN.i - arr[i].y;
			cell.j = (ORIGIN.j + (arr[i].x * (width_x + axis_x_indents)));

			if (cell.i >= TT.get_N() || cell.j >= TT.get_M()) //TT.get_M()
				throw std::exception("exception in hello.cpp  -> metod draw_points_ is_axys");

			TT.set_at(cell.i, cell.j, arr[i].symbol);
			//set_at(cell, arr[i].symbol); //@symbol
		}
		else
		{
			cell.i = ZERO.i - arr[i].y;
			cell.j = (ZERO.j + (arr[i].x * (width_x + axis_x_indents))) - axis_x_indents;
			if (cell.i >= TT.get_N() || cell.j >= TT.get_M())
				throw std::exception("exception in hello.cpp -> metod draw_points : cell >= corner_arr");
			TT.set_at(cell.i, cell.j, arr[i].symbol); //@symbol
		}
	}
}

void canvas::erase_point(Point& err)
{
	Coordinates cell;

	cell.i = ZERO.i - err.y;
	cell.j = (ZERO.j + (err.x * (width_x + axis_x_indents))) - axis_x_indents;

	if (cell.i < corner_arr.get_N() - axis_x_indents && (cell.j > width_y && cell.j < corner_arr.get_M()))
		corner_arr.set_at(cell.i, cell.j, ' ');
	else
		throw std::exception("exception in hello.cpp -> metod erase_point : cell coord");
}

double get_step(unsigned coefficient)
{
	double step = 1.0 / coefficient;
	return step;
}


void canvas::delite_point(const Point& dl)
{
	size_t length = line_points_to_draw.size();

	for (size_t i = 0; i < length; i++)
	{
		if (dl == line_points_to_draw[i])
		{
			line_points_to_draw.remove(i);
			--length;
		}
		erase_point(line_points_to_draw[i]);
	}
	delite_line(dl, dl);
}

void canvas::delite_line(const Point& A, const Point& B)
{
	Ray_3_ erase_line_arr;      //òî÷êè äëÿ çàòèðàíèÿ õîëñòà ëèíèÿìè

	for (size_t i = 0; i < 2; i++)
	{

		if (i == 0)
			erase_line_arr = calculate_line_round(A, B);
		else
			erase_line_arr = calculate_line_swap(A, B);

		size_t length_to_erase = erase_line_arr.size();
		size_t length_to_line_arr = line_points_to_draw.size();

		for (size_t i = 0; i < length_to_erase; i++)
		{
			erase_point(erase_line_arr[i]);
			for (size_t j = 0; j < length_to_line_arr; j++)
			{
				if (erase_line_arr[i] == line_points_to_draw[j])
				{
					line_points_to_draw.remove(j);
					--length_to_line_arr;
				}
			}
		}
		erase_line_arr.clear();
	}
}

void canvas::add_point_to_arr_for_print_line(const Point& A, const Point& B, bool is_round, char symbol)
{
	const Ray_3_& lockal_draw_line_arr = is_round ? calculate_line_round(A, B, symbol) : calculate_line_swap(A, B, symbol);

	size_t length = lockal_draw_line_arr.size();

	for (size_t i = 0; i < length; i++)
	{
		line_points_to_draw.add_to_back(lockal_draw_line_arr[i]);
	}
}

Ray_3_ canvas::calculate_line_round(const Point& A, const Point& B, char symbol)
{
	Ray_3_ lockal_line_arr;

	Point coords;

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
		Point point;
		point.x = A.x;
		for (double y = start; y >= end; y -= step)
		{
			point.y = y;

			point.x = (int)utilities::round_by_step(point.x, step);
			point.y = (int)utilities::round_by_step(point.y, step);


			//if (delite_line_flag)
			//	delite_line_arr.add_to_back(point);
			//else
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
		Point point;
		point.x = rounded_min + i * step;
		point.y = k * point.x + b;

		point.x = (int)utilities::round_by_step(point.x, step);
		point.y = (int)utilities::round_by_step(point.y, step);

		//if (delite_line_flag)
		//	delite_line_arr.add_to_back(point);
		//else
		point.symbol = symbol;
		lockal_line_arr.add_to_back(point);
	}

	return lockal_line_arr;

	lockal_line_arr.clear();

	if (debug) {
		size_t length = line_points_to_draw.size();
		for (size_t i = 0; i < length; i++)
		{
			std::cout << "\n" << line_points_to_draw[i].x << " : " << line_points_to_draw[i].y;
		}
	}
}


Ray_3_ canvas::calculate_line_swap(const Point& A, const Point& B, char symbol)
{
	Ray_3_ lockal_line_arr;

	if (A.x == B.x && A.y == B.y)
	{
		return calculate_line_round(A, B);
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

		Point coords;
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


void axys::create_axys(canvas& this_, char axys_arr_fill_symbol)
{

	this_.add_points(this_.points_to_draw);

	int max_y = this_.MAX_VIRTUAL.y;
	int min_y = this_.MIN_VIRTUAL.y;

	int max_x = this_.MAX_VIRTUAL.x;
	int min_x = this_.MIN_VIRTUAL.x;

	/// <Костыльвания>
	if ((min_x < 0 || min_y < 0) && (fabs(min_x) >= 10 || fabs(min_y) >= 10))
	{
		this_.width_x = this_.width_x - 1;
	}
	this_.width_y = this_.width_x;
	/// </Костыльвания>

	int N, M;
	int size_N, size_M;
	size_N = fabs(min_y) > fabs(max_y) ? this_.get_distance_between(min_y, 0) : this_.get_distance_between(0, max_y);
	size_M = fabs(min_x) > fabs(max_x) ? this_.get_distance_between(min_x, 0) : this_.get_distance_between(0, max_x);

	if (fabs(min_y) == fabs(max_y))
		size_N = fabs(max_y);
	if (fabs(min_x) == fabs(max_x))
		size_M = fabs(max_x);

	int loc_width_x = this_.width_x + this_.axis_x_indents; //+1 
	int loc_width_y = this_.width_y + 1;


	this_.width_x_with_indent = loc_width_x;
	this_.width_y_with_indent = loc_width_y;


	N = (size_N * 2) + this_.axis_x_strings;
	M = (size_M * loc_width_x) + (loc_width_y);
	int M_ = M;
	M = M * 2 + (loc_width_y);

	//axys_arr.clear_matrix();

	if (this_.axys_arr.is_empty()) {
		this_.axys_arr.create_matrix(N, M);
		this_.axys_arr.fill(axys_arr_fill_symbol);
	}

	int or_x = size_N;
	int or_y = M_ + this_.width_x - 1;

	this_.x_axis_filling(this_.axys_arr, size_M * 2 + 1, -size_M, size_N);
	//std::cout << "\n width_x = " << width_x << "  width_y = " << width_y << "\n";
	this_.y_axis_filling(this_.axys_arr, N, size_N, M_ - 1); //- (loc_width_x + 1) -1, -1,


	this_.ORIGIN.i = or_x;
	this_.ORIGIN.j = or_y;
	//std::cout << "\n" << this_.ORIGIN.i << " " << or_x << " " << this_.ORIGIN.j << " " << or_y << "\n";
	// print on zero coords
	//this_.axys_arr[this_.ORIGIN.i][this_.ORIGIN.j] = '*';

}

void  axys::draw_lines(canvas& this_)
{
	this_.draw_points_(true, true, this_.axys_arr);
}

void axys::axys::draw_points(canvas& this_)
{
	this_.draw_points_(false, true, this_.axys_arr);
}
