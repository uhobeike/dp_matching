CXX = g++
CXXFLAGS = -W -Wall -std=c++11
TARGET = main

$(TARGET): dp_maching.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@