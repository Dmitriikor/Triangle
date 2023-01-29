#include "Axys.h"


void Axys::set_at(Coordinates_TEMPLATE cell, char symbol)
{
	axys_arr_.set_at(cell.i, cell.j, symbol);
}

void Axys::remove()
{
	axys_arr_.clear();
}

void  Axys::print()
{
	axys_arr_.clear();
	create();
	draw_points();
	axys_arr_.print();
	print_f_a(*this);
}

void Axys::create(char axys_arr_fill_symbol)
{

	insert(points_to_draw_);

	int max_y = MAX_VIRTUAL_.y;
	int min_y = MIN_VIRTUAL_.y;

	int max_x = MAX_VIRTUAL_.x;
	int min_x = MIN_VIRTUAL_.x;

	/// <Костыльвания>
	if ((min_x < 0 || min_y < 0) && (fabs(min_x) >= 10 || fabs(min_y) >= 10))
	{
		width_x_ = width_x_ - 1;
	}
	width_y_ = width_x_;
	/// </Костыльвания>

	int N, M;
	int size_N, size_M;
	size_N = fabs(min_y) > fabs(max_y) ? get_distance_between(min_y, 0) : get_distance_between(0, max_y);
	size_M = fabs(min_x) > fabs(max_x) ? get_distance_between(min_x, 0) : get_distance_between(0, max_x);

	if (fabs(min_y) == fabs(max_y))
		size_N = fabs(max_y);
	if (fabs(min_x) == fabs(max_x))
		size_M = fabs(max_x);

	int loc_width_x = width_x_ + axis_x_indents_ + 1; //+1 
	int loc_width_y = width_y_ + 1;


	width_x_with_indent_ = loc_width_x;
	width_y_with_indent_ = loc_width_y;


	N = (size_N * 2) + axis_x_strings_;
	M = (size_M * loc_width_x) + (loc_width_y);
	int M_ = M;
	M = M * 2 + (loc_width_y);

	if (axys_arr_.is_empty()) {
		axys_arr_ = Matrix<char>(N, M);
		axys_arr_.fill(axys_arr_fill_symbol);
	}

	int or_x = size_N;
	int or_y = M_ + width_x_ - 1;

	x_axis_filling(axys_arr_, size_M * 2 + 1, -size_M, size_N);
	y_axis_filling(axys_arr_, N, size_N, M_); //- (loc_width_x + 1) -1, -1,


	ORIGIN_.i = or_x;
	ORIGIN_.j = or_y;

}


void Axys::draw_points()
{
	draw_points_or_line_axys(points_to_draw_, axys_arr_);
	/// draw_points_(false, true,  axys_arr_);
}

template <typename T>
void Axys::draw_points_or_line_axys(Ray<T>& loc_arr_to_draw, Matrix<char>& loc_arr) //, Matrix & loc_arr
{

	size_t length;

	length = loc_arr_to_draw.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinates_TEMPLATE cell;


		cell.i = ORIGIN_.i - loc_arr_to_draw[i].y;
		cell.j = (ORIGIN_.j + (loc_arr_to_draw[i].x * (width_x_ + axis_x_indents_ + 1))) + axis_x_indents_;

		if (cell.i >= loc_arr.get_N() || cell.j >= loc_arr.get_M()) //loc_arr.get_M()
			throw std::runtime_error("exception in hello.cpp  -> method draw_points_ is_axys");

		loc_arr.set_at(cell.i, cell.j, loc_arr_to_draw[i].symbol);
	}
}



void print_f_a(Axys& this_)
{
	std::ofstream out_p(this_.outfile_adress);
	print_f_m(this_.axys_arr_, out_p);
}