#include "Lines_draw_test.h"


//#include <stdio.h>
//#include <time.h>
//
//#include <algorithm>
//#include <cmath>
//#include <fstream>
//
//#include <iostream>
//#include <string>
//#include <vector>


#include <iomanip>
// //#include <conio.h>
// //#include <windows.h>
// //#include <wingdi.h>
//
// void goto_s(Point a) {
// 	Point b;
// 	b.X = round(a.x);
// 	b.Y = round(a.y);
// 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
// }

// void setCursorPosition(int XPos, int YPos) {
// 	Point b;
// 	b.X = XPos;
// 	b.Y = YPos;
// 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
// }

//struct Point {
//    double x;
//    double y;
//
//    void Point_print(const Point& a) {
//        std::cout << x << " " << y << "\n";
//    }
//};

/////////////////////////
Point ORIGIN;  // origin relative to the console  / Г­Г Г·. ГЄГ®Г®Г°Г¤ГЁГ­Г ГІ Г®ГІГ­Г®Г±ГЁГІГҐГ«ГјГ­Г® ГЄГ®Г­Г±Г®Г«ГЁ
/////////////////////////
unsigned int coefficient = 1;
/////////////////////////

double step_is(unsigned coefficient) {
    double step = 1.0 / coefficient;
    return step;
}
/////////////////////////
int shift_w = 0;

/////////////////////////

void setCursorPosition(int XPos, int YPos) {
    printf("\033[%d;%dH", YPos + 1, XPos + 1);
}

int set_pos_x(int index) {
    return (ORIGIN.x + index) * shift_w;
}

void printPoint(const Point& point, const Point& ORIGIN, unsigned coefficient) {
    /*if (point.x == 18 && point.y == 25) {
            int k = point.x * 18;
    }*/

    int _con_x = (ORIGIN.x + (int)round(point.x * coefficient)) * shift_w;
    int _con_y = ORIGIN.y - (int)round(point.y * coefficient);
    // 
    int con_x_ = point.x * coefficient;
    int con_y_ = point.y * coefficient;

    int con_x__ = (int)round(con_x_);
    int con_y__ = (int)round(con_y_);

    int con_x = (ORIGIN.x + con_x__) * shift_w;
    int con_y = ORIGIN.y - con_y__;

    /* if (con_x >= 10) {
                 setCursorPosition(con_x, con_y);
                 std::cout << "  " << std::endl;
                 con_x += 1;
         }*/
    setCursorPosition(con_x, con_y);
    std::cout << "o" << std::endl;
}

bool isEqual(double a, double b) {
    const double eps = 1e-5;
    if (abs(a - b) <= eps)
        return true;
    return false;
}

double round(double x, double step) {
    double modulo = fmod(x, step);
    if (modulo < step / 2)
        return x - modulo;
    return x - modulo + step;
}

void print_vert(Point& A, Point& B) {
    double start = A.y;
    double end = B.y;
    if (A.y < B.y) {
        start = B.y;
        end = A.y;
    }
    double step = step_is(coefficient);  // 1.0 / coefficient;
    Point point;
    point.x = A.x;
    for (double y = start; y >= end; y -= step) {
        point.y = y;
        printPoint(point, ORIGIN, coefficient);
    }
    return;

}

void draw_line_4(const Point& A, const Point& B, const Point& ORIGIN, unsigned coefficient) {

    Point coords;

    double min = A.x;
    double max = B.x;
    if (A.x > B.x) {
        min = B.x;
        max = A.x;
    }

    //  cd /root/Vs_Code/Matrix/
    //  ./Line4

    if (isEqual(min, max)) {
        double start = A.y;
        double end = B.y;
        if (A.y < B.y) {
            start = B.y;
            end = A.y;
        }
        double step = step_is(coefficient);  // 1.0 / coefficient;
        Point point;
        point.x = A.x;
        for (double y = start; y >= end; y -= step) {
            point.y = y;
            printPoint(point, ORIGIN, coefficient);
        }
        return;
    }

    double k = (B.y - A.y) / (B.x - A.x);
    double b_ = k * A.x;
    double b = A.y - b_;
    
    double step = step_is(coefficient);  // 1.0 / coefficient;

    double rounded_min = round(min, step);
    double rounded_max = round(max, step);

    unsigned N = (rounded_max - rounded_min) / step + 1;

    
    for (int i = 0; i < N; ++i) {
        Point point;
        point.x = rounded_min + i * step;
        point.y = k * point.x + b;
        

        printPoint(point, ORIGIN, coefficient);
    }
}





    struct draw_line_2
    {
        static void goto_coords_(Point a) {
            
            COORD b;
            //b.X = a.x;
            b.X = a.x;
            b.Y = a.y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
        }

       static void draw_line_no_round(const Point& A, const Point& B, const Point& ORIGIN) {

           if (A.x == B.x && A.y == B.y)
           {
               throw std::exception("Lines_draw_test.cpp draw_line_no_round Point A == Point B (NO LINE)");
               return;
           }

            int x1, y1, x2, y2;
            x1 = A.x;
            y1 = A.y;
            x2 = B.x;
            y2 = B.y;

            bool steep = false;
            if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
                std::swap(x1, y1);
                std::swap(x2, y2);
                steep = true;
            }
            if (x1 > x2) {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }

            for (int x = x1; x <= x2; x++) {
                float k = (x - x1) / (float)(x2 - x1);
                int y = y1 * (1. - k) + y2 * k;

                Point coords;


                if (steep) {
                    coords.x = (ORIGIN.x + y) * shift_w;
                    coords.y = ORIGIN.y - x;

                    goto_coords_(coords);	/////  /////
                    std::cout << "+";		/////  /////

                }
                else {
                    coords.x = (ORIGIN.x + x) * shift_w;
                    coords.y = ORIGIN.y - y;

                    goto_coords_(coords);	/////  /////
                    
                    std::cout << "+";		/////  /////
                }
            }
        }



    };




    // triangle, coefficient, bool draw_triangle=false, bool draw_round=true
