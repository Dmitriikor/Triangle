
#ifndef AXYS_H__

#define  AXYS_H__

#include "Canvas_console.h"
#include "Point.h"
#include "Ray.h"
#include "Matrix.h"

class Axys : public Canvas_console
{
public:
	////Axys& operator+=(const Axys& other);
	void remove();

	void render_matrix() override;
	void print() const override;

private:
	void calculate_matrix() override;
	Coordinate ORIGIN_;

	std::string outfile_adress = "Axys_out.txt";

	void moving_points_from_ray_to_matrix();
};

#endif //!  AXYS_H__


