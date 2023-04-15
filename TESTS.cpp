#pragma once

#include "Ray.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <iterator>
#include "it_test.h"

struct TEST
{
    void test_0()
    {
        Ray<int> arr{ 1, 2, 3, 4, 5};
        int end;
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            std::cout << *it  << " ";
            end = *it;
        }
        assert(end == 5);
        std::cout << "\ntest_0_END\n";
    }

    void test_1 ()
    {
        Ray<int> arr{ 1, 2, 3, 4, 5 };
        int sum = 0;
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            sum += *it;
        }
        assert(sum == 15);
        std::cout << "\ntest_1_END\n";
    }

    void test_2() const
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        const Iterator<int> begin(arr);
        const Iterator<int> end(arr + 5);
        for (auto it = begin; it != end; ++it)
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

        const Iterator<int> begin(&it_test[0]);
        const Iterator<int> end(&it_test[0] + 5);

        for (auto it_test = begin; it_test != end; ++it_test)
        {
            *it_test = 10;
            std::cout << *it_test << " ";
        }
        std::cout << "\ntest_3_END\n";
    }

    void test_4()
    {
        Ray<int> arr{ 1, 2, 3 };
        auto it = arr.begin();
        *it = 10;
        ++it;
        *it = 20;
        ++it;
        *it = 30;
        assert(arr[0] == 10);
        assert(arr[1] == 20);
        assert(arr[2] == 30);
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
        assert(sum == 6);
        std::cout << "\ntest_5_END\n";
    }
    
    //void test_6()
    //{
    //     Ray<int> arr{ 1, 2, 3, 4, 5 };
    //     const auto it = std::find(arr.begin(), arr.end(), 3);
    //    assert(*it == 3);
    //    std::cout << "\ntest_6_END\n";
    //}

    //void test_7()
    //    {
    //    Ray<int> arr{ 1, 2, 3, 4, 5 };
    //    std::vector<int> v;
    //    std::copy(arr.begin(), arr.end(), std::back_inserter(v));
    //    assert(v.size() == arr.size());
    //    for (int i = 0; i < arr.size(); ++i) {
    //        assert(v[i] == arr[i]);
    //    }
    //    std::cout << "\ntest_7_END\n";
    //}
};