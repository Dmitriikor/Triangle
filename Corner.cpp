#include "Corner.h"


void Corner::fill(char fill_symbol)
{
	create(fill_symbol);
}

void  Corner::prepare(std::ostream& output) const
{
	if (points_to_draw_.size() == 0)
		return;
	Canvas_Matrix.clear();
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
////		Canvas_Matrix.print();
////		///Canvas_Matrix.clear();
////		///Canvas_Matrix.fill('*');
////		///isMatrixCalculated = true;
////	}
////}

void Corner::print(std::ostream& output) const
{
	if (!isMatrixCalculated)
	{
		//Corner test = *this;
		//prepare_free(output, test);
		//test.prepare(output);
		prepare(output);
		//const_cast<Corner*>(this)->prepare(output);
	}
	else
	{

		for (size_t i = 0; i < Canvas_Matrix.get_N(); i++)
		{
			for (size_t j = 0; j < Canvas_Matrix.get_M(); j++)
			{
				output << Canvas_Matrix[i][j];

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


void Corner::add_zero_point()
{
	Canvas_Matrix.set_at(ORIGIN_.i, ORIGIN_.j - axis_x_indents_, '0'); //!!!
}

void Corner::clear()
{
	points_to_draw_.clear();
	Canvas_Matrix.clear();

	///initialize_width();

	///create();
	isMatrixCalculated = false;
}

void Corner::draw_points_or_line_corner() const //, Matrix & loc_arr
{
	size_t length;

	length = points_to_draw_.size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinate cell;

		cell.i = ORIGIN_.i - points_to_draw_[i].y;
		cell.j = (ORIGIN_.j + (points_to_draw_[i].x * (width_x_ + axis_x_indents_))) - axis_x_indents_;
		if (cell.i >= Canvas_Matrix.get_N() || cell.j >= Canvas_Matrix.get_M())
			throw std::runtime_error("exception in hello.cpp -> method draw_points : cell >= Canvas_Matrix");

		Canvas_Matrix.set_at(cell.i, cell.j, points_to_draw_[i].symbol); //@symbol

	}
}

void Corner::add_points_to_corner() const
{
	draw_points_or_line_corner();
}


void Corner::erase_point_from_corner(const Dot& dot)
{
	Coordinate cell;

	cell.i = ORIGIN_.i - dot.y;
	cell.j = (ORIGIN_.j + (dot.x * (width_x_ + axis_x_indents_))) - axis_x_indents_;

	if (cell.i < Canvas_Matrix.get_N() - axis_x_indents_ && (cell.j > width_y_ && cell.j < Canvas_Matrix.get_M()))
		Canvas_Matrix.set_at(cell.i, cell.j, 'E');
	else
		throw std::runtime_error("exception in hello.cpp -> method erase_point : cell coord");
}

//!!! module sub-functions
void Corner::create(char axys_arr_fill_symbol) const
{
	//!!! Coordinate

	int max_y = MAX_VIRTUAL().y;
	int min_y = MIN_VIRTUAL().y;

	int max_x = MAX_VIRTUAL().x;
	int min_x = MIN_VIRTUAL().x;

	{
		size_t N, M;

		N = get_distance_between(min_y, max_y) + 1;
		M = get_distance_between(min_x, max_x) + 1;

		N = N + axis_x_strings_;
		M = width_y_ + (M * (width_x_ + axis_x_indents_)) + (width_x_ + axis_x_indents_);

		if (N > Canvas_Matrix.get_N() || M > Canvas_Matrix.get_M())
		{
			Canvas_Matrix = Matrix<char>(N, M);
			Canvas_Matrix.fill(axys_arr_fill_symbol);
		}
	}

	// {print y axis
	int start_i = max_y > 0 ? max_y : 0;

	width_y_with_indent_ = width_y_;
	{
		int N = Canvas_Matrix.get_N() - axis_x_strings_;

		y_axis_filling(Canvas_Matrix, N, start_i, 0); //???????
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

		int i_for_x = Canvas_Matrix.get_N() - axis_x_strings_;

		width_x_with_indent_ = width_x_ + axis_x_indents_;

		x_axis_filling(Canvas_Matrix, N__, start_x, i_for_x);

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
		this_.Canvas_Matrix.clear();
		this_.create();
		this_.add_points_to_corner();
		this_.isMatrixCalculated = true;

		this_.print(output);
		///std::ofstream outfile(outfile_adress);
		///print(outfile);
	}
