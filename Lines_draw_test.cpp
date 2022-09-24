#include "Lines_draw_test.h"

//Point ZERO_() { Point ZERO; return  ZERO; };
//Point ORIGIN() { Point ORIGIN; return  ORIGIN; }  // origin relative to the console  / íà÷. êîîðäèíàò îòíîñèòåëüíî êîíñîëè
Point ORIGIN;
size_t shift() {	size_t shift = 0; return shift; };
size_t shift_w() { size_t shift_w = 3 + (shift() * 3); return shift_w; };
void shift_w(size_t shiftset) { size_t shift_w = shiftset;};
size_t shift_h() { size_t shift_h = 0 + (shift() * 1); return shift_h; };
size_t indent() { size_t indent = 4; return indent; };
int y_axis_thickness() { int y_axis_thickness = 2; return y_axis_thickness; };
int x_axis_thickness() { int x_axis_thickness = 1; return x_axis_thickness; };
unsigned int coefficient() { unsigned int coefficient = 1; return coefficient; };


void indent_print() {
	for (size_t i = 0; i < indent(); i++)
	{
		std::cout << " ";
	}
}

double get_step_by(unsigned coefficient) {
	double step = 1.0 / coefficient;
	return step;
}

void setCursorPosition(int XPos, int YPos) {
	printf("\033[%d;%dH", YPos + 1, XPos + 1);
}

void SetCursorPosition(int XPos, int YPos) {
	printf("\033[%d;%dH", YPos + 1, XPos + 1);
}

int set_pos_x(int index) {
	return (ORIGIN.x + index) * shift_w();
}

void printPoint(const Point& point, const Point& ORIGIN, unsigned coefficient) {

	int con_x = (ORIGIN.x + (int)round(point.x * coefficient)) * shift_w();
	int con_y = ORIGIN.y - (int)round(point.y * coefficient);

	setCursorPosition(con_x, con_y);
	std::cout << "o" << std::endl;
}

double round(double x, double step) {
	double modulo = fmod(x, step);
	if (modulo < step / 2)
		return x - modulo;
	return x - modulo + step;
}

void draw_line_4(const Point& A, const Point& B, const Point& ORIGIN, unsigned coefficient) {

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
		double step = get_step_by(coefficient);  // 1.0 / coefficient;
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

	double step = get_step_by(coefficient);  // 1.0 / coefficient;

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Line_4_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
