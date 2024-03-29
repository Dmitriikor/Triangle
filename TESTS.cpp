﻿#pragma once

#include "Ray.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include "it_test.h"

  struct TEST
{
      void test_0()
    {
        Ray<int> arr{ 1, 2, 3, 4, 5};
        int s_end;
        for (auto it = arr.s_begin(); it != arr.s_end(); ++it) {
            std::cout << *it  << " ";
            s_end = *it;
        }
        if(s_end == 5);
        std::cout << "\ntest_0_END\n";
    }

      void test_1 ()
    {
        Ray<int> arr{ 1, 2, 3, 4, 5 };
        int sum = 0;
        for (auto it = arr.s_begin(); it != arr.s_end(); ++it) {
            sum += *it;
        }
        if(sum == 15);
        std::cout << "\ntest_1_END\n";
    }

      void test_2() const
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        const Iterator<int> s_begin(arr);
        const Iterator<int> s_end(arr + 5);
        for (auto it = s_begin; it != s_end; ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << "\ntest_2_END\n";
    }

      void test_3()
    {
        Ray<int> it_test;
        for (int i = 0; i < 7; ++i)
            it_test.add_to_back(i);

        const Iterator<int> s_begin(&it_test[0]);
        const Iterator<int> s_end(&it_test[0] + 5);

        for (auto it_test = s_begin; it_test != s_end; ++it_test)
        {
            *it_test = 10;
            std::cout << *it_test << " ";
        }
        std::cout << "\ntest_3_END\n";
    }

      void test_4()
    {
        Ray<int> arr{ 1, 2, 3 };
        auto it = arr.s_begin();
        *it = 10;
        ++it;
        *it = 20;
        ++it;
        *it = 30;
        if(arr[0] == 10);
        if(arr[1] == 20);
        if(arr[2] == 30);
        std::cout << "\ntest_4_END\n";
    }
    
      void test_5()
    {
        Ray<int> arr{ 1, 2, 3 };
        const Ray<int>& c_arr = arr;
        int sum = 0;
        for (auto it = c_arr.cbegin(); it != c_arr.cend(); ++it) {
            sum += *it;
        }
        if(sum == 6);
        std::cout << "\ntest_5_END\n";
    }
    
    //void test_6()
    //{
    //     Ray<int> arr{ 7, 2, 3, 4, 5 };
    //     std::sort(arr.s_begin(), arr.s_end(), 3);
    //    if(arr[0] = 2);
    //    std::cout << "\ntest_6_END\n";
    //}

    //void test_7()
    //    {
    //    Ray<int> arr{ 1, 2, 3, 4, 5 };
    //    std::vector<int> v;
    //    std::copy(arr.s_begin(), arr.s_end(), std::back_inserter(v));
    //    if(v.size() == arr.size());
    //    for (int i = 0; i < arr.size(); ++i) {
    //        if(v[i] == arr[i]);
    //    }
    //    std::cout << "\ntest_7_END\n";
    //}
};