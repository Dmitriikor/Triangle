﻿#pragma once

#include "Ray.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include "matrix.h"
#include "IT_TEST.h"


#include <iostream>
#include <ranges>

struct MyStruct {
	int x;
	double y;
	char str;

	MyStruct(int xValue, double yValue, const char strValue)
		: x(xValue), y(yValue), str(strValue)
	{
		std::cout << "\n" << "constr" << "\n";
	}
	MyStruct(MyStruct&& other) noexcept
		: x(std::move(other.x)), y(std::move(other.y)), str(std::move(other.str))
	{
		std::cout << "\n" << "move" << "\n";
	}
	MyStruct(const MyStruct& other)
		: x(other.x), y(other.y), str(other.str)
	{
		std::cout << "\n" << "copy" << "\n";
	}

	~MyStruct()
	{
		std::cout << "\n" << "destruction!!!" << "\n";
	}

	void print() const {
		std::cout << "x: " << x << ", y: " << y << ", str: " << str << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& os, const MyStruct& obj)
	{
		os << "x: " << obj.x << ", y: " << obj.y << ", str: " << obj.str;
		return os;
	}

	bool operator!=(const MyStruct& other) const
	{
		//std::cout << *this << " & " << other << "\n\n";
		if (
			x == other.x &&
			y == other.y &&
			str == other.str
			)
			return false;

		return true;
	}
};


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
			int cntrTEMP = 0;
			for (size_t i = 0; i < N; ++i)
			{
				for (size_t j = 0; j < M; ++j)
				{
					arr[i][j] = cntrTEMP;
					++cntrTEMP;
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
			if (arr[0] == 10)
			if (arr[1] == 20)
			if (arr[2] == 30)

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
			if (sum == 6)
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


	void test_10()
	{
		Array<MyStruct> q(-1);

		//MyStruct qwe(1, 0.1, 'a');
		//q.add(qwe);
		////q.print();
		////q.add(10);
		//q.add(2, 0.2, 'b');
		////q.print();
		//q.add(3, 0.3, 'c');
		//q.print();
		//q.remove(1);
		//q.print();
		//MyStruct asd(99, 0.99, 'w');
		//q.add(std::move(asd));
		//q.print();
		//q.remove(2);
		//q.print();
		//q.add(4, 0.4, 'd');
		//q.cut();
		//q.print();

		//Array w(q);
		//w.print();

		////w.add(asd);
		////w.add(9, 8, 'b');
		////w.add(std::move(asd));

		//if(q==w)
		//	w.print();


		//q.add(6);
		//q.add(5);
		//q.add(4);
		//q.add(3);
		//q.add(2);
		//q.add(1);
		//q.add(0);
		//q.add(-1);
		//q.cutArray();
		//q.print();
		//q.print();
		//q.add(-999);
		//q.print();
	}

	void test_11()
	{
		Ray<int> empty0;

		if (empty0.empty() == true)
			std::cout << "empty0 start= " << empty0.empty() << "\n";

		empty0.add_to_back(0);

		if (empty0.empty() == false)
			std::cout << "empty0 add_to_back= " << empty0.empty() << "\n";

		empty0.remove(0);

		if (empty0.empty() == true)
			std::cout << "empty0 remove= " << empty0.empty() << "\n";

		empty0.add_to_first(0);

		if (empty0.empty() != true)
			std::cout << "empty0 add_to_first= " << empty0.empty() << "\n";
	
	}
	namespace Array_test
	{
		#include <cassert>

		void test_Array()
		{
			Array<int> arr;
			assert(arr.size() == 0);
			assert(arr.is_empty());

		}
		void test_Array_capacity()
		{
			Array<int> arr(5);
			assert(arr.size() == 0);
			assert(!arr.is_empty());
		}
		void test_Array_other()
		{
			Array<int> arr1;
			arr1.push_back(1);
			arr1.push_back(2);
			arr1.push_back(3);
			Array<int> arr2(arr1);
			assert(arr2.size() == arr1.size());
			assert(arr2 == arr1);
		}
		void test_Array_operator()
		{
			Array<int> arr1;
			arr1.push_back(1);
			arr1.push_back(2);
			arr1.push_back(3);
			Array<int> arr2(arr1);
			assert(arr1 == arr2);
			arr2.pop_back();
			assert(arr1 != arr2);
		}
		void test_Array_size()
		{
			Array<int> arr;
			assert(arr.size() == 0);
			arr.push_back(1);
			assert(arr.size() == 1);
		}
		void test_Array_is_empty()
		{
			Array<int> arr;
			assert(arr.is_empty());
			arr.push_back(1);
			assert(!arr.is_empty());
		}
		void test_Array_push_back()
		{
			Array<int> arr;
			arr.push_back(1);
			assert(arr.size() == 1);
			assert(arr.back() == 1);
			arr.push_back(2);
			assert(arr.size() == 2);
			assert(arr.back() == 2);
		}
		void test_Array_at()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			assert(arr.at(0) == 1);
			assert(arr.at(1) == 2);
			assert(arr.at(2) == 3);
		}
		void test_Array_front()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			assert(arr.front() == 1);
		}
		void test_Array_back()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			assert(arr.back() == 3);
		}
		void test_Array_Iterator()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);

			Array<int>::Iterator iter = arr.begin();
			assert(*iter == 1);
			++iter;
			assert(*iter == 2);
			--iter;
			assert(*iter == 1);
		}
		void test_Array_clear()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			arr.clear();
			assert(arr.size() == 0);
			assert(arr.is_empty());
		}
		void test_Array_insert()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			int t_val = 3;
			arr.insert(1, t_val);
			assert(arr.size() == 3);
			assert(arr.at(0) == 1);
			assert(arr.at(1) == 3);
			assert(arr.at(2) == 2);
		}
		void test_Array_erase()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			arr.erase(1);
			assert(arr.size() == 2);
			assert(arr.at(0) == 1);
			assert(arr.at(1) == 3);
		}
		void test_Array_emplace()
		{
			Array<std::string> arr;
			arr.emplace("Hello");
			arr.emplace("World");
			assert(arr.size() == 2);
			assert(arr.at(0) == "Hello");
			assert(arr.at(1) == "World");
		}
		void test_Array_cut()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			arr.cut();
			assert(arr.size() == 3);
			assert(arr.capacity() == 3);
		}
		void test_Array_resize()
		{
			Array<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			arr.resize(5);
			assert(arr.size() == 3);
			assert(arr.capacity() == 5);
		}
		void test_Array_run()
		{
			TEST::Array_test::test_Array();
			test_Array_capacity();
			test_Array_other();
			test_Array_operator();
			test_Array_size();
			test_Array_is_empty();
			test_Array_push_back();
			test_Array_at();
			test_Array_front();
			test_Array_back();
			test_Array_Iterator();
			test_Array_clear();
			test_Array_insert();
			test_Array_erase();
			test_Array_emplace();
			test_Array_cut();
			test_Array_resize();
		}
	}


	//std::cout << "\ntest_START\n";
	//TEST::test_0();
	//TEST::test_1();
	//TEST::test_2();
	//TEST::test_3();
	//TEST::test_4();
	//TEST::test_5();
	////TEST::test_6();
	////TEST::test_7();
	//TEST::test_9();
	//std::cout << "\ntest_END\n";
};