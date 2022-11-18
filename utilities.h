#ifndef UTILITIES_H__

#define  UTILITIES_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <random>
#include "Ray_3_test.h"

using UTILITIES_H_MLTY_TYPE = Point;

namespace utilities
{
	 double round_by_step(double x, double step);

	 int random_INT(int start, int end);

	 Point* start_dialoge(std::streamsize MAX_STREAMSIZE, size_t n_points, std::string path_in = "points.txt", std::string path_out = "out.txt");

};


#endif //!  UTILITIES_H__
