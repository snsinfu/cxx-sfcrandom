#include <cstdint>
#include <random>

#include <sfc.hpp>

#include <catch.hpp>


TEST_CASE("sfc16 works with uniform_int_distribution")
{
    std::seed_seq seed{1, 2, 3, 4};
    cxx::sfc16 engine{seed};

    constexpr std::int64_t min = -123456789012;
    constexpr std::int64_t max = 345678901234;

    std::uniform_int_distribution<std::int64_t> dist{min, max};

    CHECK(dist(engine) >= min);
    CHECK(dist(engine) <= max);
}

TEST_CASE("sfc32 works with uniform_int_distribution")
{
    std::seed_seq seed{1, 2, 3, 4};
    cxx::sfc32 engine{seed};

    constexpr std::int64_t min = -123456789012;
    constexpr std::int64_t max = 345678901234;

    std::uniform_int_distribution<std::int64_t> dist{min, max};

    CHECK(dist(engine) >= min);
    CHECK(dist(engine) <= max);
}

TEST_CASE("sfc64 works with uniform_int_distribution")
{
    std::seed_seq seed{1, 2, 3, 4};
    cxx::sfc64 engine{seed};

    constexpr std::int64_t min = -123456789012;
    constexpr std::int64_t max = 345678901234;

    std::uniform_int_distribution<std::int64_t> dist{min, max};

    CHECK(dist(engine) >= min);
    CHECK(dist(engine) <= max);
}
