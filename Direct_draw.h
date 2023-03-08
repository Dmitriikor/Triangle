#pragma once

#include "Canvas_console.h"
#include "Point.h"
#include "Ray.h"
#include "Matrix.h"

class Direct_draw : public Canvas_console
{
public:
	void print() const override;
	void render_matrix();
private:
	void calculate_matrix() override;
};