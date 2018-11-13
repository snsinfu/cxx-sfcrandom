# Small fast random number generator for C++

![C++11][cxx-badge]
[![Build Status][travis-badge]][travis-url]
[![Boost License][license-badge]][license-url]

[PractRand][practrand]'s sfc16/32/64 random number generators adapted to C++11.
[Download][header].

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
[header]: https://raw.githubusercontent.com/snsinfu/cxx-sfcrandom/master/include/sfc.hpp
[practrand]: http://pracrand.sourceforge.net/

## Testing

```console
git clone https://github.com/snsinfu/cxx-sfcrandom
cd cxx-sfcrandom/tests
make
```

## License

Boost Software License, Version 1.0.
