
#ifndef LINES_DRAW_TEST_H__

#define  LINES_DRAW_TEST_H__

#include <cmath>
#include <iostream>
#include "Point_test.h"
#include "Is_equal_test.h"
/*
size_t shift();
size_t shift_w();
void shift_w(size_t shiftset);
size_t shift_h();
size_t indent();

unsigned int coefficient();
*/
int y_axis_thickness();
int x_axis_thickness();

double get_step_by(unsigned coefficient);

void setCursorPosition(int XPos, int YPos);

void SetCursorPosition(int XPos, int YPos);

int set_pos_x(int index);

void printPoint(const Point& point, const Point& ORIGIN, unsigned coefficient);

double round(double x, double step);

void draw_line_4(const Point& A, const Point& B, const Point& ORIGIN, unsigned coefficient);

//void indent_print();


#endif //!  LINES_DRAW_TEST_H__