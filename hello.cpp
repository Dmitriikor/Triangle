#include "hello.h"

Point MAX_VIRTUAL;
Point MIN_VIRTUAL;

void max_min_init()
{
	MAX_VIRTUAL.x = DBL_MIN;
	MAX_VIRTUAL.y = DBL_MIN;

	MIN_VIRTUAL.x = DBL_MAX;
	MIN_VIRTUAL.y = DBL_MAX;
}



Matrix canvas_arr;



//Point ZERO; //!!!
Coordinates ZERO;
Coordinates ORIGIN;

bool earse_line_flag = false;


Ray_3_ points_to_draw;		//ñâîáîäíûå òî÷êè äëÿ ðèñîâàíèÿ
Ray_3_ line_points_to_draw;	//òî÷êè ëèíèé äëÿ ðèñîâàíèÿ

bool is_copied_array = false;

int width_x = -1;
int width_y = -1;

int axis_x_indents = 1;
int axis_x_strings = 1;

int width_x_with_indent;
int width_y_with_indent;

int coefficient = 1;




bool debug;
void go_debug(bool is_debug)
{
	debug = is_debug;
}



//private
void initialize_min_max_points(const Ray_3_& points)
{
	points_to_draw = points;

	//if (is_need_to_copy_array)
		//copy_arr(points);

	size_t length = points.size();
	MAX_VIRTUAL = points[0];
	MIN_VIRTUAL = points[0];

	for (size_t i = 1; i < length; i++)
	{

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

void initialize_width() {
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

int get_distance_between(int min_coord, int max_coord)
{
	if (min_coord >= 0 && max_coord >= 0)
		return abs(max_coord);

	if (min_coord <= 0 && max_coord <= 0)
		return abs(min_coord);

	return abs(max_coord) + abs(min_coord);
}

void x_axis_filling(Matrix& arr, size_t axis_length, int min_x, int axis_location)
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
			//canvas_arr[i][j - 1] = ' '; //!!! here was [i][1]
	}
}

void y_axis_filling(Matrix& arr, size_t axis_length, int start_i, int axis_location)
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
			//canvas_arr[i][j - 1] = ' '; //!!! here was [i][1]
	}
}




//!!! module sub-functions
void create_corner()
{
	initialize_min_max_points(points_to_draw);
	int max_y = MAX_VIRTUAL.y;
	int min_y = MIN_VIRTUAL.y;

	int max_x = MAX_VIRTUAL.x;
	int min_x = MIN_VIRTUAL.x;



	{
		size_t N, M;

		N = get_distance_between(min_y, max_y) + 1;
		M = get_distance_between(min_x, max_x) + 1;

		N = N + axis_x_strings;
		M = width_y + (M * (width_x + axis_x_indents)) + (width_x + axis_x_indents);

		if (N > canvas_arr.get_N() || M > canvas_arr.get_M())
		{
			canvas_arr.create_matrix(N, M);
			canvas_arr.fill(' ');
		}
	}

	// {print y axis
	int start_i = max_y > 0 ? max_y : 0;

	width_y_with_indent = width_y;
	{
		int N = canvas_arr.get_N() - axis_x_strings;

		y_axis_filling(canvas_arr, N, start_i, 0); //???????
	}
	// }end print y axis

	//{find actual console point of start coodrs
	//zero is shifted by max_y from top
	ZERO.i = start_i;// +width_x; //!x_axis_thickness
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
			N__ = abs(min_x) + abs(max_x) +1;
		else
			N__ = max_x + 1;

		int i_for_x = canvas_arr.get_N() - axis_x_strings;

		width_x_with_indent = width_x + axis_x_indents;

		std::cout <<"\n canvas_arr = " << canvas_arr.get_M() <<" N__ = " << N__ << " start_x = " << start_x << " i_for_x = " << i_for_x << "\n";
		x_axis_filling(canvas_arr, N__, start_x, i_for_x);

		// }end print x axis

		//{find actual console point of start coodrs
		ZERO.j = ((abs(start_x * width_x_with_indent)) + width_y + (width_x_with_indent - 1));
	}
	//}find actual console point of start coodrs



	//std::cout << "\n" << "\t" << "ZERO.j = " << ZERO.j << " : ZERO.i = " << ZERO.i << "\n";

	//canvas_arr[ZERO.i][ZERO.j - axis_x_indents] = 'o';

	//}end of work wich axis 
}

//!!!maybe in matrix
void print_arr() {
	std::cout << "\n";

	if (canvas_arr.is_empty())
		canvas_arr.create_matrix(0, 0);
	//throw std::exception("exception in hello.cpp -> metod print_arr : canvas_arr.is_empty");

	canvas_arr.Matrix_print();
	std::cout << "\n";
}

