# Small fast random number generator for C++

![C++11][cxx-badge]
[![Build Status][travis-badge]][travis-url]
[![Boost License][license-badge]][license-url]

[PractRand][practrand]'s sfc16/32/64 random number generators adapted to C++11.

```c++
#include <iostream>
#include <random>
#include <sfc.hpp>

int main()
{
    cxx::sfc64 engine;
    std::normal_distribution<double> normal;

    double x = normal(engine);
    double y = normal(engine);

    std::cout << x << '\t' << y << '\n';
}
```

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[license-badge]: https://img.shields.io/badge/license-Boost-blue.svg
[license-url]: https://raw.githubusercontent.com/snsinfu/cxx-sfcrandom/master/LICENSE.txt
[travis-badge]: https://travis-ci.org/snsinfu/cxx-sfcrandom.svg?branch=master
[travis-url]: https://travis-ci.org/snsinfu/cxx-sfcrandom
[practrand]: http://pracrand.sourceforge.net/

## Usage

Download and include [sfc.hpp][header]. It exports three random number engines:

- `cxx::sfc16`
- `cxx::sfc32`
- `cxx::sfc64`

sfc64 is the recommended one. It's a small, fast and statistically good engine.
You can use it as a drop-in replacement for the standard engines like `std::mt19937`.

[header]: https://raw.githubusercontent.com/snsinfu/cxx-sfcrandom/master/include/sfc.hpp

## Testing

```console
git clone https://github.com/snsinfu/cxx-sfcrandom
cd cxx-sfcrandom/tests
make
```

## License

Boost Software License, Version 1.0.
