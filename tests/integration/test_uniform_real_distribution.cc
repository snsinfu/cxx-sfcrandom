#include <cstdint>
#include <random>

#include <sfc.hpp>

#include <catch.hpp>


TEST_CASE("sfc16 works with uniform_real_distribution")
{
    std::seed_seq seed{1, 2, 3, 4};
    cxx::sfc16 engine{seed};

    std::uniform_real_distribution<double> dist;

    CHECK(dist(engine) >= 0);
    CHECK(dist(engine) < 1);
}

TEST_CASE("sfc32 works with uniform_real_distribution")
{
    std::seed_seq seed{1, 2, 3, 4};
    cxx::sfc32 engine{seed};

    std::uniform_real_distribution<double> dist;

    CHECK(dist(engine) >= 0);
    CHECK(dist(engine) < 1);
}

TEST_CASE("sfc64 works with uniform_real_distribution")
{
    std::seed_seq seed{1, 2, 3, 4};
    cxx::sfc64 engine{seed};

    std::uniform_real_distribution<double> dist;

    CHECK(dist(engine) >= 0);
    CHECK(dist(engine) < 1);
}
