#include "Corner.h"


void Corner::fill(char fill_symbol)
{
	create(fill_symbol);
}

void  Corner::prepare(std::ostream& output)
{
	if (points_to_draw_.size() == 0)
		return;
	corner_arr().clear();
	create();
	add_points_to_corner();
	isMatrixCalculated = true;

	print(output);
	///std::ofstream outfile(outfile_adress);
	///print(outfile);
}

////void Corner::print() const
////{
////
////		///this->prepare();
////		///print_private();
////	}
////
////		corner_arr_.print();
////		///corner_arr_.clear();
////		///corner_arr_.fill('*');
////		///isMatrixCalculated = true;
////	}
////}

void Corner::print(std::ostream& output) const
{
	if (!isMatrixCalculated)
	{
		Corner test = *this;
		prepare_free(output, test);
		test.prepare(output);

		const_cast<Corner*>(this)->prepare(output);
	}
	else
	{

		for (size_t i = 0; i < corner_arr_.get_N(); i++)
		{
			for (size_t j = 0; j < corner_arr_.get_M(); j++)
			{
				output << corner_arr_[i][j];

			}
			output << std::endl;
		}
	}
}

void Corner::print_to_file() const
{
	std::ofstream outfile_M(outfile_adress);
	print(outfile_M);
};

void Corner::add_points_to_corner()
{
	draw_points_or_line_corner(points_to_draw_, corner_arr());
}

void Corner::add_zero_point()
{
	corner_arr().set_at(ORIGIN_.i, ORIGIN_.j - axis_x_indents_, '0'); //!!!
}

void Corner::clear()
{
	points_to_draw_.clear();
	corner_arr().clear();

	///initialize_width();

	///create();
	isMatrixCalculated = false;
}

template <typename T>
void Corner::draw_points_or_line_corner(Ray<T>& loc_arr_to_draw, Matrix<char>& loc_arr) //, Matrix & loc_arr
{
	size_t length;

	length = loc_arr_to_draw.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinate cell;

		cell.i = ORIGIN_.i - loc_arr_to_draw[i].y;
		cell.j = (ORIGIN_.j + (loc_arr_to_draw[i].x * (width_x_ + axis_x_indents_))) - axis_x_indents_;
		if (cell.i >= loc_arr.get_N() || cell.j >= loc_arr.get_M())
			throw std::runtime_error("exception in hello.cpp -> method draw_points : cell >= corner_arr()");

		loc_arr.set_at(cell.i, cell.j, loc_arr_to_draw[i].symbol); //@symbol

	}
}

void Corner::erase_point_from_corner(const Dot& dot)
{
	Coordinate cell;

	cell.i = ORIGIN_.i - dot.y;
	cell.j = (ORIGIN_.j + (dot.x * (width_x_ + axis_x_indents_))) - axis_x_indents_;

	if (cell.i < corner_arr().get_N() - axis_x_indents_ && (cell.j > width_y_ && cell.j < corner_arr().get_M()))
		corner_arr().set_at(cell.i, cell.j, 'E');
	else
		throw std::runtime_error("exception in hello.cpp -> method erase_point : cell coord");
}

//!!! module sub-functions
void Corner::create(char axys_arr_fill_symbol)
{
	//!!! Coordinate

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
	ORIGIN_.i = start_i;// +width_x_; //!x_axis_thickness
	//}find actual console point of start coodrs

	// {print x Axys
	{
		int start_x = min_x < 0 ? min_x : 0;


		int N__;
		//if (min_x == max_x)
		//{
		//	N__ = abs(min_x) + 1;
		//}
		//else if (min_x < 0)
		//	N__ = abs(min_x) + abs(max_x) + 1;
		//else
		//	N__ = max_x + 1;

		if (min_x < 0 && max_x < 0 || min_x > 0 && max_x > 0)
		{
			N__ = std::abs(min_x) < std::abs(max_x) ? std::abs(max_x) : std::abs(min_x);
			N__ += 1;
		}
		else
			N__ = std::abs(min_x) + std::abs(max_x) + 1;

		int i_for_x = corner_arr().get_N() - axis_x_strings_;

		width_x_with_indent_ = width_x_ + axis_x_indents_;

		x_axis_filling(corner_arr(), N__, start_x, i_for_x);

		// }end print x axis

		//{find actual console point of start coodrs
		ORIGIN_.j = ((abs(start_x * width_x_with_indent_)) + width_y_ + (width_x_with_indent_ - 1));
	}
	//}find actual console point of start coodrs
	// 
	//}end of work with axis 
}

//void Corner::change_file_path(const std::string& adress)
//{
//	outfile_adress = adress;
//}


	void  prepare_free(std::ostream& output, Corner& this_)
	{
		if (this_.points_to_draw_.size() == 0)
			return;
		this_.corner_arr().clear();
		this_.create();
		this_.add_points_to_corner();
		this_.isMatrixCalculated = true;

		this_.print(output);
		///std::ofstream outfile(outfile_adress);
		///print(outfile);
	}
