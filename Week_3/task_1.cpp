#include "timer.hpp"
#include <random>
#include <iterator> 
#include <set>
#include <vector>

int main()
{
    Timer t;
    long long vector_time = 0, multiset_time = 0;
    const std::size_t measures = 5, count = 100000;
    std::mt19937 gen{ std::random_device()() };
    std::uniform_int_distribution<int> uid(0, count);

    for (auto j = 0U; j < measures; ++j)
    {
        std::vector<int> v(count);
        const auto begin = std::begin(v), end = std::end(v);
        std::generate(begin, end, [&uid, &gen]() { return uid(gen); });
        std::multiset<int> s;

        t.resume();
        for (auto i = 0U; i < count; ++i){ s.insert(v[i]);}
        t.pause();
        multiset_time += t.delta_time();

        t.resume();
        std::sort(begin, end);
        t.pause();
        vector_time += t.delta_time();
    }
    std::cout << "Average vector sorting time equals " << vector_time/measures << " microseconds" << std::endl << //approximately 5500 microseconds
        "Average set sorting time equals " << multiset_time /measures << " microseconds" << std::endl; //more than 25000 microseconds, in other words in 5 times more than vector

	system("pause");
	return EXIT_SUCCESS;
}