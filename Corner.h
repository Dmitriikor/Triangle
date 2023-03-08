//#pragma once
#ifndef Corner_H__

#define  Corner_H__

#include "Canvas_console.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

class Corner : public Canvas_console
{
public:
	void change_file_path(const std::string& address);

	void print(std::ostream& output = std::cout);
	void render_and_print(std::ostream& output);
	void print_to_file();

	void render_matrix() override;
	void print() const override;

	Corner();

private:

	Coordinate ORIGIN_;
	std::string outfile_adress;

	void calculate_matrix() override;

	void moving_points_from_ray_to_matrix(); //not for public mb move to Canvas
	void add_points_to_corner();
	void erase_point_from_corner(const Dot& err);
};
#endif //!  Corner_H__
