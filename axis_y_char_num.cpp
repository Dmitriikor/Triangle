#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

int main() {

    char corner_print[150][150];
    for (size_t i = 0; i < 150; i++)
    {
        for (size_t j = 0; j < 150; j++)
        {
            corner_print[i][j] = ' ';
        }
    }


    //corner_print.create_matrix(N + shift_h, M + shift_w);
    int max_y = 2;
    int N = 150;
    int shift_h = 3;
    int start_y = max_y > 0 ? max_y : 0;
    int size_h = shift_h;
    int temp_N = N;
    int temp_inpt;

    for (size_t i = 0; i < N; i++)
    {
        size_h = shift_h;
        temp_inpt = max_y - i;



        for (size_t j = 0; j < shift_h; j++)
        {
            int inpt = temp_inpt % 10;
            temp_inpt = temp_inpt / 10;
            int g = 0 + size_h;
            if (inpt < 0)
                corner_print[i][0] = '-';

            corner_print[i][g] = '0' + abs(inpt);

            --size_h;
        }

    }


    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            std::cout << corner_print[i][j] << " ";
        }
        std::cout << "\n";
    }

}