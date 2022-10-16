#include "Ray_3_test.h"
#include "hello.h"
#include "Point_test.h"
#include <iostream>


int main(int argc, char const* argv[])
{
    Point a;
    Point b;
    Point c;
    Point d;
    Ray_3_ test___;

    a.x = 15; a.y = 1;
    test___.add_to_back(a);
    b.x = 0; b.y = 0;
    test___.add_to_back(b);
    c.x = -5; c.y = -12;
    test___.add_to_back(c);
    d.x = 1; d.y = 10;
    test___.add_to_back(d);

    hello_min_max_points(test___, true);

    Point pt;
    pt.x = 20; pt.y = -15;

    hello_try_set_min_max_by(pt);

    hello_char_w_cntr(); //rename

    hello_corner();

    hello_print_arr();

    draw_points();

    Point to_line_1;
    std::cout << "\n\t" << "input" << "\n";
    std::cin >> to_line_1.x >> to_line_1.y;
    Point to_line_2;
    std::cout << "\n\t" << "input" << "\n";
    std::cin >> to_line_2.x >> to_line_2.y;

    hello_draw_line_1(to_line_1, to_line_2);
    draw_points(true);
    std::cout << "end hello" << "\n";




    return 0;
}
