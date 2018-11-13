OPTFLAGS = \
  -O2 \
  -flto \
  -mtune=native

INCLUDES = \
  -I ../include

CXXFLAGS = \
  -std=c++11 \
  -pedantic \
  -Wall \
  -Wextra \
  -Wconversion \
  -Wsign-conversion \
  -Wshadow \
  $(OPTFLAGS) \
  $(INCLUDES)

PRODUCTS = \
  bench_batch_generation


.PHONY: all clean

all: $(PRODUCTS)
	@:

clean:
	rm -f $(PRODUCTS)