void axys(Triangle& triangle, unsigned int coefficient, bool draw_triangle, bool draw_round) {
    if (coefficient == 0) 
    {
        throw std::exception("Lines_draw_test.cpp axys coefficient == 0");
        return;
    }

        Point b;

        Point loc_min = triangle.get_A();
        Point loc_mid = triangle.get_B();
        Point loc_max = triangle.get_C();

        if (abs(loc_min.x) >= abs(loc_mid.x) && abs(loc_min.x) >= abs(loc_max.x))
            b.x = loc_min.x;
        else if (abs(loc_mid.x) >= abs(loc_min.x) && abs(loc_mid.x) >= abs(loc_max.x))
            b.x = loc_mid.x;
        else if (abs(loc_max.x) >= abs(loc_min.x) && abs(loc_max.x) >= abs(loc_mid.x))
            b.x = loc_max.x;


        if (abs(loc_min.y) >= abs(loc_mid.y) && abs(loc_min.y) >= abs(loc_max.y))
            b.y = loc_min.y;
        else if (abs(loc_mid.y) >= abs(loc_min.y) && abs(loc_mid.y) >= abs(loc_max.y))
            b.y = loc_mid.y;
        else if (abs(loc_max.y) >= abs(loc_min.y) && abs(loc_max.y) >= abs(loc_mid.y))
            b.y = loc_max.y;

        Point a;
        a.x = 1;
        a.y = 1;


        /*Point a;*/
        //std::cin >> a.x >> a.y;
        /*Point b;*/
        //std::cin >> b.x >> b.y;

        system("cls");

        double round_a_x = round(a.x, step_is(coefficient));
        double round_a_y = round(a.y, step_is(coefficient));
        double round_b_x = round(b.x, step_is(coefficient));
        double round_b_y = round(b.y, step_is(coefficient));

        ORIGIN.x = fabs(b.x) > fabs(a.x) ? fabs(b.x) : fabs(a.x);  // abs > fabs
        ORIGIN.y = fabs(b.y) > fabs(a.y) ? fabs(b.y) : fabs(a.y);  // abs > fabs

        ORIGIN.x = round(ORIGIN.x, step_is(coefficient)) / step_is(coefficient);
        ORIGIN.y = round(ORIGIN.y, step_is(coefficient)) / step_is(coefficient);

        if (coefficient <= 2)
            shift_w = 4;
        else
            shift_w = 6;
        std::cout << std::fixed;
        if (coefficient >= 3)
            std::cout << std::setprecision(2);
        else
            std::cout << std::setprecision(0);


        for (int j = -(ORIGIN.y); j < ORIGIN.y + 1; j++) {
            setCursorPosition(set_pos_x(0), ORIGIN.y + j);
            std::cout << fabs(j * step_is(coefficient)) << "\n";
        }
        for (int i = -(ORIGIN.x); i < ORIGIN.x + 1; i++)  // axis X
        {
            setCursorPosition(set_pos_x(i), ORIGIN.y);
            std::cout << std::setw(shift_w) << std::left << fabs(i * step_is(coefficient)) << "\n";
        }
        std::cout << "\n";

        //draw_line_4(a, b, ORIGIN, coefficient);


        setCursorPosition(0, ORIGIN.y * 2 + 2);

        if (draw_triangle && draw_round) 
        {
			draw_line_4(triangle.get_A(), triangle.get_B(), ORIGIN, coefficient);
			draw_line_4(triangle.get_B(), triangle.get_C(), ORIGIN, coefficient);
			draw_line_4(triangle.get_C(), triangle.get_A(), ORIGIN, coefficient);
        }
        if (draw_triangle && !draw_round) 
        {
            Point A_ = triangle.get_A();
            Point B_ = triangle.get_B();

            draw_line_2::draw_line_no_round(triangle.get_A(), triangle.get_B(), ORIGIN);
            draw_line_2::draw_line_no_round(triangle.get_B(), triangle.get_C(), ORIGIN);
            draw_line_2::draw_line_no_round(triangle.get_C(), triangle.get_A(), ORIGIN);
        }

        setCursorPosition(0, ORIGIN.y * 2 + 2);

    }
