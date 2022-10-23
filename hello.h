
#ifndef HELLO_H__

#define  HELLO_H__

#include <iostream>


#include "Ray_3_test.h"
#include "Point_test.h"
#include "Matrix_test.h"
#include "Is_equal_test.h"

#include "utilities.h"
void go_debug(bool is_debug = false);



void initialize_min_max_points(const Ray_3_& points);
void initialize_width();
void create_corner();
void print_arr();
void hello_try_set_min_max_by(Point pt, bool save_point = true);

//void draw_points(Ray_3_ arr = ptr_arr);

void draw_points_(bool is_need_to_draw_line = false, char symbol = '*');
void draw_points();
void draw_line();

void erase(bool is_need_to_erase_line);
void erase_point(Point err);
void erase_lines();
void erase_points();
void erase_line(const Point& A, const Point& B);

void canvas_clear();
void canvas_print_zero();

void hello_draw_line_1(const Point& A, const Point& B);







#endif //!  HELLO_H__