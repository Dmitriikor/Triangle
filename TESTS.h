#pragma once

#include "Ray.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include "matrix.h"
#include "IT_TEST.h"


#include <iostream>
#include <ranges>
struct TEST
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
					arr[i][j] = i+j;
				}
			}

			for (auto val : arr)
			{
				std::cout << val << " ";
			}

			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;


			int cntr = 0;
			for (auto it = arr.begin(); it != arr.end(); it++)
			{
				if (cntr == M)
				{
					std::cout << std::endl;
					cntr = 0;
				}
				std::cout << " " << *it;
				cntr++;
			}


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

			// test const_str_i
			const Matrix<int>& cm = m;
			for (auto it = cm[1].begin(); it != cm[1].end(); ++it) 
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		

			std::cout << "\n\nsub_test_for_for :\n";
			for (auto row_it = m.begin(); row_it != m.end(); ++row_it)
			{
				std::cout << *row_it << "\n";
				for (auto it = m[*row_it].begin(); it != m[*row_it].end(); ++it)
					std::cout << *it << " ";

				std::cout << std::endl;
			}
			for (int i = 0; i < rows; i++) 
				std::for_each(arr[i], arr[i] + 10, doSomething);
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
				if(it2 < arr.end())
				std::cout << " " << *it2;
				else
					std::cout << " and garbage = " << *it2;
			}
				std::cout << "\n\n<  \n";
			for (auto it2 = arr.begin(); it2 < arr.end(); ++it2)
			{
				std::cout << " " << *it2;
			}

			std::cout << "\n\narr.capacity = " << arr.capacity()<< "\n";

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

	void test_2() const
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


	//void test_6()
	//{
	//     Ray<int> arr{ 7, 2, 3, 4, 5 };
	//     std::sort(arr.begin(), arr.s_end(), 3);
	//    if(arr[0] = 2);
	//    std::cout << "\ntest_6_END\n";
	//}

	//void test_7()
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
};