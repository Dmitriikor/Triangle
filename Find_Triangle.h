#ifndef Find_Triangle_H__

#define  Find_Triangle_H__
#pragma once

#include "Canvas.h"
#include "Point.h"
#include "Triangle.h"
#include "utilities.h"
#include "Ray.h"
#include "Matrix.h"

Triangle_hi Find_Triangle(const Ray<Dot>& point_arr);
///Triangle_hi Find_Triangle_with_the_thread(Ray<Dot>& point_arr, size_t n_points);
#endif //!  Find_Triangle_H__