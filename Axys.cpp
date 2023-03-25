#include "Axys.h"

void Axys::remove()
{
	Canvas_Matrix().clear();
	isMatrixCalculated(false);
}


void Axys::render_matrix()
{
	if (points_to_draw().size() == 0)
		return;
	if (!isMatrixCalculated()) {
		Canvas_Matrix().clear();
		
		calculate_matrix();
		moving_points_from_ray_to_matrix();
		isMatrixCalculated(true);
	}
	return;
}

void Axys::print() const
{
	Canvas_Matrix().print();
}

void Axys::calculate_matrix()
{
	if (points_to_draw().size() == 0)
		return;

	//Canvas::insert(points_to_draw_);

	initialize_width();

	int max_y = MAX_VIRTUAL().y;
	int min_y = MIN_VIRTUAL().y;

	int max_x = MAX_VIRTUAL().x;
	int min_x = MIN_VIRTUAL().x;

	int width_x_loc = width_x();
	int width_y_loc = width_y();

	
	if ((min_x < 0 || min_y < 0) && (fabs(min_x) >= 10 || fabs(min_y) >= 10))
	{
		width_x_loc = width_x() - 1;
	}
	width_y_loc = width_x();
	

	int N, M;
	int size_N, size_M;
	size_N = fabs(min_y) > fabs(max_y) ? utilities::get_distance_between(min_y, 0) : utilities::get_distance_between(0, max_y);
	size_M = fabs(min_x) > fabs(max_x) ? utilities::get_distance_between(min_x, 0) : utilities::get_distance_between(0, max_x);

	if (fabs(min_y) == fabs(max_y))
		size_N = fabs(max_y);
	if (fabs(min_x) == fabs(max_x))
		size_M = fabs(max_x);

	int loc_width_x = width_x_loc + axis_x_indents() + 1; //+1 
	int loc_width_y = width_y_loc; // +1;


	width_x_with_indent(loc_width_x);
	width_y_with_indent(loc_width_y);


	N = (size_N * 2) + axis_x_strings();
	M = (size_M * loc_width_x) + (loc_width_y);
	int M_ = M;
	M = M * 2 + (loc_width_y);

	if (Canvas_Matrix().is_empty()) {
		Canvas_Matrix() = Matrix<char>(N, M);
		Canvas_Matrix().fill(EMPTY());
	}

	int or_x = size_N;
	int or_y = M_ + width_x_loc - 1;

	x_axis_filling(size_M * 2 + 1, -size_M, size_N);
	y_axis_filling( N, size_N, M_-1); //- (loc_width_x + 1) -1, -1,
	///Canvas_Matrix_().print();

	ORIGIN_.i = or_x;
	ORIGIN_.j = or_y;

}

void Axys::moving_points_from_ray_to_matrix() //, Matrix & loc_arr
{

	size_t length;
	
	length = points_to_draw().size();

	for (size_t i = 0; i < length; i++)
	{
		Coordinate cell;


		cell.i = ORIGIN_.i - points_to_draw()[i].y;
		///std::cout << "\n" << ORIGIN_.i << " " << points_to_draw()[i].y;
		///std::cout << "\n" << cell.i;
		cell.j = (ORIGIN_.j + (points_to_draw()[i].x * (width_x() + axis_x_indents()))) + axis_x_indents();

		(46 + (-11 * (3 + 1 ))) + 1;
		///std::cout << "\n"<< ORIGIN_.j << points_to_draw()[i].x << " " << width_x() << " " << axis_x_indents();
		///std::cout << "\n" << cell.j;
		if (cell.i >= Canvas_Matrix().get_N() || cell.j >= Canvas_Matrix().get_M()) //loc_arr.get_M()
			throw std::runtime_error("exception in hello.cpp  -> method draw_points_ is_axys");

		Canvas_Matrix().set_at(cell.i, cell.j, points_to_draw()[i].symbol);
	}
}
