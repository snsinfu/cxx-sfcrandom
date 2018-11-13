#include <algorithm>
#include <cmath>
#include <cstdint>
#include <type_traits>

#include <sfc.hpp>

#include <catch.hpp>


TEST_CASE("sfc64 - is a 64-bit random number generator")
{
    CHECK(std::is_same<cxx::sfc64::result_type, std::uint64_t>::value);

    constexpr std::uint64_t min = cxx::sfc64::min();
    constexpr std::uint64_t max = cxx::sfc64::max();

    CHECK(min == 0);
    CHECK(max == 0xffffffffffffffff);
}

TEST_CASE("sfc64 - produces correct sequence with default seed")
{
    cxx::sfc64 engine;

    // RNG_output sfc64 64 0000000000000000 | hexdump -e '/8 "0x%016x"'
    CHECK(engine() == 0x3acfa029e3cc6041);
    CHECK(engine() == 0xf5b6515bf2ee419c);
    CHECK(engine() == 0x1259635894a29b61);
    CHECK(engine() == 0x0b6ae75395f8ebd6);
    CHECK(engine() == 0x225622285ce302e2);
    CHECK(engine() == 0x520d28611395cb21);
    CHECK(engine() == 0xdb909c818901599d);
    CHECK(engine() == 0x8ffd195365216f57);
}

TEST_CASE("sfc64 - produces correct sequence with given 64-bit seed")
{
    cxx::sfc64 engine{0x87bc440d3f300ce1};

    // RNG_output sfc64 64 87bc440d3f300ce1 | hexdump -e '/8 "0x%016x"'
    CHECK(engine() == 0x145ad72a58ef02af);
    CHECK(engine() == 0x794b77692bb3ba6c);
    CHECK(engine() == 0xb0b276c99fd67b27);
    CHECK(engine() == 0x818bd0f2b8956c45);
    CHECK(engine() == 0xade42a16cb2bdab7);
    CHECK(engine() == 0xf934d7fc2d39ed86);
    CHECK(engine() == 0xb989400313436b9d);
    CHECK(engine() == 0x3910b9dc0af18aa0);
}

TEST_CASE("sfc64 - produces correct sequence with given seed sequence")
{
    struct seed_seq
    {
        void generate(std::uint32_t* rb, std::uint32_t* re)
        {
            // a = 0x1a0dfbde3b0fe18c
            *rb++ = 0x1a0dfbde;
            *rb++ = 0x3b0fe18c;

            // b = 0xa4f4562c68322d39
            *rb++ = 0xa4f4562c;
            *rb++ = 0x68322d39;

            // c = 0xfef0d87e2f216bc1
            *rb++ = 0xfef0d87e;
            *rb++ = 0x2f216bc1;

            CHECK(rb == re);
        }
    };

    seed_seq seed;
    cxx::sfc64 engine{seed};

    CHECK(engine() == 0x62d88ea4f8e52534);
    CHECK(engine() == 0xed8152736a1e06d8);
    CHECK(engine() == 0xab437fa78f703b0c);
    CHECK(engine() == 0xa4a705dd41bc312f);
}

TEST_CASE("sfc64 - produces uniformly distributed numbers")
{
    using engine_type = cxx::sfc64;
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
