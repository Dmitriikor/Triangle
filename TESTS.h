#pragma once

#include "Ray.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include "matrix.h"
#include "IT_TEST.h"


struct TEST
{
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

			for (int val : arr) 
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
		}
		catch (const std::runtime_error& err)
		{
			std::cerr << "runtime_error: " << err.what() << std::endl;
		}
		std::cout << "\ntest_0_END\n";
	}

	void test_1()
	{
		try
		{
			Ray<int> arr{ 1, 2, 3, 4, 5 };

			auto it = arr.begin();
			Ray<int>::iterator tmp0 = arr.begin()[0];
			std::cout << *it << " " << *tmp0 << "\n";
			Ray<int>::iterator tmp1 = arr.begin()[1];
			++it;
			std::cout << *it << " " << *tmp1 << "\n";
			Ray<int>::iterator tmp2 = arr.begin()[2];
			it++;
			std::cout << *it << " " << *tmp2 << "\n";


			if (it == tmp2)
				std::cout << "\ntest_1_END\n" << *it << " " << *tmp0 << "\n";
			else
				std::cout << "\ntest_1_FF\n" << *it << " " << *tmp0 << "\n";
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
			Ray<int> arr{ 1, 2, 3 };
			const Ray<int>& c_arr = arr;
			int sum = 0;
			for (auto it = c_arr.cbegin(); it != c_arr.cend(); ++it) {
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