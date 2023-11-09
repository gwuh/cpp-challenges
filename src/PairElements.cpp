/*
    ######### Problem description: #########
    cons(a, b) constructs a pair, and car(pair) and cdr(pair) returns the first and last element of that pair.
    For example, car(cons(3, 4)) returns 3, and cdr(cons(3, 4)) returns 4.

    Given this implementation of cons:

    def cons(a, b):
        def pair(f):
            return f(a, b)
        return pair

    Implement car and cdr.
*/

#include "helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <iostream>

// The purpose of this problem is to use functional programming.
// (car, cdr, and cons are major functions in the Scheme programming language)
// As such this implementation takes into consideration immutability, using first-class
// functions (function objects), and preventing side-effects.

template <typename T>
const std::function<T(T(const T&, const T&))> cons(const T& a, const T& b)
{
    return [a, b](T (*f)(const T&, const T&)) -> T {
        return f(a, b);
    };
}

template <typename T>
T car(const std::function<T(T(const T&, const T&))>& pair)
{
    return pair([](const T& a, const T& b) -> T {
        return a;
    });
}

template <typename T>
T cdr(const std::function<T(T(const T&, const T&))>& pair)
{
    return pair([](const T& a, const T& b) -> T {
        return b;
    });
}

TEST_CASE("PairElements", "[current]")
{
    SECTION("Sample case")
    {
        REQUIRE(car(cons(3, 4)) == 3);
        REQUIRE(cdr(cons(3, 4)) == 4);
    }

    SECTION("Swap case")
    {
        const auto p = cons<std::string>("Bark", "Woof");

        REQUIRE(car(p) == "Bark");
        REQUIRE(cdr(p) == "Woof");

        // Construct a new pair that has swapped the first and last values of the old pair
        const auto pSwapped = cons<std::string>(cdr(p), car(p));

        REQUIRE((car(pSwapped) + cdr(pSwapped)) == "WoofBark");
    }
}