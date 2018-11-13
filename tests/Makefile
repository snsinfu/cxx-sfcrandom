OPTFLAGS = \
  -O2

DBGFLAGS = \
  -g \
  -fsanitize=address

INCLUDES = \
  -isystem include \
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
  $(DBGFLAGS) \
  $(INCLUDES)

OBJECTS = \
  main.o \
  test_sfc16.o \
  test_sfc32.o \
  test_sfc64.o \
  test_sfc64_features.o \
  integration/test_independent_bits_engine.o \
  integration/test_uniform_int_distribution.o \
  integration/test_uniform_real_distribution.o

ARTIFACTS = \
  $(OBJECTS) \
  main \
  *.dSYM


.PHONY: test clean

test: main
	@./main

clean:
	rm -rf $(ARTIFACTS)

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

test_sfc16.o: ../include/sfc.hpp
test_sfc32.o: ../include/sfc.hpp
test_sfc64.o: ../include/sfc.hpp
test_sfc64_features.o: ../include/sfc.hpp
integration/test_independent_bits_engine.o: ../include/sfc.hpp
integration/test_uniform_int_distribution.o: ../include/sfc.hpp
integration/test_uniform_real_distribution.o: ../include/sfc.hpp
