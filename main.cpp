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

    a.x = 101; a.y = 1;
    test___.add_to_back(a);
    b.x = 0; b.y = 0;
    test___.add_to_back(b);
    c.x = 3; c.y = -5000;
    test___.add_to_back(c);
    d.x = 1; d.y = 800;
    test___.add_to_back(d);

    hello_min_max_points(test___);

    hello_char_w_cntr();
    std::cout << "end helo" << "\n";




    return 0;
}
