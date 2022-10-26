#include "hello.h"

Point MAX_VIRTUAL;
Point MIN_VIRTUAL;

Matrix canvas_arr;

//Point ZERO; //!!!
Coordinates ZERO;

bool earse_line_flag = false;


Ray_3_ points_to_draw;		//свободные точки для рисования
Ray_3_ line_points_to_draw;	//точки линий для рисования

bool is_copied_array = false;

int width_x = -1;
int width_y = -1;

int axis_x_indents = 1;
int axis_x_strings = 1;

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

	}

	/*std::cout << std::endl << MAX_VIRTUAL.x << " : " << MAX_VIRTUAL.y << std::endl;
	std::cout << std::endl << MIN_VIRTUAL.x << " : " << MIN_VIRTUAL.y << std::endl;*/
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

//!!! module sub-functions
void create_corner() {

	int max_y = MAX_VIRTUAL.y;
	int min_y = MIN_VIRTUAL.y;

	int max_x = MAX_VIRTUAL.x;
	int min_x = MIN_VIRTUAL.x;


	{
		size_t N, M;
		N = get_distance_between(min_y, max_y) + 1;
		M = get_distance_between(min_x, max_x) + 1;

		N = N + axis_x_strings;
		M = M * (width_x + axis_x_indents) + width_y;

		canvas_arr.create_matrix(N, M);
		canvas_arr.fill(' ');
	}

	// {print y axis
	int start_i = max_y > 0 ? max_y : 0;

	for (size_t i = 0; i < canvas_arr.get_N() - axis_x_strings; ++i)
	{
		int temp_y = start_i - i;

		int abs_y = fabs(temp_y);
		int j;
		for (j = width_y - 1; j >= 0; --j)
		{
			int digit = abs_y % 10;

			canvas_arr[i][j] = '0' + digit;

			abs_y = abs_y / 10;
			if (abs_y == 0)
				break;
		}

		if (j == -1)
			throw std::exception("hello.cpp -> create_corner -> WRONG WIDTH_Y");

		if (temp_y < 0)
			canvas_arr[i][j - 1] = '-'; //!!! here was [i][1]
		//else
			//canvas_arr[i][j - 1] = ' '; //!!! here was [i][1]

	}
	// }end print y axis

	//{find actual console point of start coodrs
	//zero is shifted by max_y from top
	ZERO.i = start_i;// +width_x; //!x_axis_thickness
	//}find actual console point of start coodrs

	// {print x axys
	int start_x = min_x < 0 ? min_x : 0;
	int N = abs(min_x) + abs(max_x) + 1;
	int i_for_x = canvas_arr.get_N() - axis_x_strings;
	int width_x_with_indent = width_x + axis_x_indents;


	for (size_t i = 0; i < N; i++)
	{
		int temp_x = min_x + i;
		
		canvas_arr[i_for_x][width_y + (i * width_x_with_indent) + (width_x_with_indent - 1)] = '|';

		int abs_x = fabs(temp_x);
		int j;
		for (j = width_x_with_indent - 2; j >= 0; --j)
		{
			int digit = abs_x % 10;

			canvas_arr[i_for_x][width_y + (i * width_x_with_indent) + j] = '0' + digit;

			abs_x = abs_x / 10;

			if (abs_x == 0)
				break;
		}

		if (j == -1)
			throw std::exception("hello.cpp -> create_corner -> WRONG WIDTH_Y");

		if (temp_x < 0)
			canvas_arr[i_for_x][(width_y + (i * width_x_with_indent) + j) - 1] = '-'; //!!! here was [i][1]
		//else
			//canvas_arr[i][j - 1] = ' '; //!!! here was [i][1]
	}
	// }end print x axis

	//{find actual console point of start coodrs
	ZERO.j = ((abs(start_x * width_x_with_indent)) + width_y + (width_x_with_indent - 1)); //!!!!!SHIFT
	//}find actual console point of start coodrs



	//std::cout << "\n" << "\t" << "ZERO.j = " << ZERO.j << " : ZERO.i = " << ZERO.i << "\n";

	//canvas_arr[ZERO.i][ZERO.j - axis_x_indents] = 'o';

	//}end of work wich axis 
}

