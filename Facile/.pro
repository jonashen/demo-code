CONFIG += debug               # enables debugging (like the -g flag)
TARGET = debugger               # sets output executable name to debugger
QMAKE_CXXFLAGS += -std=c++11  # enable C++11 libraries
SOURCES -= msort_test.cpp   # Don't compile certain test files
