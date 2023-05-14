#pragma once

#include "Ray.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include "matrix.h"
#include "IT_TEST.h"


#include <iostream>
#include <ranges>
namespace TEST
{

	void displayNumber(int n) {
		std::cout << n << ' ';
	}

	void test_0()
	{
		try
		{
			int M = 3;
			int N = 10;
			Matrix<int> arr(N, M);

			for (size_t i = 0; i < N; ++i)
			{
				for (size_t j = 0; j < M; ++j)
				{
					arr[i][j] = i + j;
				}
			}

			for (Matrix<int>::line_iterator it = arr.lbegin(); it != arr.lend(); ++it)
			{
				std::cout << *it << " ";
			}

			/*for (auto val : arr)
			{
				std::cout << val << " ";
			}*/
			std::cout << std::endl;
			std::cout << std::endl;
			for (auto str : arr)
			{
				for (auto val : str)
					std::cout << val << " ";
				std::cout << std::endl;
			}
			int yyy = 0;
			std::cout << "\n\n RESIZE 2 x 2\n";
			arr.resize(4, 4);
			for (Matrix<int>::iterator it = arr.begin(); it != arr.end(); ++it)
			{
				for (Matrix<int>::str_i::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
				{
					if (yyy == 0)
					{
						arr.resize(2, 2);
						arr.fill(1);
						yyy++;
					}
					std::cout << *it2 << ' ';
				}
				std::cout << std::endl;
			}
			std::cout << "\n\n RESIZE 10 x 10\n";
			arr.resize(10, 10);
			arr.fill(0);

			for (auto i = arr.begin(); i != arr.end(); ++i)
			{
				for (auto j = i->begin(); j != i->end(); ++j)
				{
					std::cout << *j << " ";
				}
				std::cout << std::endl;
			}


			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;


			auto it = arr.begin();
			arr.resize(100, 100);
			if (it != arr.begin())
				std::cout << "\n auto it = arr.begin(); \n";
			arr.resize(1, 1);
			it = arr.end();
			if (it != arr.end())
				std::cout << "\n it = arr.end(); \n";
			auto itr = it;
			if (itr != it)
				std::cout << "\n auto itr = it; \n";
			if (itr != arr.end())
				std::cout << "\n itr != arr.end(); \n";


			//int cntr = 0;
			//for (auto it = arr.lbegin(); it != arr.lend(); it++)
			//{
			//	if (cntr == arr.get_M())
			//	{
			//		std::cout << std::endl;
			//		cntr = 0;
			//	}
			//	std::cout << " " << *it;
			//	cntr++;
			//}
			//int s_end;
			//for (; it != arr.end(); ++it) {
			//	s_end = *it;
			//}
			//if (s_end == 40);

			std::cout << "\n\nsub_test_m :\n";

			Matrix<int> m(2, 3);
			m[0][0] = 1;
			m[0][1] = 2;
			m[0][2] = 3;
			m[1][0] = 4;
			m[1][1] = 5;
			m[1][2] = 6;

			// test str_i
			for (auto it = m[0].begin(); it != m[0].end(); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			for (auto i = m.begin(); i != m.end(); ++i)
			{
				for (auto j = i->begin(); j != i->end(); ++j)
				{
					std::cout << *j << " ";
				}
				std::cout << std::endl;
			}


			// test const_str_i
			const Matrix<int>& cm = m;
			for (auto it = cm[1].begin(); it != cm[1].end(); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;


			std::cout << "\n\nsub_test_for_for :\n";
			for (auto i = 0; i < m.get_N(); ++i)
			{
				//std::cout << *row_it << "\n";
				for (auto it = m[i].begin(); it != m[i].end(); ++it)
					std::cout << *it << " ";

				std::cout << std::endl;
			}
			/*for (int i = 0; i < rows; i++)*/
			std::for_each(arr[0].begin(), arr[0].end(), displayNumber);

			Ray<int> r({ 1,2,3,4,5,6 });

			std::for_each(r.begin(), r.end(), displayNumber);

			std::cout << std::endl;

		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}
		std::cout << "\ntest_0_END\n\n";
	}

	void test_1()
	{
		try
		{
			Ray<int> arr;

			for (int i = 0; i <= 10; i++)
			{
				arr.add_to_back(i);
				arr.add_to_first(-i);
			}

			auto it = arr.begin();
			Ray<int>::iterator tmp0 = arr.begin() + 0;
			std::cout << *it << " " << *tmp0 << "\n";
			Ray<int>::iterator tmp1 = arr.begin() + 1;
			++it;
			std::cout << *it << " " << *tmp1 << "\n";
			Ray<int>::iterator tmp2 = arr.begin() + 2;
			it++;
			std::cout << *it << " " << *tmp2 << "\n";
			Ray<int>::iterator tmp3 = arr.begin() += 3;
			++it;
			std::cout << *it << " " << *tmp3 << "\n";

			--it;
			++it;
			it--;
			it++;

			std::cout << "\n\n== \n";
			for (auto it2 = arr.begin(); it2 != arr.end(); ++it2)
			{
				std::cout << " " << *it2;
			}
			std::cout << "\n\n<= \n";
			for (auto it2 = arr.begin(); it2 <= arr.end(); ++it2)
			{
				if (it2 < arr.end())
					std::cout << " " << *it2;
				else
					std::cout << " and garbage = " << *it2;
			}
			std::cout << "\n\n<  \n";
			for (auto it2 = arr.begin(); it2 < arr.end(); ++it2)
			{
				std::cout << " " << *it2;
			}

			std::cout << "\n\narr.capacity = " << arr.capacity() << "\n";

			if (it == tmp3)
				std::cout << "\ntest_1_end  " << *it << " = " << *tmp3 << "\n";
			else
				std::cout << "\ntest_1_ff  " << *it << " = " << *tmp3 << "\n";
		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}
	}

	void test_2()
	{
		try
		{
			int arr[] = { 1, 2, 3, 4, 5 };
			const Iterator<int> begin(arr);
			const Iterator<int> s_end(arr + 5);
			for (auto it = begin; it != s_end; ++it);


			std::cout << "\ntest_2_END\n";
		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}

	}

	void test_3()
	{
		try
		{
			Ray<int> it_test;
			for (int i = 0; i < 7; ++i)
				it_test.add_to_back(i);

			const Iterator<int> begin(&it_test[0]);
			const Iterator<int> s_end(&it_test[0] + 5);

			for (auto it_test = begin; it_test != s_end; ++it_test)
			{
				*it_test = 10;
			}
			std::cout << "\ntest_3_END\n";


		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}

	}

	void test_4()
	{
		try
		{
			Ray<int> arr{ 1, 2, 3 };
			auto it = arr.begin();
			*it = 10;
			++it;
			*it = 20;
			++it;
			*it = 30;
			if (arr[0] == 10);
			if (arr[1] == 20);
			if (arr[2] == 30);

			std::cout << "\ntest_4_END\n";

		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}

	}

	void test_5()
	{
		try
		{
			Ray<int> arr{ 1, 2, 3, 4, 5, 6 };
			const Ray<int>& c_arr = arr;
			int sum = 0;
			for (auto it = c_arr.begin(); it != c_arr.end(); ++it) {
				sum += *it;
			}
			if (sum == 6);
			std::cout << "\ntest_5_END\n";

		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}

	}

	void test_6()
	{
		try
		{
			std::cout << "\ntest_6_START\n\n";
			Ray<int> arr(100, 100);

			std::cout << "Array size before push_back: " << arr.size() << std::endl;

			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);

			std::cout << "Array elements: \n";
			for (auto it = arr.begin(); it != arr.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;

			std::cout << "Array size after push_back: " << arr.size() << std::endl;

			arr.remove(1);

			std::cout << "Array size after remove: " << arr.size() << std::endl;

			std::cout << "Array elements after erase: \n";
			for (auto it = arr.begin(); it != arr.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;

			std::cout << "Array size after all: " << arr.size() << std::endl;
			std::cout << "\ntest_6_END\n";

		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}

	}


	//void test_7()
	//{
	//     Ray<int> arr{ 7, 2, 3, 4, 5 };
	//     std::sort(arr.begin(), arr.s_end(), 3);
	//    if(arr[0] = 2);
	//    std::cout << "\ntest_6_END\n";
	//}

	//void test_8()
	//    {
	//    Ray<int> arr{ 1, 2, 3, 4, 5 };
	//    std::vector<int> v;
	//    std::copy(arr.begin(), arr.s_end(), std::back_inserter(v));
	//    if(v.size() == arr.size());
	//    for (int i = 0; i < arr.size(); ++i) {
	//        if(v[i] == arr[i]);
	//    }
	//    std::cout << "\ntest_7_END\n";
	//}

	void test_9()
	{
		try
		{
			std::cout << "\ntest_9_START\n";

			Ray<float> ray({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f });


			float* data_ptr = ray.data();
			if (data_ptr[0] != 1.0f || data_ptr[1] != 2.0f || data_ptr[2] != 3.0f ||
				data_ptr[3] != 4.0f || data_ptr[4] != 5.0f || data_ptr[5] != 6.0f) {
				throw std::runtime_error("data() method returns incorrect data.");
			}

			const float* const_data_ptr = ray.cdata();
			if (const_data_ptr[0] != 1.0f || const_data_ptr[1] != 2.0f || const_data_ptr[2] != 3.0f ||
				const_data_ptr[3] != 4.0f || const_data_ptr[4] != 5.0f || const_data_ptr[5] != 6.0f) {
				throw std::runtime_error("cdata() method returns incorrect data.");
			}

			Ray v({ 9, 2, 3 });
			auto it = v.begin();

			int* ptr = it.operator->();
			int* ptr1 = it.data();
			const int* ptr2 = it.cdata();
			const int* ptr3 = it.data();
			auto		 ptr4 = it.size();
			auto		 ptr5 = it.empty();

			std::cout << "ptr  = " << *ptr << "\n";
			std::cout << "ptr1  = " << *ptr1 << "\n";
			std::cout << "ptr2  = " << *ptr2 << "\n";
			std::cout << "ptr3  = " << *ptr3 << "\n";
			std::cout << "ptr4  = " << ptr4 << "\n";
			std::cout << "ptr5  = " << ptr5 << "\n";

		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}
		std::cout << "\ntest_9_END\n";
	}
};