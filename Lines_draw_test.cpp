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

struct Point {
    double x;
    double y;

    void Point_print(const Point& a) {
        std::cout << x << " " << y << "\n";
    }
};

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

    int con_x = (ORIGIN.x + (int)round(point.x * coefficient)) * shift_w;
    int con_y = ORIGIN.y - (int)round(point.y * coefficient);
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
    double b = A.y - k * A.x;

    double step = step_is(coefficient);  // 1.0 / coefficient;

    double rounded_min = round(min, step);
    double rounded_max = round(max, step);

    unsigned N = (rounded_max - rounded_min) / step + 1;

    if (N < abs(B.y) + abs(A.y)) {

        bool start = false;
        for (int i = 0; i < N; ++i) {
            Point point;
            point.x = rounded_min + i * step;
            point.y = k * point.x + b;
            // Point old;
            // Point prt;
            // if (start){
            //     prt.x = old.x;
            //     prt.y = int(old.y);
            //     print_vert(old, prt);
            //     prt.x= prt.x+1;
            //     prt.y = old.y;
            //     print_vert(prt, point);
            // }
            // old.x = point.x;
            // old.y = point.y;
            // start = true;
            printPoint(point, ORIGIN, coefficient);
        }
        return;
    }

    for (int i = 0; i < N; ++i) {
        Point point;
        point.x = rounded_min + i * step;
        point.y = k * point.x + b;

        printPoint(point, ORIGIN, coefficient);
    }
}

int main() {
    Point a;
    a.x = 1;
    a.y = 1;
    Point b;
    while (a.x != 0 && a.y != 0 && b.x != 0 && b.y != 0) {
        /*Point a;*/
        std::cin >> a.x >> a.y;
        /*Point b;*/
        std::cin >> b.x >> b.y;

        system("clear");

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

        draw_line_4(a, b, ORIGIN, coefficient);


        setCursorPosition(0, ORIGIN.y * 2 + 2);
    }

    return 0;
}