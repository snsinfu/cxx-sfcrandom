#include <cstdint>
#include <type_traits>

#include <sfc.hpp>

#include <catch.hpp>


TEST_CASE("sfc32 - is a 32-bit random number generator")
{
    CHECK(std::is_same<cxx::sfc32::result_type, std::uint32_t>::value);

    constexpr std::uint32_t min = cxx::sfc32::min();
    constexpr std::uint32_t max = cxx::sfc32::max();

    CHECK(min == 0);
    CHECK(max == 0xffffffff);
}

TEST_CASE("sfc32 - produces correct sequence with default seed")
{
    cxx::sfc32 engine;

    // RNG_output sfc32 32 0000000000000000
    CHECK(engine() == 0x514676c3);
    CHECK(engine() == 0x08a809df);
    CHECK(engine() == 0x30349d2b);
    CHECK(engine() == 0xfb52c520);
    CHECK(engine() == 0x38802be1);
    CHECK(engine() == 0x948279e6);
    CHECK(engine() == 0xec4bf1d9);
    CHECK(engine() == 0x7cb0a909);
}

TEST_CASE("sfc32 - produces correct sequence with given 64-bit seed")
{
    cxx::sfc32 engine;

    engine.seed64(0x1160843560a847b1);

    // RNG_output sfc32 32 1160843560a847b1
    CHECK(engine() == 0xf9ea2944);
    CHECK(engine() == 0xb8de4818);
    CHECK(engine() == 0xda3f8ef3);
    CHECK(engine() == 0xdfe59c72);
    CHECK(engine() == 0xda840bc6);
    CHECK(engine() == 0x93eb481b);
    CHECK(engine() == 0x80ff0e2d);
    CHECK(engine() == 0x47a441a1);
}

TEST_CASE("sfc32 - produces correct sequence with given 32-bit seed")
{
    cxx::sfc32 engine{0x07f04ebf};

    // RNG_output sfc32 32 07f04ebf
    CHECK(engine() == 0x7a00facc);
    CHECK(engine() == 0x5a97b427);
    CHECK(engine() == 0xb5e3cb93);
    CHECK(engine() == 0x68fcdf1f);
    CHECK(engine() == 0xf07040c9);
    CHECK(engine() == 0x9aad485b);
    CHECK(engine() == 0xbfba12d8);
    CHECK(engine() == 0xd953c25b);
}

TEST_CASE("sfc32 - produces uniformly distributed numbers")
{
    using engine_type = cxx::sfc32;
    using word_type = engine_type::result_type;

    engine_type engine;

    // Sampling
    int const sample_count = 5000;

    std::vector<word_type> samples;
    std::generate_n(std::back_inserter(samples), sample_count, [&] {
        return engine();
    });
    std::sort(samples.begin(), samples.end());

    // KS test (two-sided, 1%)
    double const critical_value = 1.63 / std::sqrt(sample_count);

    double D = 0;
    int rank = 0;

    for (word_type x : samples) {
        rank++;

        double const sample_cdf = rank / double(sample_count);
        double const uniform_cdf = double(x) / double(word_type(-1));

        D = std::max(D, std::fabs(sample_cdf - uniform_cdf));
    }

    CHECK(D < critical_value);
}
