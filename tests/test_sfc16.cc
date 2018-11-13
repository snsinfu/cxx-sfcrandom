#include <algorithm>
#include <cmath>
#include <cstdint>
#include <type_traits>

#include <sfc.hpp>

#include <catch.hpp>


TEST_CASE("sfc16 - is a 16-bit random number generator")
{
    CHECK(std::is_same<cxx::sfc16::result_type, std::uint16_t>::value);

    constexpr std::uint16_t min = cxx::sfc16::min();
    constexpr std::uint16_t max = cxx::sfc16::max();

    CHECK(min == 0);
    CHECK(max == 0xffff);
}

TEST_CASE("sfc16 - produces correct sequence with default seed")
{
    cxx::sfc16 engine;

    // RNG_output sfc16 16 0000000000000000 | hexdump -e '/2 "0x%04x "'
    CHECK(engine() == 0x0a64);
    CHECK(engine() == 0x97c6);
    CHECK(engine() == 0x9cf1);
    CHECK(engine() == 0x7e56);
    CHECK(engine() == 0xf4b5);
    CHECK(engine() == 0x047a);
    CHECK(engine() == 0x791c);
    CHECK(engine() == 0x6dc6);
}

TEST_CASE("sfc16 - produces correct sequence with given 64-bit seed")
{
    cxx::sfc16 engine;

    engine.seed64(0xb7c97bb6cb9b60ee);

    // RNG_output sfc16 16 b7c97bb6cb9b60ee | hexdump -e '/2 "0x%04x "'
    CHECK(engine() == 0x6024);
    CHECK(engine() == 0x23cd);
    CHECK(engine() == 0x1367);
    CHECK(engine() == 0xbcda);
    CHECK(engine() == 0x105d);
    CHECK(engine() == 0x8c97);
    CHECK(engine() == 0xeacd);
    CHECK(engine() == 0x5606);
}

TEST_CASE("sfc16 - produces correct sequence with given 16-bit seed")
{
    cxx::sfc16 engine{0x08cb};

    // RNG_output sfc16 16 08cb | hexdump -e '/2 "0x%04x "'
    CHECK(engine() == 0x1034);
    CHECK(engine() == 0x5fc5);
    CHECK(engine() == 0x77eb);
    CHECK(engine() == 0x6e2b);
    CHECK(engine() == 0x3d6a);
    CHECK(engine() == 0x9bc3);
    CHECK(engine() == 0xe8c4);
    CHECK(engine() == 0xfca0);
}

TEST_CASE("sfc16 - produces correct sequence with given seed sequence")
{
    struct seed_seq
    {
        void generate(std::uint32_t* rb, std::uint32_t* re)
        {
            // a = 0xb5c6
            // b = 0x4862
            *rb++ = 0x4862b5c6;

            // c = 0x332a
            *rb++ = 0x332a;

            CHECK(rb == re);
        }
    };

    seed_seq seed;
    cxx::sfc16 engine{seed};

    CHECK(engine() == 0xcded);
    CHECK(engine() == 0x5ae9);
    CHECK(engine() == 0x3111);
    CHECK(engine() == 0xa4a4);
}

TEST_CASE("sfc16 - produces uniformly distributed numbers")
{
    using engine_type = cxx::sfc16;
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
