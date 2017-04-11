ODIR = obj

BENCH_SRC = $(wildcard *.cpp)

BENCH_OBJ = $(patsubst %.cpp,$(ODIR)/%.o,$(BENCH_SRC))

BENCHS = $(patsubst %.o,%,$(BENCH_OBJ))

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -std=c++11 -I. -I../include

.PHONY: bench clean

bench : $(BENCHS)

clean :
	rm -f $(ODIR)/*

# Build benchmark programe
$(ODIR)/%.o: %.cpp Profiler.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ODIR)/%: $(ODIR)/%.o
	$(CXX) $(CXXFLAGS) -o $@ $<
