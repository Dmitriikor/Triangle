#include "Corner.h"


void Corner::change_file_path(const std::string& address)
{
	std::string outfile_adress = address;
}

void  Corner::render_and_print(std::ostream& output)
{
	if (points_to_draw().size() == 0)
		return;

	if (isMatrixCalculated())
	{
		print(output);
		return;
	}

	Canvas_Matrix().clear();
	calculate_matrix();
	add_points_to_corner();
	isMatrixCalculated(true);

	print(output);
}

void Corner::render_matrix()
{
	if (points_to_draw().size() == 0)
		return;

	Canvas_Matrix().clear();
	calculate_matrix();
	add_points_to_corner();
	isMatrixCalculated(true);
}

void Corner::print(std::ostream& output)
{
	{
		for (size_t i = 0; i < Canvas_Matrix().get_N(); i++)
		{
			for (size_t j = 0; j < Canvas_Matrix().get_M(); j++)
			{
				output << Canvas_Matrix()[i][j];

			}
			output << std::endl;
		}

	}
}

void Corner::print() const
{
	{
		for (size_t i = 0; i < Canvas_Matrix().get_N(); i++)
		{
			for (size_t j = 0; j < Canvas_Matrix().get_M(); j++)
			{
				std::cout << Canvas_Matrix()[i][j];

			}
			std::cout << std::endl;
		}

	}
}

Corner::Corner() : Canvas_xy()
{
	ORIGIN_.i = 0;
	ORIGIN_.j = 0;
	outfile_adress = "Corner_out.txt";
}

void Corner::print_to_file()
{
	std::ofstream outfile_M(outfile_adress);
	print(outfile_M);
};


////void Corner::add_zero_point()
////{
////	Canvas_Matrix_().set_at(ORIGIN_.i, ORIGIN_.j - axis_x_indents(), '0'); //!!!
////}


void Corner::moving_points_from_ray_to_matrix() //, Matrix & loc_arr
{
	size_t length;

	length = points_to_draw().size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinate cell;

		cell.i = ORIGIN_.i - points_to_draw()[i].y;
		cell.j = (ORIGIN_.j + (points_to_draw()[i].x * (width_x() + axis_x_indents()))) - axis_x_indents();
		if (cell.i >= Canvas_Matrix().get_N() || cell.j >= Canvas_Matrix().get_M())
			throw std::runtime_error("exception in hello.cpp -> method draw_points : cell >= Canvas_Matrix");

		Canvas_Matrix().set_at(cell.i, cell.j, points_to_draw()[i].symbol); //@symbol

	}
}

void Corner::add_points_to_corner()
{
	moving_points_from_ray_to_matrix();
}


void Corner::erase_point_from_corner(const Dot& dot)
{
	Coordinate cell;

	cell.i = ORIGIN_.i - dot.y;
	cell.j = (ORIGIN_.j + (dot.x * (width_x() + axis_x_indents()))) - axis_x_indents();

	if (cell.i < Canvas_Matrix().get_N() - axis_x_indents() && (cell.j > width_y() && cell.j < Canvas_Matrix().get_M()))
		Canvas_Matrix().set_at(cell.i, cell.j, EMPTY());
	else
		throw std::runtime_error("exception in hello.cpp -> method erase_point : cell coordinates");
}

//!!! module sub-functions
void Corner::calculate_matrix()
{
	//!!! Coordinate
	initialize_width();


	int max_y = MAX_VIRTUAL().y;
	int min_y = MIN_VIRTUAL().y;

	int max_x = MAX_VIRTUAL().x;
	int min_x = MIN_VIRTUAL().x;

	{

		size_t N = utilities::get_distance_between(min_y, max_y) + 1;
		size_t M = utilities::get_distance_between(min_x, max_x) + 1;

		N = N + axis_x_strings();
		M = width_y() + (M * (width_x() + axis_x_indents())) + (width_x() + axis_x_indents());

		if (N > Canvas_Matrix().get_N() || M > Canvas_Matrix().get_M())
		{
			Canvas_Matrix() = Matrix<char>(N, M);
			Canvas_Matrix().fill(EMPTY());
		}
	}

	//// {print y axis
	int start_i = max_y > 0 ? max_y : 0;

	////width_y_with_indent() = width_y();

	{
		int N = Canvas_Matrix().get_N() - axis_x_strings();

		y_axis_filling(N, start_i, 0); //???????
	}
	// }end print y axis

	//{find actual console point of start coordinates
	//zero is shifted by max_y from top
	ORIGIN_.i = start_i;// +width_x_; //!x_axis_thickness
	//}find actual console point of start coordinates

	// {print x Axys
	{
		int start_x = min_x < 0 ? min_x : 0;

		int N__;

		if (min_x < 0 && max_x < 0 || min_x > 0 && max_x > 0)
		{
			N__ = std::abs(min_x) < std::abs(max_x) ? std::abs(max_x) : std::abs(min_x);
			N__ += 1;
		}
		else
			N__ = std::abs(min_x) + std::abs(max_x) + 1;

		size_t i_for_x = Canvas_Matrix().get_N() - axis_x_strings();

		width_x_with_indent(width_x() + axis_x_indents());
		
		x_axis_filling(N__, start_x, i_for_x);

		// }end print x axis

		//{find actual console point of start coordinates
		ORIGIN_.j = ((abs(start_x * (width_x() + axis_x_indents()))) + width_y() + ((width_x() + axis_x_indents()) - 1));
	}
	//}find actual console point of start coordinates
	// 
	//}end of work with axis 
}



