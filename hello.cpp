#include "hello.h"

Point _MAX_;
Point _MIN_;

void hello_min_max_points(Ray_3_& points) {
	size_t length = points.size();

	_MAX_ = points[0];
	_MIN_ = points[0];

	for (size_t i = 0; i < length; i++)
	{

		if (_MAX_.x < points[i].x)
			_MAX_.x = points[i].x;


		if (_MAX_.y < points[i].y)
			_MAX_.y = points[i].y;

		if (_MIN_.x > points[i].x)
			_MIN_.x = points[i].x;

		if (_MIN_.y > points[i].y)
			_MIN_.y = points[i].y;

	}

	std::cout << std::endl << _MAX_.x << " : " << _MAX_.y << std::endl;
	std::cout << std::endl << _MIN_.x << " : " << _MIN_.y << std::endl;

}

int shift_w_ = -1;
int shift_h_ = -1;

void hello_char_w_cntr() {
	size_t answ_w = 1;
	size_t answ_h = 1;
	if (_MIN_.y < 0 || _MIN_.x < 0)
	{
		answ_w++;
		answ_h++;
	}
	size_t x = abs(_MAX_.x) > abs(_MIN_.x) ? abs(_MAX_.x) : abs(_MIN_.x);
	for (; x >= 10; answ_w++) {
		x = x / 10;
	}
	size_t y = abs(_MAX_.y) > abs(_MIN_.y) ? abs(_MAX_.y) : abs(_MIN_.y);
	for (; y >= 10; answ_h++) {
		y = y / 10;
	}

	shift_w_ = answ_w;
	shift_h_ = answ_h;

	std::cout << std::endl << shift_w_ << std::endl;
	std::cout << std::endl << shift_h_ << std::endl;

}

	size_t N;
	size_t M;
	Matrix corner_print;

void hello_corner() {


	int max_y = _MAX_.y;
	int min_y = _MIN_.y;

	int max_x = _MAX_.x;
	int min_x = _MIN_.x;

	if (min_y == max_y)
		N = abs(max_y) + 1;
	else
		if (min_y >= 0 && max_y >= 0)
			N = abs(max_y) + 1;
		else if (min_y <= 0 && max_y <= 0)
			N = abs(min_y) + 1;
		else
			N = abs(max_y) + abs(min_y) + 1;

	if (max_x == min_x)
		M = abs(max_x) + 1;
	else if (max_x >= 0 && min_x >= 0)
		M = abs(max_x) + 1;
	else if (max_x <= 0 && min_x <= 0)
		M = abs(min_x) + 1;
	else
		M = abs(max_x) + abs(min_x) + 1;

	int indent = 1;
	int axis_x_str = 1;

	N = N + axis_x_str;
	M = M * (shift_w_ + indent) + shift_h_;

	corner_print.create_matrix(N, M);

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			corner_print[i][j] = ' ';
		}
	}

	// {print y axis
	int start_y = max_y > 0 ? max_y : 0;

	for (size_t i = 0; i < N - axis_x_str; i++)
	{
		int  temp_inpt = start_y - i;

		for (size_t j = shift_h_; j > 0; --j)
		{
			int inpt = temp_inpt % 10;
			temp_inpt = temp_inpt / 10;
			if (inpt > 0)
				corner_print[i][1] = ' ';

			if (inpt < 0) {
				corner_print[i][1] = '-';
			}
			if (j != 1)
				corner_print[i][j] = '0' + abs(inpt);

		}

	}
	// }end print y axis

	//{find actual console point of start coodrs
	Point ZERO;
	ZERO.y = start_y;// +shift_w_; //!x_axis_thickness
	//}find actual console point of start coodrs

	// {print x axys
	int start_x = min_x > 0 ? 0 : min_x;

	for (size_t i = 0; i <= abs(max_x) + abs(min_x); i++)
	{
		int temp_inpt = min_x + i; // ?
		bool neg = false;
		bool sml = false;

		for (int j = shift_w_; j > 0; --j)
		{
			if (j == shift_w_)
			{
				corner_print[N - axis_x_str][shift_h_ + (i * shift_w_) + j] = '|';
			}
			else
			{
				int inpt = temp_inpt % 10;

				if (inpt < 0)
					neg = true;

				if (temp_inpt <= 9 && !neg && j == shift_w_ - 1)
					sml = true;

				temp_inpt = temp_inpt / 10;
				corner_print[N - axis_x_str][shift_h_ + (i * shift_w_) + j] = '0' + abs(inpt);

				if (neg)
					corner_print[N - axis_x_str][shift_h_ + (i * shift_w_) + 1] = '-';
				if (sml)
					corner_print[N - axis_x_str][shift_h_ + (i * shift_w_) + 1] = ' ';
			}
		}
	}
	// }end print x axis

	//{find actual console point of start coodrs
	ZERO.x = ((abs(start_x * shift_w_)) + shift_h_ + (shift_w_ - 1)); //!!!!!SHIFT
	//}find actual console point of start coodrs

	std::cout << "\n" << "\t" << "ZERO.x = " << ZERO.x << " : ZERO.y = " << ZERO.y << "\n";
	corner_print[ZERO.y][ZERO.x] = 'o';

	int stop = 1;

	//}end of work wich axis 
}

void hello_print_arr() {
	std::cout << "\n";
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			std::cout << corner_print[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void hello_try_set_min_max_by(Point pt)
{
	if (_MAX_.x < pt.x)
		_MAX_.x = pt.x;

	if (_MAX_.y < pt.y)
		_MAX_.y = pt.y;

	if (_MIN_.x > pt.x)
		_MIN_.x = pt.x;

	if (_MIN_.y > pt.y)
		_MIN_.y = pt.y;
}

