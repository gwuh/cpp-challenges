/*
    ######### Problem description: #########
    Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

    For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

    Bonus: Can you do this in one pass?
*/
#include "helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

// Find two numbers in a list that sum to a target number
// Note: Each number has exactly 1 other number with which it can sum to any other number.
//       For each number encountered, we can calculate its paired number as target - num
//       and store that value in a map as a key. As we traverse, if the current value
//       exists in the map, it means it must sum with an already-seen number in the list,
//       to equal the target, so we can return the indices to these two values as the result.
const std::pair<size_t, size_t> findTwoSum(const std::vector<int>& numbers, const int target)
{
    // Hash table that tracks numbers required for the target sum
    std::unordered_map<int, int> sumMap {};

    for (size_t i = 0; i < numbers.size(); ++i) {
        if (sumMap.contains(numbers[i])) {
            // This number is sought by another in the list, return both indices
            auto index = sumMap[numbers[i]];
            return std::make_pair(index, i);
        }
        // Store the index under a key that is the paired number
        // that this number needs for the target sum
        sumMap[target - numbers[i]] = i;
    }

    // target was not found
    return std::make_pair(-1, -1);
}

TEST_CASE("TwoSum")
{
    std::vector<int> numbers {};
    int target {};

    SECTION("Sample case")
    {
        numbers = { 10, 15, 3, 7 };
        target = 17;
        auto result = findTwoSum(numbers, 17);
        auto fact = std::make_pair<size_t, size_t>(0, 3);
        REQUIRE(result.first == fact.first);
        REQUIRE(result.second == fact.second);
    }

    SECTION("Random values (size = 12)")
    {
        constexpr unsigned VEC_SIZE = 12;

        numbers = createRandVec(VEC_SIZE);
        // choose a random target sum that definitely exists within the list
        // (at least as long as VEC_SIZE is an even number)
        const int rand_ind = std::rand() % VEC_SIZE;
        target = numbers.at(rand_ind) + numbers.at((VEC_SIZE - 1) - rand_ind);

        auto [idx1, idx2] = findTwoSum(numbers, target);
        REQUIRE((numbers[idx1] + numbers[idx2]) == target);
    }
}