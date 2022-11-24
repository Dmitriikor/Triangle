#include "utilities.h"


double utilities::round_by_step(double x, double step) {
	double modulo = fmod(x, step);
	if (modulo < step / 2)
		return x - modulo;
	return x - modulo + step;
}


int utilities::random_INT(int start, int end)
{
	std::random_device rnd;
	std::uniform_int_distribution<int> dist(start, end);

	return dist(rnd);
}

 

//Dot* utilities::start_dialoge(std::streamsize MAX_STREAMSIZE, size_t n_points, std::string path_in, std::string path_out)
//{
	// { start dialoge
	 

	//clear_cls(OS);

	//  } start dialoge

