
#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>


#include "Ray_3_test.h"
#include "Point_test.h"
#include "Matrix_test.h"
#include "Is_equal_test.h"


void initialize_min_max_points(const Ray_3_& points, bool run_copy_arr = false);
void initialize_width();
void print_corner();
void print_arr();
void hello_try_set_min_max_by(Point pt, bool save_point = true);

//void draw_points(Ray_3_ arr = ptr_arr);

void draw_points(bool is_need_to_draw_line = false);
void hello_draw_line_1(const Point& A, const Point& B);

#endif //!  HELLO_H__