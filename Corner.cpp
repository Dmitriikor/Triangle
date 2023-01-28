#include "Corner.h"


void Corner::fill(char fill_symbol)
{
	create(fill_symbol);
}

void  Corner::print()
{
	corner_arr().clear();
	create();
	add_points_to_corner();
	corner_arr().print();
	print_f(*this);
}

void Corner::add_points_to_corner()
{
	draw_points_or_line_corner(points_to_draw_, corner_arr());
}

void Corner::print_zero()
{
	corner_arr().set_at(ZERO().i, ZERO().j - axis_x_indents_, '0'); //!!!
}

void Corner::clear()
{
	corner_arr().clear();

	initialize_width();

	create();
}

template <typename T>
void Corner::draw_points_or_line_corner(Ray<T>& loc_arr_to_draw, Matrix<char>& loc_arr) //, Matrix & loc_arr
{
	size_t length;

	length = loc_arr_to_draw.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinates_TEMPLATE cell;

		cell.i = ZERO().i - loc_arr_to_draw[i].y;
		cell.j = (ZERO().j + (loc_arr_to_draw[i].x * (width_x_ + axis_x_indents_))) - axis_x_indents_;
		if (cell.i >= loc_arr.get_N() || cell.j >= loc_arr.get_M())
			throw std::runtime_error("exception in hello.cpp -> method draw_points : cell >= corner_arr()");

		loc_arr.set_at(cell.i, cell.j, loc_arr_to_draw[i].symbol); //@symbol

	}
}

void Corner::erase_point_from_corner(const Dot& dot)
{
	Coordinates_TEMPLATE cell;

	cell.i = ZERO().i - dot.y;
	cell.j = (ZERO().j + (dot.x * (width_x_ + axis_x_indents_))) - axis_x_indents_;

	if (cell.i < corner_arr().get_N() - axis_x_indents_ && (cell.j > width_y_ && cell.j < corner_arr().get_M()))
		corner_arr().set_at(cell.i, cell.j, 'E');
	else
		throw std::runtime_error("exception in hello.cpp -> method erase_point : cell coord");
}

//!!! module sub-functions
void Corner::create(char axys_arr_fill_symbol)
{
	//!!! Coordinates_TEMPLATE

	int max_y = MAX_VIRTUAL_.y;
	int min_y = MIN_VIRTUAL_.y;

	int max_x = MAX_VIRTUAL_.x;
	int min_x = MIN_VIRTUAL_.x;

	{
		size_t N, M;

		N = get_distance_between(min_y, max_y) + 1;
		M = get_distance_between(min_x, max_x) + 1;

		N = N + axis_x_strings_;
		M = width_y_ + (M * (width_x_ + axis_x_indents_)) + (width_x_ + axis_x_indents_);

		if (N > corner_arr().get_N() || M > corner_arr().get_M())
		{
			corner_arr() = Matrix<char>(N, M);
			corner_arr().fill(axys_arr_fill_symbol);
		}
	}

	// {print y axis
	int start_i = max_y > 0 ? max_y : 0;

	width_y_with_indent_ = width_y_;
	{
		int N = corner_arr().get_N() - axis_x_strings_;

		y_axis_filling(corner_arr(), N, start_i, 0); //???????
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

		int i_for_x = corner_arr().get_N() - axis_x_strings_;

		width_x_with_indent_ = width_x_ + axis_x_indents_;

		x_axis_filling(corner_arr(), N__, start_x, i_for_x);

		// }end print x axis

		//{find actual console point of start coodrs
		ZERO().j = ((abs(start_x * width_x_with_indent_)) + width_y_ + (width_x_with_indent_ - 1));
	}
	//}find actual console point of start coodrs
	// 
	//}end of work with axis 
}

void Corner::remove(const Dot& dot_to_erase)
{
	remove_line_total(dot_to_erase, dot_to_erase);
	erase_point_from_corner(dot_to_erase);
}

void Corner::remove_line(const Dot& A, const Dot& B)
{
	remove_line_total(A, B);
}

void  Corner::change_file_path(std::string& adress)
{
	outfile_adress = adress;
}

void print_f(Corner& this_)
{
	std::ofstream out_p(this_.outfile_adress);
	print_f_m(this_.corner_arr_, out_p);
}
