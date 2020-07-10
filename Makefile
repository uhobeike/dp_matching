CXX = g++
CXXFLAGS = -W -Wall -std=c++14
TARGET = main

$(TARGET): dp_maching.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@