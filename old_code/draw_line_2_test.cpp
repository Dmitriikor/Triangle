#include "draw_line_2_test.h"


//void goto_coords_(Dot a) {
//
//	COORD b;
//	b.X = a.x;
//	b.Y = a.y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
//}
//
//void draw_line_2(const Dot& A, const Dot& B, const Dot& ZERO) {
//	int x1, y1, x2, y2;
//	x1 = A.x;
//	y1 = A.y;
//	x2 = B.x;
//	y2 = B.y;
//
//	bool steep = false;
//	if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
//		std::swap(x1, y1);
//		std::swap(x2, y2);
//		steep = true;
//	}
//	if (x1 > x2) {
//		std::swap(x1, x2);
//		std::swap(y1, y2);
//	}
//
//	for (int x = x1; x <= x2; x++) {
//		float k = (x - x1) / (float)(x2 - x1);
//		int y = y1 * (1. - k) + y2 * k;
//
//		Dot coords;
//
//
//		if (steep) {
//			coords.x = ZERO.x + y * shift_w();
//			coords.y = ZERO.y - x;
//
//			goto_coords_(coords);	/////  /////
//			std::cout << "/";		/////  /////
//
//		}
//		else {
//			coords.x = ZERO.x + x * shift_w();
//			coords.y = ZERO.y - y;
//
//			goto_coords_(coords);	/////  /////
//			std::cout << "/";		/////  /////
//		}
//	}
//}
