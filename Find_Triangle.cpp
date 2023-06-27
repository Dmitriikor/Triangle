#include "Find_Triangle.h"
#include <omp.h>
#include <chrono>
///#include <future>

#include "nana/gui.hpp"
#include "nana/gui/widgets/label.hpp"
#include "nana/gui/widgets/button.hpp"
#include "nana/gui/widgets/checkbox.hpp"
#include "nana/gui/widgets/textbox.hpp"
#include "nana/gui/place.hpp"
#include <nana/gui/widgets/progress.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// { work with Dot arr, to create triangle and find max inside point
	size_t count_triangles_raw(size_t n_points)
	{
		if (n_points < 3)
			return 0;
		return n_points * (n_points - 2) * (n_points - 1) / 6;
	}

	double  count_triangles_raw_comb(size_t n_points)
	{
		if (n_points < 3) 
		{
			return 0;
		}
		double percent = 8.0;
		return ((n_points * (n_points - 1) * (n_points - 2)) / 6) - (((n_points * (n_points - 1) * (n_points - 2)) / 6)* percent/100);
	}


Triangle_hi Find_Triangle(const Ray<Dot>& point_arr)
{
	 

	///Triangle_hi* triangle_arr = new Triangle_hi[1 * 2 * 3 * (n_points - 2) * (n_points - 1) * n_points];  /// 1*2*3*(n_points-2)*(n_points-1)*n_points;
	Ray<Triangle_hi> triangle_arr;
	size_t n_triangles = 0;


	int num_procs = omp_get_num_procs();
	std::cout << "Number of available processors: " << num_procs << std::endl;
	omp_set_num_threads(num_procs);
//#pragma omp parallel
//	{
//Ray<Triangle_hi> local_arr;

	size_t final_count = count_triangles_raw_comb(point_arr.size());

	nana::form fm{ nana::API::make_center(320, 29), nana::appear::bald<>()};
	nana::progress progress(fm, nana::rectangle(0, 0, 320, 30));
	//progress.amount(0);
	fm.show();
	progress.amount(final_count);
	progress.unknown(false);


	
#pragma omp for collapse(3) schedule(dynamic) //private(local_arr)
		for (int i = 0; i < point_arr.size(); i++)
		{
			for (int j = i + 1; j < point_arr.size(); j++)  //!!! < n
			{
				for (int k = j + 1; k < point_arr.size(); k++)  //!!! < n
				{
					//#pragma omp atomic

					//printf("Процесс %d  стартовал\n", omp_get_thread_num());
					Triangle_hi temp_abc(point_arr[i], point_arr[j], point_arr[k]);

					if (utilities::isEqual(temp_abc.get_area(), 0))
						break;

					if (temp_abc.is_triangle_())
					{
						#pragma omp critical
						{
							triangle_arr.add_to_back(temp_abc);
							++n_triangles;
							progress.value(n_triangles);
							nana::API::update_window(fm);
							//progress.inc();
						}
					}

					//triangle_arr += local_arr;
					//printf("Процесс %d  был завершён\n", omp_get_thread_num());
				}
			}
		}
	
	//}

	std::cout	<< " count_triangles_raw = " << count_triangles_raw(point_arr.size()) 
				<< " and count_triangles_raw_comb = " << count_triangles_raw_comb(point_arr.size()) 
				<< " and n_triangles = " << n_triangles << "\n"
				<< " and triangle_arr.size() = " << triangle_arr.size() << "\n";
		
	Ray<Triangle_hi> final_triangle_arr = std::move(triangle_arr);

	progress.hide();
	nana::progress progress2(fm, nana::rectangle(0, 0, 320, 30));
	progress2.unknown(false);
	progress2.amount(final_triangle_arr.size() * point_arr.size());

	///size_t hit = 0;
#pragma omp for collapse(2) schedule(dynamic) //private(local_arr)
	for (int i = 0; i < final_triangle_arr.size(); i++)
	{
		for (int j = 0; j < point_arr.size(); j++)
		{
			if (final_triangle_arr[i].is_inside(point_arr[j]))
			{
				#pragma omp critical
				{
				final_triangle_arr[i].add_point_at_vector(point_arr[j]);
				progress2.inc();
				nana::API::update_window(fm);
				}
			}
		}
	}

	progress2.hide();
	nana::progress progress3(fm, nana::rectangle(0, 0, 320, 30));
	progress3.amount(final_triangle_arr.size());

	std::string path_out2 = "out.txt";

	size_t max_dot = 0;
	size_t max_dot_index = 0;
	for (size_t i = 0; i < final_triangle_arr.size(); i++)
	{
		if (final_triangle_arr[i].get_dot_counter() > max_dot) 
		{
			max_dot = final_triangle_arr[i].get_dot_counter();
			max_dot_index = i;
		}
			progress3.inc();
			nana::API::update_window(fm);
		//triangles_print_outfile(final_triangle_arr, n_triangles, path_out2);
	}

	progress3.hide();
	fm.close();

	if (max_dot != 0)
	{
		//return final_triangle_arr[max_dot_index];

		Triangle_hi final_triangle;
		final_triangle = final_triangle_arr[max_dot_index];

		final_triangle.print();
		return final_triangle;
	}

	//return Triangle_hi();
	Triangle_hi no_Triangle;
	return no_Triangle;
}
// } work with Dot arr, to create triangle and find max inside point
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//auto start = std::chrono::high_resolution_clock::now();
		//auto end = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<double> duration = end - start;
		//auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
		//std::cout << "\n\n---------------------------------------\n";
		//std::cout << "Runtime of print_to_file: " << seconds;
		//std::cout << "\n---------------------------------------\n";
		//print_to_file_timer = seconds;




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
