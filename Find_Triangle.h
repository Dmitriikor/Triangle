#pragma once

#include "Canvas.h"
#include "Point.h"
#include "Triangle.h"
#include "utilities.h"
#include "Ray.h"
#include "Matrix.h"

Triangle_hi Find_Triangle(Ray<Dot>& point_arr, size_t n_points);