//!!!maybe in matrix
void print_arr() {
	std::cout << "\n";
	//for (size_t i = 0; i < canvas_arr.get_N(); i++)
	//{
	//	for (size_t j = 0; j < canvas_arr.get_M(); j++)
	//	{
	//		std::cout << canvas_arr[i][j];
	//	}
	//	std::cout << "\n";
	//}

	if (canvas_arr.is_empty())
		create_corner();
			//throw std::exception("exception in hello.cpp -> metod print_arr : canvas_arr.is_empty");

	canvas_arr.Matrix_print();
	std::cout << "\n";
}

void hello_try_set_min_max_by(Point pt, bool save_point)
{
	//if (save_point)
		//points_to_draw.add_to_back(pt);

	if (MAX_VIRTUAL.x < pt.x)
	{
		MAX_VIRTUAL.x = pt.x;
		canvas_clear();
	}
	if (MAX_VIRTUAL.y < pt.y)
	{
		MAX_VIRTUAL.y = pt.y;
		canvas_clear();
	}
	if (MIN_VIRTUAL.x > pt.x)
	{
		MIN_VIRTUAL.x = pt.x;
		canvas_clear();
	}

	if (MIN_VIRTUAL.y > pt.y)
	{
		MIN_VIRTUAL.y = pt.y;
		canvas_clear();
	}
}

void draw_points()
{
	draw_points_(false);
}

void draw_line()
{
	draw_points_(true);
}

void draw_points_(bool is_need_to_draw_line)
{
	//!!! MIN MAX is set?
	//! throw;
	
	if (canvas_arr.is_empty())
		create_corner();
			//throw std::exception("exception in hello.cpp -> metod draw_points : canvas_arr.is_empty");

	const Ray_3_& arr = is_need_to_draw_line ? line_points_to_draw : points_to_draw;
	size_t length = arr.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinates cell;

		cell.i = ZERO.i - arr[i].y;
		cell.j = (ZERO.j + (arr[i].x * (width_x + axis_x_indents))) - axis_x_indents;

		
		canvas_arr.set_at(cell.i, cell.j, arr[i].symbol); //@symbol
	}
	/*
	std::cout << "\n";
	print_arr();
	std::cout << "\n";
	*/
}

//void erase(bool is_need_to_erase_line)
//{
//	draw_points_(is_need_to_erase_line, ' ');
//}
//
//void erase_lines()
//{
//	erase(true);
//}
//void erase_points()
//{
//	erase(false);
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


double get_step(unsigned coefficient) {
	double step = 1.0 / coefficient;
	return step;
}

void canvas_print_zero() 
{
	canvas_arr[ZERO.i][ZERO.j - axis_x_indents] = '0';
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
	delite_line(dl,dl);
}


void delite_line(const Point& A, const Point& B)
{
	Ray_3_ erase_line_arr;      //точки для затирания холста линиями

	erase_line_arr = hello_draw_line_1(A, B);

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

void draw_line_1_(const Point& A, const Point& B, char symbol)
{
	Ray_3_ lockal_draw_line_arr;
	lockal_draw_line_arr = hello_draw_line_1(A, B);

	size_t length = lockal_draw_line_arr.size();

	for (size_t i = 0; i < length; i++)
	{
		lockal_draw_line_arr[i].symbol = symbol;
		line_points_to_draw.add_to_back(lockal_draw_line_arr[i]);
	}	
	lockal_draw_line_arr.clear();
}


Ray_3_ hello_draw_line_1(const Point& A, const Point& B)
{
	Ray_3_ lockal_line_arr;

	int coefficient = 1;

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
