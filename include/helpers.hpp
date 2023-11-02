#include <random>
#include <vector>

// Populate a new vector with random integers in (randMin <= val < randMin + range-1)
inline std::vector<int> createRandVec(size_t vecSize, const int range = 100, const int randMin = 0)
{
    std::vector<int> numbers(vecSize);
    for (auto i = 0; i < vecSize; ++i) {
        numbers[i] = ((std::rand() - randMin) % range + randMin);
    }
    return numbers;
}