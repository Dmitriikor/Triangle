#include "Find_Triangle.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// { work with Dot arr, to create triangle and find max inside point
Triangle_hi Find_Triangle(Ray<Dot>& point_arr, size_t n_points)
{
	///Triangle_hi* triangle_arr = new Triangle_hi[1 * 2 * 3 * (n_points - 2) * (n_points - 1) * n_points];  /// 1*2*3*(n_points-2)*(n_points-1)*n_points;
	Ray<Triangle_hi> triangle_arr;
	size_t n_triangles = 0;
	for (size_t i = 0; i < n_points; i++)
	{
		for (size_t j = i + 1; j < n_points; j++)  //!!! < n
		{
			for (size_t k = j + 1; k < n_points; k++)  //!!! < n
			{
				Triangle_hi temp_abc(point_arr[i], point_arr[j], point_arr[k]);

				if (utilities::isEqual(temp_abc.get_area(), 0))
					break;

				if (temp_abc.is_triangle_()) {
					triangle_arr.add_to_back(temp_abc);
					++n_triangles;
				}
			}
		}
	}

	Ray<Triangle_hi> final_triangle_arr = std::move(triangle_arr);

	///size_t hit = 0;
	for (size_t i = 0; i < n_triangles; i++) {
		for (size_t j = 0; j < n_points; j++)
			if (Triangle_hi::is_inside(point_arr[j], final_triangle_arr[i])) {
				final_triangle_arr[i].add_point_at_vector(point_arr[j]);
			}
	}


	std::string path_out2 = "out.txt";

	size_t max_dot = 0;
	size_t max_dot_index = 0;
	for (size_t i = 0; i < n_triangles; i++) {
		if (final_triangle_arr[i].get_dot_counter() > max_dot) {
			max_dot = final_triangle_arr[i].get_dot_counter();
			max_dot_index = i;
		}
		Triangle_hi::triangles_print_outfile(final_triangle_arr, n_triangles, path_out2);
	}

	if (max_dot != 0)
	{
	Triangle_hi final;
		final = final_triangle_arr[max_dot_index];

		final.print();
		return final;
	}

	Triangle_hi no_Triangle;
	return no_Triangle;
}
// } work with Dot arr, to create triangle and find max inside point
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
