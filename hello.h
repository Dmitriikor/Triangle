
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

void draw_points_(bool is_need_to_draw_line = false);
void draw_points();
void draw_line();

void erase_point(Point err);
//void erase(bool is_need_to_erase_line);
//void erase_lines();
//void erase_points();
void delite_line(const Point& A, const Point& B);
void delite_point(const Point& dl);

void canvas_clear();
void canvas_print_zero();

Ray_3_ calculate_line_round(const Point& A, const Point& B,  char symbol = '+');
Ray_3_ calculate_line_swap(const Point& A, const Point& B,  char symbol = '+');
void draw_line_1_(const Point& A, const Point& B, bool is_round = true,  char symbol = '+');






#endif //!  HELLO_H__