void hello_try_set_min_max_by(Point pt, bool save_point)
{
	save_point = true; ///////////!!!!!!!!!!!!!!!!!!!!!!! to do
	if (save_point)
	{
		points_to_draw.add_to_back(pt);
		initialize_min_max_points(points_to_draw);
	}
	if (!save_point)
	{
		Ray_3_ pt_tmp;
		pt_tmp.add_to_back(pt);
		pt_tmp.print();
		initialize_min_max_points(pt_tmp);
	}

	/*
	bool is_new_set = false;
	if (MAX_VIRTUAL.x < pt.x)
	{
		MAX_VIRTUAL.x = pt.x;
		is_new_set = true;
	}
	if (MAX_VIRTUAL.y < pt.y)
	{
		MAX_VIRTUAL.y = pt.y;
		is_new_set = true;
	}
	if (MIN_VIRTUAL.x > pt.x)
	{
		MIN_VIRTUAL.x = pt.x;
		is_new_set = true;
	}
	if (MIN_VIRTUAL.y > pt.y)
	{
		MIN_VIRTUAL.y = pt.y;
		is_new_set = true;
	}
	if (is_new_set = true)
	*/
	canvas_clear();

}

void draw_points()
{
	draw_points_(false);
}

void draw_line()
{
	draw_points_(true);
}

void draw_points_(bool is_need_to_draw_line, bool is_axys, canvas_axys& a) //, Matrix & TT
{
	if (canvas_arr.is_empty())
		canvas_arr.create_matrix(1, 1);

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

			if (cell.i >= a.axys_arr.get_N() || cell.j >= a.axys_arr.get_M()) //TT.get_M()
				throw std::exception("exception in hello.cpp -> metod draw_points_for_axys : cell >= canvas_arr");

			a.set_at(cell, arr[i].symbol); //@symbol
		}
		else
		{
			cell.i = ZERO.i - arr[i].y;
			cell.j = (ZERO.j + (arr[i].x * (width_x + axis_x_indents))) - axis_x_indents;
			if (cell.i >= canvas_arr.get_N() || cell.j >= canvas_arr.get_M())
				throw std::exception("exception in hello.cpp -> metod draw_points : cell >= canvas_arr");
			canvas_arr.set_at(cell.i, cell.j, arr[i].symbol); //@symbol
		}

	}
}


//void draw_points_(bool is_need_to_draw_line)
//{
//	//!!! MIN MAX is set?
//	//! throw;
//
//	if (canvas_arr.is_empty())
//		canvas_arr.create_matrix(1, 1);
//	//throw std::exception("exception in hello.cpp -> metod draw_points : canvas_arr.is_empty");
//
//	const Ray_3_& arr = is_need_to_draw_line ? line_points_to_draw : points_to_draw;
//	size_t length = arr.size();
//
//
//	for (size_t i = 0; i < length; i++)
//	{
//		Coordinates cell;
//
//		cell.i = ZERO.i - arr[i].y;
//		cell.j = (ZERO.j + (arr[i].x * (width_x + axis_x_indents))) - axis_x_indents;
//
//		if (cell.i >= canvas_arr.get_N() || cell.j >= canvas_arr.get_M())
//			throw std::exception("exception in hello.cpp -> metod draw_points : cell >= canvas_arr");
//
//		canvas_arr.set_at(cell.i, cell.j, arr[i].symbol); //@symbol
//	}
//}

void erase_point(Point err)
{
	Coordinates cell;

	cell.i = ZERO.i - err.y;
	cell.j = (ZERO.j + (err.x * (width_x + axis_x_indents))) - axis_x_indents;

	if (cell.i < canvas_arr.get_N() - axis_x_indents && (cell.j > width_y && cell.j < canvas_arr.get_M()))
		canvas_arr.set_at(cell.i, cell.j, ' ');
	else
		throw std::exception("exception in hello.cpp -> metod erase_point : cell coord");
}

double get_step(unsigned coefficient)
{
	double step = 1.0 / coefficient;
	return step;
}

void canvas_print_zero()
{
	canvas_arr.set_at(ZERO.i, ZERO.j - axis_x_indents, '0'); //!!!
}

void canvas_clear()
{
	canvas_arr.clear_matrix();

	initialize_width();

	create_corner();
}

void delite_point(const Point& dl)
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

void delite_line(const Point& A, const Point& B)
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

