#ifndef UTILITIES_H__

#define  UTILITIES_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include "Ray_3_test.h"


namespace utilities
{
	 double round_by_step(double x, double step);


	 Point* start_dialoge(std::streamsize MAX_STREAMSIZE, size_t n_points, std::string path_in = "points.txt", std::string path_out = "out2.txt");

};


#endif //!  UTILITIES_H__
