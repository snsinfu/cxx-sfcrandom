#include <cstdint>
#include <random>

#include <sfc.hpp>

#include <catch.hpp>


TEST_CASE("sfc16 works with independent_bits_engine")
{
    std::seed_seq seed{1, 2, 3, 4};
    std::independent_bits_engine<cxx::sfc16, 52, std::uint64_t> engine{seed};

    constexpr auto upper_bound = std::uint64_t(1) << 52;

    CHECK(engine() < upper_bound);
    CHECK(engine() < upper_bound);
    CHECK(engine() < upper_bound);
}

TEST_CASE("sfc32 works with independent_bits_engine")
{
    std::seed_seq seed{1, 2, 3, 4};
    std::independent_bits_engine<cxx::sfc32, 52, std::uint64_t> engine{seed};

    constexpr auto upper_bound = std::uint64_t(1) << 52;

    CHECK(engine() < upper_bound);
    CHECK(engine() < upper_bound);
    CHECK(engine() < upper_bound);
}

TEST_CASE("sfc64 works with independent_bits_engine")
{
    std::seed_seq seed{1, 2, 3, 4};
    std::independent_bits_engine<cxx::sfc64, 52, std::uint64_t> engine{seed};

    constexpr auto upper_bound = std::uint64_t(1) << 52;

    CHECK(engine() < upper_bound);
    CHECK(engine() < upper_bound);
    CHECK(engine() < upper_bound);
}

