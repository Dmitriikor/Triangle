//#include "Lines_draw_test.h"
//#include <charconv>
//
//
////#include <stdio.h>
////#include <time.h>
////
////#include <algorithm>
////#include <cmath>
////#include <fstream>
////
////#include <iostream>
////#include <string>
////#include <vector>
//
//// //#include <conio.h>
//// //#include <windows.h>
//// //#include <wingdi.h>
////
//// void goto_s(Point a) {
//// 	Point b;
//// 	b.X = round(a.x);
//// 	b.Y = round(a.y);
//// 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
//// }
//
//// void setCursorPosition(int XPos, int YPos) {
//// 	Point b;
//// 	b.X = XPos;
//// 	b.Y = YPos;
//// 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
//// }
//
////struct Point {
////    double x;
////    double y;
////
////    void Point_print(const Point& a) {
////        std::cout << x << " " << y << "\n";
////    }
////};
//
///////////////////////////
//Point ORIGIN;  // origin relative to the console  / Г­Г Г·. ГЄГ®Г®Г°Г¤ГЁГ­Г ГІ Г®ГІГ­Г®Г±ГЁГІГҐГ«ГјГ­Г® ГЄГ®Г­Г±Г®Г«ГЁ
///////////////////////////
//unsigned int coefficient = 1;
///////////////////////////
//
//struct virtual_MAX
//{
//    int x = INT_MIN;
//    int y = INT_MIN;
//
//}virtual_MAX;
//
//struct virtual_MIN
//{
//     int x = INT_MAX;
//     int y = INT_MAX;
//}virtual_MIN;
//
//
//double step_is(unsigned coefficient) {
//    double step = 1.0 / coefficient;
//    return step;
//}
///////////////////////////
//int shift_w = -1;
//int shift_h = -1;
///////////////////////////
//
//void goto_coords(Point a) {
//
//	COORD b;
//	b.X = a.x;
//	b.Y = a.y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
//}
//
//void setCursorPosition(int XPos, int YPos) {
//    printf("\033[%d;%dH", YPos + 1, XPos + 1);
//}
//
//int set_pos_x(int index) {
//    return (ORIGIN.x + index) * shift_w;
//}
//
//void printPoint(const Point& point, const Point& ORIGIN, unsigned coefficient) {
//    /*if (point.x == 18 && point.y == 25) {
//            int k = point.x * 18;
//    }*/
//
//    int _con_x = (ORIGIN.x + (int)round(point.x * coefficient)) * shift_w;
//    int _con_y = ORIGIN.y - (int)round(point.y * coefficient);
//    // 
//    int con_x_ = point.x * coefficient;
//    int con_y_ = point.y * coefficient;
//
//    int con_x__ = (int)round(con_x_);
//    int con_y__ = (int)round(con_y_);
//
//    int con_x = (ORIGIN.x + con_x__) * shift_w;
//    int con_y = ORIGIN.y - con_y__;
//
//    /* if (con_x >= 10) {
//                 setCursorPosition(con_x, con_y);
//                 std::cout << "  " << std::endl;
//                 con_x += 1;
//         }*/
//    setCursorPosition(con_x, con_y);
//    std::cout << "o" << std::endl;
//}
//
//bool isEqual(double a, double b) {
//    const double eps = 1e-5;
//    if (abs(a - b) <= eps)
//        return true;
//    return false;
//}
//
//double round(double x, double step) {
//    double modulo = fmod(x, step);
//    if (modulo < step / 2)
//        return x - modulo;
//    return x - modulo + step;
//}
//
//void print_vert(Point& A, Point& B) {
//    double start = A.y;
//    double end = B.y;
//    if (A.y < B.y) {
//        start = B.y;
//        end = A.y;
//    }
//    double step = step_is(coefficient);  // 1.0 / coefficient;
//    Point point;
//    point.x = A.x;
//    for (double y = start; y >= end; y -= step) {
//        point.y = y;
//        printPoint(point, ORIGIN, coefficient);
//    }
//    return;
//
//}
//
//void draw_line_4(const Point& A, const Point& B, const Point& ORIGIN, unsigned coefficient) {
//
//    Point coords;
//
//    double min = A.x;
//    double max = B.x;
//    if (A.x > B.x) {
//        min = B.x;
//        max = A.x;
//    }
//
//    //  cd /root/Vs_Code/Matrix/
//    //  ./Line4
//
//    if (isEqual(min, max)) {
//        double start = A.y;
//        double end = B.y;
//        if (A.y < B.y) {
//            start = B.y;
//            end = A.y;
//        }
//        double step = step_is(coefficient);  // 1.0 / coefficient;
//        Point point;
//        point.x = A.x;
//        for (double y = start; y >= end; y -= step) {
//            point.y = y;
//            printPoint(point, ORIGIN, coefficient);
//        }
//        return;
//    }
//
//    double k = (B.y - A.y) / (B.x - A.x);
//    double b_ = k * A.x;
//    double b = A.y - b_;
//    
//    double step = step_is(coefficient);  // 1.0 / coefficient;
//
//    double rounded_min = round(min, step);
//    double rounded_max = round(max, step);
//
//    unsigned N = (rounded_max - rounded_min) / step + 1;
//
//    
//    for (int i = 0; i < N; ++i) {
//        Point point;
//        point.x = rounded_min + i * step;
//        point.y = k * point.x + b;
//        
//
//        printPoint(point, ORIGIN, coefficient);
//    }
//}
//
//
//
//
//
//    struct draw_line_2
//    {
//        static void goto_coords_(Point a) {
//            
//            COORD b;
//            //b.X = a.x;
//            b.X = a.x;
//            b.Y = a.y;
//            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
//        }
//
//       static void draw_line_no_round(const Point& A, const Point& B, const Point& ORIGIN) {
//
//           if (A.x == B.x && A.y == B.y)
//           {
//               throw std::exception("Lines_draw_test.cpp draw_line_no_round Point A == Point B (NO LINE)");
//               return;
//           }
//
//            int x1, y1, x2, y2;
//            x1 = A.x;
//            y1 = A.y;
//            x2 = B.x;
//            y2 = B.y;
//
//            bool steep = false;
//            if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
//                std::swap(x1, y1);
//                std::swap(x2, y2);
//                steep = true;
//            }
//            if (x1 > x2) {
//                std::swap(x1, x2);
//                std::swap(y1, y2);
//            }
//
//            for (int x = x1; x <= x2; x++) {
//                float k = (x - x1) / (float)(x2 - x1);
//                int y = y1 * (1. - k) + y2 * k;
//
//                Point coords;
//
//
//                if (steep) {
//                    coords.x = (ORIGIN.x + y) * shift_w;
//                    coords.y = ORIGIN.y - x;
//
//                    goto_coords_(coords);	/////  /////
//                    std::cout << "+";		/////  /////
//
//                }
//                else {
//                    coords.x = (ORIGIN.x + x) * shift_w;
//                    coords.y = ORIGIN.y - y;
//
//                    goto_coords_(coords);	/////  /////
//                    
//                    std::cout << "+";		/////  /////
//                }
//            }
//        }
//
//    };
//
//
//
//
//    // triangle, coefficient, bool draw_triangle=false, bool draw_round=true
//void Axys(Triangle& triangle, unsigned int coefficient, bool draw_triangle, bool draw_round) {
//    if (coefficient == 0) 
//    {
//        throw std::exception("Lines_draw_test.cpp Axys coefficient == 0");
//        return;
//    }
//
//        Point b;
//
//        Point loc_min = triangle.get_A();
//        Point loc_mid = triangle.get_B();
//        Point loc_max = triangle.get_C();
//
//        if (abs(loc_min.x) >= abs(loc_mid.x) && abs(loc_min.x) >= abs(loc_max.x))
//            b.x = loc_min.x;
//        else if (abs(loc_mid.x) >= abs(loc_min.x) && abs(loc_mid.x) >= abs(loc_max.x))
//            b.x = loc_mid.x;
//        else if (abs(loc_max.x) >= abs(loc_min.x) && abs(loc_max.x) >= abs(loc_mid.x))
//            b.x = loc_max.x;
//
//
//        if (abs(loc_min.y) >= abs(loc_mid.y) && abs(loc_min.y) >= abs(loc_max.y))
//            b.y = loc_min.y;
//        else if (abs(loc_mid.y) >= abs(loc_min.y) && abs(loc_mid.y) >= abs(loc_max.y))
//            b.y = loc_mid.y;
//        else if (abs(loc_max.y) >= abs(loc_min.y) && abs(loc_max.y) >= abs(loc_mid.y))
//            b.y = loc_max.y;
//
//        Point a;
//        a.x = 1;
//        a.y = 1;
//
//
//        /*Point a;*/
//        //std::cin >> a.x >> a.y;
//        /*Point b;*/
//        //std::cin >> b.x >> b.y;
//
//        //system("cls");
//
//        double round_a_x = round(a.x, step_is(coefficient));
//        double round_a_y = round(a.y, step_is(coefficient));
//        double round_b_x = round(b.x, step_is(coefficient));
//        double round_b_y = round(b.y, step_is(coefficient));
//
//        ORIGIN.x = fabs(b.x) > fabs(a.x) ? fabs(b.x) : fabs(a.x);  // abs > fabs
//        ORIGIN.y = fabs(b.y) > fabs(a.y) ? fabs(b.y) : fabs(a.y);  // abs > fabs
//
//        ORIGIN.x = round(ORIGIN.x, step_is(coefficient)) / step_is(coefficient);
//        ORIGIN.y = round(ORIGIN.y, step_is(coefficient)) / step_is(coefficient);
//
//        if (coefficient <= 2)
//            shift_w = 4;
//        else
//            shift_w = 6;
//        std::cout << std::fixed;
//        if (coefficient >= 3)
//            std::cout << std::setprecision(2);
//        else
//            std::cout << std::setprecision(0);
//
//
//        for (int j = -(ORIGIN.y); j < ORIGIN.y + 1; j++) {
//            setCursorPosition(set_pos_x(0), ORIGIN.y + j);
//            std::cout << fabs(j * step_is(coefficient)) << "\n";
//        }
//        for (int i = -(ORIGIN.x); i < ORIGIN.x + 1; i++)  // axis X
//        {
//            setCursorPosition(set_pos_x(i), ORIGIN.y);
//            std::cout << std::setw(shift_w) << std::left << fabs(i * step_is(coefficient)) << "\n";
//        }
//        std::cout << "\n";
//
//        //draw_line_4(a, b, ORIGIN, coefficient);
//
//
//        setCursorPosition(0, ORIGIN.y * 2 + 2);
//
//        if (draw_triangle && draw_round) 
//        {
//			draw_line_4(triangle.get_A(), triangle.get_B(), ORIGIN, coefficient);
//			draw_line_4(triangle.get_B(), triangle.get_C(), ORIGIN, coefficient);
//			draw_line_4(triangle.get_C(), triangle.get_A(), ORIGIN, coefficient);
//        }
//        if (draw_triangle && !draw_round) 
//        {
//            Point A_ = triangle.get_A();
//            Point B_ = triangle.get_B();
//
//            draw_line_2::draw_line_no_round(triangle.get_A(), triangle.get_B(), ORIGIN);
//            draw_line_2::draw_line_no_round(triangle.get_B(), triangle.get_C(), ORIGIN);
//            draw_line_2::draw_line_no_round(triangle.get_C(), triangle.get_A(), ORIGIN);
//        }
//        setCursorPosition(0, ORIGIN.y * 2 + 2);
//    }
//
//
//
//
//void set_min_max_of_points_rey(Ray_3_ &points) 
//{
//    size_t length = points.size();
//
//    for (size_t i = 0; i < length; i++)
//    {
//        
//        if (virtual_MAX.x < points[i].x)
//            virtual_MAX.x = points[i].x;
//
//
//        if (virtual_MAX.y < points[i].y)
//            virtual_MAX.y = points[i].y;
//
//        if (virtual_MIN.x > points[i].x)
//            virtual_MIN.x = points[i].x;
//
//        if (virtual_MIN.y > points[i].y)
//            virtual_MIN.y = points[i].y;
//
//    }
//}
//
//void update_min_max_by(Point pt) 
//{
//    if (virtual_MAX.x < pt.x)
//        virtual_MAX.x = pt.x;
//
//    if (virtual_MAX.y < pt.y)
//        virtual_MAX.y = pt.y;
//
//    if (virtual_MIN.x > pt.x)
//        virtual_MIN.x = pt.x;
//
//    if (virtual_MIN.y > pt.y)
//        virtual_MIN.y = pt.y;
//    
//}
//
//void char_shift_w_h_cntr() {
//    size_t answ_w = 1;
//    size_t answ_h = 1;
//    if (virtual_MIN.y < 0 || virtual_MIN.x < 0) 
//    {
//        answ_w++; 
//        answ_h++;
//    }
//    size_t x = abs(virtual_MAX.x) > abs(virtual_MIN.x) ? abs(virtual_MAX.x) : abs(virtual_MIN.x);
//    for (; x >= 10; answ_w++) 
//    {
//        x = x / 10;
//    }
//    size_t y = abs(virtual_MAX.y) > abs(virtual_MIN.y) ? abs(virtual_MAX.y) : abs(virtual_MIN.y);
//    for (; y >= 10; answ_h++) 
//    {
//        y = y / 10;
//    }
//
//    shift_w = answ_w;
//    shift_h = answ_h;
//}
//
//
//
//
//	void Corner(Triangle& triangle, unsigned int coefficient, bool draw_triangle, bool draw_round) {
//
//        // { some magic
//       /* shift_w = 4;
//        int indent = shift_w*2;
//        int y_axis_thickness = 2;
//        int x_axis_thickness = 1;
//        int shift_h = 1;
//        int shift = 0;*/
//        // } some magic
//
//		//} start of work wich axis 
//		// start of work with axis
//		// start of work with axis
//
//		size_t N;
//		size_t M;
//
//        int max_y = virtual_MAX.y;
//        int min_y = virtual_MIN.y;
//
//        int max_x = virtual_MAX.x;
//        int min_x = virtual_MIN.x;
//
//		if (min_y == max_y)
//			N = abs(max_y) + 1;
//		else
//			if (min_y >= 0 && max_y >= 0)
//				N = abs(max_y) + 1;
//			else if (min_y <= 0 && max_y <= 0)
//				N = abs(min_y) + 1;
//			else
//				N = abs(max_y) + abs(min_y) + 1;
//
//		if (max_x == min_x)
//			M = abs(max_x) + 1;
//		else if (max_x >= 0 && min_x >= 0)
//			M = abs(max_x) + 1;
//		else if (max_x <= 0 && min_x <= 0)
//			M = abs(min_x) + 1;
//		else
//			M = abs(max_x) + abs(min_x) + 1;
//
//		std::cout << "\n";
//
//
//
//        Matrix corner_print;
//
//        corner_print.resaize(N + shift_h, M + shift_w);
//		// {print y axis
//        
//		int start_y = max_y > 0 ? max_y : 0;
//        int size_h = shift_h;
//        int temp_N = N;
//        int temp_inpt;
//        for (size_t i = 0; i < N; i++) 
//        {
//            size_h = shift_h;
//            temp_inpt = start_y - i;
//
//            for (size_t j = 0; j < shift_h; j++)
//            {
//                int inpt = temp_inpt % 10;
//                temp_inpt = temp_inpt / 10;
//                int g = 0 + size_h;
//                if (inpt < 0)
//                    corner_print[i][0] = '-';
//
//                corner_print[i][g] = '0' + abs(inpt);
//
//                --size_h;
//            }
//          
//        }
//		// }end print y axis
//
//
//		//{find actual console point of start coodrs
//		Point ZERO;
//        
//
//        ZERO.y = start_y + 1;// +shift_w; //!x_axis_thickness
//		//}find actual console point of start coodrs
//
//		// {print x Axys
//		int start_x = min_x > 0 ? 0 : min_x;
//         
//        for (size_t i = 0; i < M; i++)
//        {
//            temp_inpt = min_x + i; // ?
//            if (temp_inpt >= 0)
//            {
//                for (int j = shift_w; j > 0; --j)
//                {
//                    if (j == shift_w)
//                    {
//                        corner_print[N][shift_h + (i * shift_w) + j] = '|';
//                    }
//                    else
//                    {
//                        int inpt = temp_inpt % 10;
//                        temp_inpt = temp_inpt / 10;
//                        corner_print[N][shift_h + (i * shift_w) + j] = '0' + abs(inpt);
//                    }
//                }
//            }
//            else
//            {
//                for (int j = shift_w; j > 0; --j)
//                {
//
//                    if (j == shift_w)
//                    {
//                        corner_print[N][shift_h + (i * shift_w) + j] = '|';
//                    }
//                    else
//                    {
//                        int inpt = temp_inpt % 10;
//                        temp_inpt = temp_inpt / 10;
//                        corner_print[N][shift_h + (i * shift_w) + j] = '0' + abs(inpt);
//                        corner_print[N][shift_h + (i * shift_w) + 1] = '-';
//
//                    }
//                }
//            }
//        }
//    
//        //for (size_t i = 0; i < M; i++)
//        //{
//        //    //std::cout << std::setw(shift_w) << start_x + (int)i;
//        //    corner_print.set_at(N, i+1, std::to_string(start_x + (int)i));
//        //}
//
//
//		// }end print x axis
//
//
//        std::cout << "\n";
//        for (size_t i = 0; i <= N; i++)
//        {
//            for (size_t j = 0; j <= M; j++) 
//            {
//                std::cout << "\t" << corner_print.get_at(i, j);
//            }
//            std::cout << "\n";
//        }
//
//		//{find actual console point of start coodrs
//		std::cout << "\n";
//		ZERO.x = ((abs(start_x))); //!!!!!SHIFT
//		//}find actual console point of start coodrs
//
//		// {print on start coord "0"
//		std::cout << "\n";
//		goto_coords(ZERO);
//		std::cout << "0";
//		// }print on start coord "0"
//
//		// {Point end use for get new line after print axis
//		//Point end; // use to print Axys
//		//end.x = 0;
//		//end.y = N + (N * shift) + x_axis_thickness + shift_h;  //+1 str
//		//end.y = end.y + 1;
//		//goto_coords(end);
//		// }Point end use for get new line after print axis
//
//
//
//
//		std::cout << "\n";
//		std::cout << "END\n";
//		std::cout << "\n";
//
//		std::cout << "min_x " << min_x << "\n";
//		std::cout << "max_x " << max_x << "\n";
//		std::cout << "max_y " << max_y << "\n";
//		std::cout << "min_y " << min_y << "\n";
//
//		//}end of work wich axis 
//		//end of work with axis
//		//end of work with axis
//
//
//	}
//
//    /*
//    //{print points in the point_arr arr
//    for (size_t j = 0; j < n_points; j++) {
//        Point coord;
//        coord.x = ZERO.x + (point_arr[j].x * width_x);
//        coord.y = ZERO.y - point_arr[j].y;
//        goto_coords(coord);
//        std::cout << "x";
//    }
//    //}print points in the point_arr arr
//    */