void draw_line_1_(const Point& A, const Point& B, bool is_round, char symbol)
{
	const Ray_3_& lockal_draw_line_arr = is_round ? calculate_line_round(A, B, symbol) : calculate_line_swap(A, B, symbol);

	size_t length = lockal_draw_line_arr.size();

	for (size_t i = 0; i < length; i++)
	{
		line_points_to_draw.add_to_back(lockal_draw_line_arr[i]);
	}
}

Ray_3_ calculate_line_round(const Point& A, const Point& B, char symbol)
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


Ray_3_ calculate_line_swap(const Point& A, const Point& B, char symbol)
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


void canvas_axys::create_axys(char axys_arr_fill_symbol)
{

	initialize_min_max_points(points_to_draw);

	int max_y = MAX_VIRTUAL.y;
	int min_y = MIN_VIRTUAL.y;

	int max_x = MAX_VIRTUAL.x;
	int min_x = MIN_VIRTUAL.x;

	/// <Костыльвания>
	if ((min_x < 0 || min_y < 0) && (fabs(min_x) >= 10 || fabs(min_y) >= 10))
	{
		width_x = width_x - 1;
	}
	width_y = width_x;
	/// </Костыльвания>

	int N, M;
	int size_N, size_M;
	size_N = fabs(min_y) > fabs(max_y) ? get_distance_between(min_y, 0) : get_distance_between(0, max_y);
	size_M = fabs(min_x) > fabs(max_x) ? get_distance_between(min_x, 0) : get_distance_between(0, max_x);

	if (fabs(min_y) == fabs(max_y))
		size_N = fabs(max_y);
	if (fabs(min_x) == fabs(max_x))
		size_M = fabs(max_x);

	int loc_width_x = width_x + axis_x_indents; //+1 
	int loc_width_y = width_y + 1;


	width_x_with_indent = loc_width_x;
	width_y_with_indent = loc_width_y;


	N = (size_N * 2) + axis_x_strings;
	M = (size_M * loc_width_x) + (loc_width_y);
	int M_ = M;
	M = M * 2 + (loc_width_y);

	//axys_arr.clear_matrix();

	if (axys_arr.is_empty()) {
		axys_arr.create_matrix(N, M);
		axys_arr.fill(axys_arr_fill_symbol);
	}

	int or_x = size_N;
	int or_y = M_ + width_x - 1;

	x_axis_filling(axys_arr, size_M * 2 + 1, -size_M, size_N);
	//std::cout << "\n width_x = " << width_x << "  width_y = " << width_y << "\n";
	y_axis_filling(axys_arr, N, size_N, M_ - 1); //- (loc_width_x + 1) -1, -1,


	ORIGIN.i = or_x;
	ORIGIN.j = or_y;
	std::cout << "\n" << ORIGIN.i << " " << or_x << " " << ORIGIN.j << " " << or_y << "\n";
	axys_arr[ORIGIN.i][ORIGIN.j] = '*';

}



canvas_axys::canvas_axys()
{
}

canvas_axys::~canvas_axys()
{
}






	//for (int j = -(ORIGIN_Point.j); j < ORIGIN_Point.j + 1; j++) 
	//{
	//	axys_arr[ORIGIN_Point.i, ORIGIN_Point.j + j];
	//}
	//for (int i = -(ORIGIN_Point.i); i < ORIGIN_Point.i + 1; i++)  // axis X
	//{
	//	setCursorPosition(set_pos_x(i), ORIGIN_Point.j);
	//	std::cout << std::setw(shift_w) << std::left << fabs(i * step_is(coefficient)) << "\n";
	//}
	//std::cout << "\n";

	////draw_line_4(a, b, ORIGIN_Point, coefficient);


	//setCursorPosition(0, ORIGIN_Point.j * 2 + 2);

	//if (draw_triangle && draw_round)
	//{
	//	draw_line_4(triangle.get_A(), triangle.get_B(), ORIGIN_Point, coefficient);
	//	draw_line_4(triangle.get_B(), triangle.get_C(), ORIGIN_Point, coefficient);
	//	draw_line_4(triangle.get_C(), triangle.get_A(), ORIGIN_Point, coefficient);
	//}
	//if (draw_triangle && !draw_round)
	//{
	//	Point A_ = triangle.get_A();
	//	Point B_ = triangle.get_B();

	//	draw_line_2::draw_line_no_round(triangle.get_A(), triangle.get_B(), ORIGIN_Point);
	//	draw_line_2::draw_line_no_round(triangle.get_B(), triangle.get_C(), ORIGIN_Point);
	//	draw_line_2::draw_line_no_round(triangle.get_C(), triangle.get_A(), ORIGIN_Point);
	//}
	//setCursorPosition(0, ORIGIN_Point.j * 2 + 2);
