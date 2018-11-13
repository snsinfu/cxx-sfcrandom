#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

#include <sfc.hpp>


struct benchmark_result
{
    double time;
    double mean;
};

std::ostream& operator<<(std::ostream& os, benchmark_result const& result)
{
    return os << result.time * 1e9 << " ns/gen\t" << result.mean;
}

template<typename Dist, typename RNG>
__attribute__((noinline))
benchmark_result run_benchmark(long count, Dist dist, RNG random)
{
    double sum = 0;

    using clock = std::chrono::steady_clock;
    auto const start = clock::now();

    for (long i = 0; i < count; i++) {
        sum += dist(random);
    }

    auto const end = clock::now();
    auto const time = std::chrono::duration_cast<std::chrono::duration<double>>(
        end - start
    );

    benchmark_result result;
    result.time = time.count() / count;
    result.mean = sum / count;
    return result;
}

int main()
{
    constexpr long count = 100000000;

    std::uniform_real_distribution<double> unoform_real;
    std::cout << "Uniform real\n";
    std::cout << "mt \t" << run_benchmark(count, unoform_real, std::mt19937_64{}) << '\n';
    std::cout << "sfc\t" << run_benchmark(count, unoform_real, cxx::sfc64{}) << '\n';
    std::cout << '\n';

    std::uniform_int_distribution<int> uniform_int{-10, 10};
    std::cout << "Uniform int\n";
    std::cout << "mt \t" << run_benchmark(count, uniform_int, std::mt19937_64{}) << '\n';
    std::cout << "sfc\t" << run_benchmark(count, uniform_int, cxx::sfc64{}) << '\n';
    std::cout << '\n';

    std::uniform_int_distribution<std::uint64_t> uniform_bits;
    std::cout << "Uniform bits\n";
    std::cout << "mt \t" << run_benchmark(count, uniform_bits, std::mt19937_64{}) << '\n';
    std::cout << "sfc\t" << run_benchmark(count, uniform_bits, cxx::sfc64{}) << '\n';
    std::cout << '\n';

    std::normal_distribution<double> normal;
    std::cout << "Normal\n";
    std::cout << "mt \t" << run_benchmark(count, normal, std::mt19937_64{}) << '\n';
    std::cout << "sfc\t" << run_benchmark(count, normal, cxx::sfc64{}) << '\n';
}
