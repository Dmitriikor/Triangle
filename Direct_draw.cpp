#include "Direct_draw.h"


void Direct_draw::calculate_matrix()
{
	double max_value_x = std::max(std::abs(MAX_VIRTUAL().x), std::abs(MIN_VIRTUAL().x));
	double max_value_y = std::max(std::abs(MAX_VIRTUAL().y), std::abs(MIN_VIRTUAL().y));
	////double max_value_x = (((std::abs(MAX_VIRTUAL().x)) > (std::abs(MIN_VIRTUAL().x))) ? (std::abs(MAX_VIRTUAL().x)) : (std::abs(MIN_VIRTUAL().x))) + 1;
	////double max_value_y = (((std::abs(MAX_VIRTUAL().y)) > (std::abs(MIN_VIRTUAL().y))) ? (std::abs(MAX_VIRTUAL().y)) : (std::abs(MIN_VIRTUAL().y))) + 1;
	
	Canvas_Matrix_().resize(max_value_y+1, max_value_x+1); ////(std::abs(MAX_VIRTUAL().x) + std::abs(MIN_VIRTUAL().x), std::abs(MAX_VIRTUAL().y)+ std::abs(MIN_VIRTUAL().y));
	Canvas_Matrix_().fill(EMPTY());

	Coordinate cell;

	for (int i = 0; i < points_to_draw().size(); ++i)
	{
		cell.j = std::abs(points_to_draw()[i].x);

		cell.i = std::abs(points_to_draw()[i].y);

		Canvas_Matrix_().set_at(cell, points_to_draw()[i].symbol);
	}
}


void Direct_draw::print() const
{
	Canvas_Matrix_().print();
}

void Direct_draw::render_matrix()
{
	if (points_to_draw().size() == 0)
		return;

	if (!isMatrixCalculated() )
	{
		Canvas_Matrix_().clear();
		calculate_matrix();
		isMatrixCalculated(true);
	}

	return;
}
