#include "hello.h"

void hello_min_max_points(Ray_3_& points) {
    size_t length = points.size();

    Point _MAX_ = points[0];
    Point _MIN_ = points[0];

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