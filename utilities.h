﻿#pragma once

#ifndef UTILITIES_H__

#define  UTILITIES_H__

#include <iostream>
#include <random>
#include <cmath>


//#include "Axys.h"

//#include "Corner.h"

namespace utilities
{
	 double round_by_step(double x, double step);

	 int random_INT(int start, int end);

	 void fast_print();
	 void fastscan(std::istream& cin);
	/// Dot* start_dialoge(std::streamsize MAX_STREAMSIZE, size_t n_points, std::string path_in = "points.txt", std::string path_out = "out.txt");

	 bool isEqual(long double a, long double b, long double eps = 1e-5);

	 int get_distance_between(int min_coord, int max_coord);

};


#endif //!  UTILITIES_H__
