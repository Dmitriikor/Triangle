#include "hello.h"

Point _MAX_;
Point _MIN_;

void hello_min_max_points(Ray_3_& points) {
    size_t length = points.size();

     _MAX_ = points[0];
     _MIN_ = points[0];

    for (size_t i = 0; i < length; i++)
    {

        if (_MAX_.x < points[i].x)
            _MAX_.x = points[i].x;


        if (_MAX_.y < points[i].y)
            _MAX_.y = points[i].y;

        if (_MIN_.x > points[i].x)
            _MIN_.x = points[i].x;

        if (_MIN_.y > points[i].y)
            _MIN_.y = points[i].y;

    }
  
    std::cout << std::endl << _MAX_.x << " : " << _MAX_.y << std::endl;
    std::cout << std::endl << _MIN_.x << " : " << _MIN_.y << std::endl;

}

int shift_w_ = -1;
int shift_h_ = -1;

void hello_char_w_cntr() {
    size_t answ_w = 1;
    size_t answ_h = 1;
    if (_MIN_.y < 0 || _MIN_.x < 0)
    {
        answ_w++;
        answ_h++;
    }
    size_t x = abs(_MAX_.x) > abs(_MIN_.x) ? abs(_MAX_.x) : abs(_MIN_.x);
    for (; x >= 10; answ_w++) {
        x = x / 10;
    }
    size_t y = abs(_MAX_.y) > abs(_MIN_.y) ? abs(_MAX_.y) : abs(_MIN_.y);
    for (; y >= 10; answ_h++) {
        y = y / 10;
    }

    shift_w_ = answ_w;
    shift_h_ = answ_h;

    std::cout << std::endl << shift_w_ << std::endl;
    std::cout << std::endl << shift_h_ << std::endl;

}