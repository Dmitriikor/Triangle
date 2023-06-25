#include "Direct_draw.h"


void Direct_draw::calculate_matrix()
{
	/*double count_value_x = std::abs(MAX_VIRTUAL().x) + std::abs(MIN_VIRTUAL().x) + 1;
	double count_value_y = std::abs(MAX_VIRTUAL().y) + std::abs(MIN_VIRTUAL().y) + 1;*/

	double count_value_x = std::abs(MAX_VIRTUAL().x - MIN_VIRTUAL().x) + 1;
	double count_value_y = std::abs(MAX_VIRTUAL().y - MIN_VIRTUAL().y) + 1;

	Canvas_Matrix().resize(count_value_y, count_value_x);
	Canvas_Matrix().fill(EMPTY());

	for (int i = 0; i < points_to_draw().size(); ++i)
	{
		Coordinate cell;

		//сдвиг оси Y таким образом, чтобы координата Y самой нижней точки стала равна 0:
		cell.i = (count_value_y - 1) - (points_to_draw()[i].y - MIN_VIRTUAL().y);

		//сдвиг оси X таким образом, чтобы координата X самой левой точки стала равна 0:
		cell.j = points_to_draw()[i].x - MIN_VIRTUAL().x;

		Canvas_Matrix().set_at(cell, points_to_draw()[i].symbol);
	}

	//Canvas_Matrix().resize(count_value_y, count_value_x);
	//Canvas_Matrix().fill(EMPTY());

	//for (int i = 0; i < points_to_draw().size(); ++i)
	//{
	//	Coordinate cell;

	//	//сдвиг оси Y таким образом, чтобы координата Y самой нижней точки стала равна 0:
	//	cell.i = points_to_draw()[i].y - MIN_VIRTUAL().y;

	//	//сдвиг оси X таким образом, чтобы координата X самой левой точки стала равна 0:
	//	cell.j = points_to_draw()[i].x - MIN_VIRTUAL().x;

	//	Canvas_Matrix().set_at(cell, points_to_draw()[i].symbol);
	//}
}


void Direct_draw::print() const
{
	Canvas_Matrix().print();
}

void Direct_draw::render_matrix()
{
	if (points_to_draw().size() == 0)
		return;

	if (!isMatrixCalculated())
	{
		Canvas_Matrix().clear();
		calculate_matrix();
		isMatrixCalculated(true);
	}

	return;
}
