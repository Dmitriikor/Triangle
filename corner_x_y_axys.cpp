//#include <iostream>
//#include <vector>
//#include <sstream>
//#include <cmath>
//
//
//void corner_x_y_axys() {
//	char corner_print[31][150];
//
//	//corner_print.create_matrix(N + shift_h, M + shift_w);
//	int max_y = 2;
//	int min_x = -5;
//	int N = 30;
//	int M = 100;
//	int shift_h = 2;
//	int shift_w = 3 + 1;
//	int start_y = max_y > 0 ? max_y : 0;
//	int size_h = shift_h;
//	int temp_N = N;
//	int temp_inpt;
//
//	for (size_t i = 0; i < N; i++)
//	{
//		size_h = shift_h;
//		temp_inpt = max_y - i;
//
//		for (size_t j = 0; j < shift_h; j++)
//		{
//			int inpt = temp_inpt % 10;
//			temp_inpt = temp_inpt / 10;
//			int g = 0 + size_h;
//			if (inpt < 0)
//				corner_print[i][0] = '-';
//
//			corner_print[i][g] = '0' + abs(inpt);
//
//			--size_h;
//		}
//
//	}
//
//
//	int start_x = min_x > 0 ? 0 : min_x;
//
//	for (size_t i = 0; i < M; i++)
//	{
//		temp_inpt = min_x + i;
//		if (temp_inpt >= 0)
//		{
//			for (int j = shift_w; j > 0; --j)
//			{
//				if (j == shift_w)
//				{
//					corner_print[N][shift_h + (i * shift_w) + j] = '|';
//				}
//				else
//				{
//					int inpt = temp_inpt % 10;
//					temp_inpt = temp_inpt / 10;
//					corner_print[N][shift_h + (i * shift_w) + j] = '0' + abs(inpt);
//				}
//			}
//		}
//		else
//		{
//			for (int j = shift_w; j > 0; --j)
//			{
//
//				if (j == shift_w)
//				{
//					corner_print[N][shift_h + (i * shift_w) + j] = '|';
//				}
//				else
//				{
//					int inpt = temp_inpt % 10;
//					temp_inpt = temp_inpt / 10;
//					corner_print[N][shift_h + (i * shift_w) + j] = '0' + abs(inpt);
//					corner_print[N][shift_h + (i * shift_w) + 1] = '-';
//
//				}
//			}
//		}
//	}
//}
//
