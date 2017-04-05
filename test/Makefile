# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = googletest/googletest

# TinySTL test header files.
TEST_HEADERS = ./*.hpp ../*.hpp ../detail/*.hpp

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
			$(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.
all : testMain

test : testMain
	./testMain

clean :
	rm -f testMain libgtest.a *.o

# Build libgtest.a
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

libgtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

# Build unittest
testMain.o : testMain.cpp $(TEST_HEADERS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) -I.. $(CXXFLAGS) -c testMain.cpp

testMain : testMain.o libgtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
