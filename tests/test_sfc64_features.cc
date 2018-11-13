#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>

#include <sfc.hpp>

#include <catch.hpp>


TEST_CASE("sfc64 - is default constructible")
{
    cxx::sfc64 engine;
}

TEST_CASE("sfc64 - is copy constructible and copy assignable")
{
    cxx::sfc64 engine;
    cxx::sfc64 copy = engine;
    copy = engine;
}

TEST_CASE("sfc64 - is equality comparable")
{
    cxx::sfc64 e1{1234};
    cxx::sfc64 e2{1234};
    cxx::sfc64 e3{4321};

    CHECK(e1 == e2);
    CHECK(e2 == e1);

    CHECK(e1 != e3);
    CHECK(e3 != e1);
}

TEST_CASE("sfc64 - is equality comparable after generations")
{
    cxx::sfc64 e1{1234};
    cxx::sfc64 e2{1234};
    cxx::sfc64 e3{4321};

    e1.discard(100);
    e2.discard(100);
    e3.discard(100);

    CHECK(e1 == e2);
    CHECK(e2 == e1);

    CHECK(e1 != e3);
    CHECK(e3 != e1);
}

TEST_CASE("sfc64::seed - reseeds the engine")
{
    std::uint64_t seed = 0xca6933fda106ba4c;

    cxx::sfc64 expected{seed};
    cxx::sfc64 reseeded;
    reseeded.seed(seed);

    CHECK(reseeded == expected);
}

TEST_CASE("sfc64::operator() - generates numbers within the range")
{
    cxx::sfc64 engine;

    std::uint64_t num = engine();

    CHECK(num >= engine.min());
    CHECK(num <= engine.max());
}

TEST_CASE("sfc64::discard - advances engine state")
{
    cxx::sfc64 engine;
    cxx::sfc64 other{engine};

    engine.discard(100);

    for (int i = 0; i < 100; i++) {
        other();
    }

    CHECK(engine() == other());
    CHECK(engine() == other());
    CHECK(engine() == other());

}

TEST_CASE("sfc64 - is serializable and deserializable")
{
    cxx::sfc64 engine{1234};

    engine.discard(100);

    std::stringstream str;
    str << engine;

    cxx::sfc64 restored;
    str >> restored;

    CHECK(engine == restored);
}

TEST_CASE("sfc64 - is stably serializable")
{
    cxx::sfc64 engine{1234};

    // hex manipulator does not change serialization
    std::stringstream str1;
    std::stringstream str2;

    str1 << engine;
    str2 << std::hex << engine;

    CHECK(str1.str() == str2.str());
}
