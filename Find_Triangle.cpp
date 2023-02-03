#include "Find_Triangle.h"
///#include <future>

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
			if (final_triangle_arr[i].is_inside(point_arr[j])) {
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
		triangles_print_outfile(final_triangle_arr, n_triangles, path_out2);
	}

	if (max_dot != 0)
	{
		Triangle_hi final_triangle;
		final_triangle = final_triangle_arr[max_dot_index];

		final_triangle.print();
		return final_triangle;
	}

	Triangle_hi no_Triangle;
	return no_Triangle;
}
// } work with Dot arr, to create triangle and find max inside point
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// { work with Dot arr, to create triangle and find max inside point
////Triangle_hi Find_Triangle_with_the_thread(Ray<Dot>& point_arr, size_t n_points)
////{
////	///Triangle_hi* triangle_arr = new Triangle_hi[1 * 2 * 3 * (n_points - 2) * (n_points - 1) * n_points];  /// 1*2*3*(n_points-2)*(n_points-1)*n_points;
////
////	Ray<Triangle_hi> to_thread;
////
////	for (size_t i = 0; i < n_points; i++)
////	{
////		for (size_t j = i + 1; j < n_points; j++)  //!!! < n
////		{
////			for (size_t k = j + 1; k < n_points; k++)  //!!! < n
////			{
////				Triangle_hi temp_abc(point_arr[i], point_arr[j], point_arr[k]);
////
////				if (utilities::isEqual(temp_abc.get_area(), 0))
////					break;
////
////				if (temp_abc.is_triangle_())
////					to_thread.add_to_back(temp_abc);
////				
////			}
////		}
////
////		 
////		bool free_1 = true;
////		 
////		bool free_2 = true;
////		 
////		bool free_3 = true;
////		int long_ = to_thread.size();
////		for (size_t i = 0; i < long_; i++)
////		{
////			for (size_t j = 0; j < n_points; j++)
////			{
////				while (true)
////				{
////					if (free_1) {
////						free_1 = false;
////						std::future<bool> async_1 = std::async(Triangle_hi::is_inside, std::ref(point_arr[j]), std::ref(to_thread[i]));
////
////						bool is = async_1.get();
////						if (is)
////							to_thread[i].add_point_at_vector(point_arr[j]);
////
////
////						free_1 = true;
////						break;
////					}
////
////					if (free_2) {
////						free_2 = false;
////						std::future<bool> async_2 = std::async(Triangle_hi::is_inside, std::ref(point_arr[j]), std::ref(to_thread[i]));
////						bool is = async_2.get();
////						if (is)
////							to_thread[i].add_point_at_vector(point_arr[j]);
////
////						free_2 = true;
////						break;
////					}
////
////					if (free_3) {
////						free_3 = false;
////						std::future<bool> async_3 = std::async(Triangle_hi::is_inside, std::ref(point_arr[j]), std::ref(to_thread[i]));
////						bool is = async_3.get();
////						if (is)
////							to_thread[i].add_point_at_vector(point_arr[j]);
////
////						free_3 = true;
////						break;
////					}
////				}
////
////			}
////		}
////
////
////
////		Ray<Triangle_hi> final_triangle_arr;
////
////		for (size_t i = 0; i < to_thread.size(); i++)
////		{
////			final_triangle_arr.add_to_back(to_thread[i]);
////		}
////		
////
////		std::string path_out2 = "triangles_out.txt";
////
////		size_t max_dot = 0;
////		size_t max_dot_index = 0;
////		for (size_t i = 0; i < final_triangle_arr.size(); i++) {
////			if (final_triangle_arr[i].get_dot_counter() > max_dot) {
////				max_dot = final_triangle_arr[i].get_dot_counter();
////				max_dot_index = i;
////			}
////			Triangle_hi::triangles_print_outfile(final_triangle_arr, final_triangle_arr.size(), path_out2);
////		}
////
////		if (max_dot != 0)
////		{
////			Triangle_hi final;
////			final = final_triangle_arr[max_dot_index];
////
////			final.print();
////			return final;
////		}
////
////		Triangle_hi no_Triangle;
////		return no_Triangle;
////	}
////}
////	// } work with Dot arr, to create triangle and find max inside point
////	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
