
#ifndef LINES_DRAW_TEST_H__

#define  LINES_DRAW_TEST_H__

#include <cmath>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <exception>
#include <string>
#include <Windows.h>
#include <utility>
#include <limits> 
#include <string_view>
#include <sstream>


#include "Ray_3_test.h"
#include "Matrix_test.h"
#include "Point_test.h"
#include "Is_equal_test.h"
#include "Triangle_test.h"
#include "Ray_test.h"

void draw_line_4(const Point& A, const Point& B, const Point& ORIGIN, unsigned coefficient);



    // triangle, coefficient, bool draw_triangle=false, bool draw_round=true
void Axys(Triangle& triangle, unsigned int coefficient, bool draw_triangle=false, bool draw_round=true);

// triangle, coefficient, bool draw_triangle=false, bool draw_round=true
void Corner(Triangle& triangle, unsigned int coefficient, bool draw_triangle = false, bool draw_round = true);

#endif //!  LINES_DRAW_TEST_H__