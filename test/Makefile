# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = googletest/googletest

# TinySTL test header files.
TEST_HEADERS = ../include/*.hpp ../include/detail/*.hpp ../include/algorithm/*.hpp

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
ODIR = obj

TEST_SRC = $(wildcard *.cpp)

TESTS_OBJ = $(patsubst %.cpp,$(ODIR)/%.o,$(TEST_SRC))

TESTS = $(patsubst %.o,%,$(TESTS_OBJ))

TESTALL = obj/testAll

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11 -I../include

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
			$(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.
.PHONY: all test clean

all : $(TESTS) $(TESTALL)

test : $(TESTALL)
	$(TESTALL)

clean :
	rm -f $(ODIR)/*

# Build googletest lib: libgtest.a libgtest_main.a
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

obj/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c -o obj/gtest-all.o \
            $(GTEST_DIR)/src/gtest-all.cc

obj/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c -o obj/gtest_main.o \
            $(GTEST_DIR)/src/gtest_main.cc

obj/libgtest_main.a : obj/gtest-all.o obj/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Build unittest
$(ODIR)/%.o: %.cpp $(TEST_HEADERS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(ODIR)/%: $(ODIR)/%.o obj/libgtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread -o $@ $< obj/libgtest_main.a

$(TESTALL) : $(TESTS_OBJ) obj/libgtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
