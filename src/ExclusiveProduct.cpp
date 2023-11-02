/*
    ######### Problem description: #########
    Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.

    For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].

    Follow-up: what if you can't use division?
*/
#include "helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>

std::vector<int> findExclusiveProduct(const std::vector<int>& numbers)
{
    // Keep a running product of all elements before the current one
    int leftProduct = 1;
    // Todo: Consider potential for overflow on multiplication
    std::vector<int> result(numbers.size());
    for (size_t i = 0; i < numbers.size(); ++i) {
        // Get product of all elements after current one
        int rightProduct = 1;
        for (size_t j = i + 1; j < numbers.size(); ++j) {
            rightProduct *= numbers[j];
        }
        // result for an element is product of all elements on left and right sides of it
        result[i] = leftProduct * rightProduct;
        leftProduct *= numbers[i];
    }
    return result;
}

TEST_CASE("ExclusiveProduct")
{
    std::vector<int> numbers {};
    std::vector<int> expected {};

    SECTION("Sample case #1")
    {
        numbers = { 1, 2, 3, 4, 5 };
        expected = { 120, 60, 40, 30, 24 };
        auto result = findExclusiveProduct(numbers);
        REQUIRE(result == expected);
    }

    SECTION("Sample case #2")
    {
        numbers = { 3, 2, 1 };
        expected = { 2, 3, 6 };
        auto result = findExclusiveProduct(numbers);
        REQUIRE(result == expected);
    }

    SECTION("Random values (size = 10, range = 1 : 10)")
    {
        numbers = createRandVec(10, 10, 1);
        expected.reserve(numbers.size());
        // test against naiive solution (uses division)
        for (size_t i = 0; i < numbers.size(); ++i) {
            int product = 1;
            for (size_t j = 0; j < numbers.size(); ++j) {
                product *= numbers[j];
            }
            expected.push_back(product / numbers[i]);
        }

        auto result = findExclusiveProduct(numbers);
        REQUIRE(result == expected);
    }
}