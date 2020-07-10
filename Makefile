CXX = g++
CXXFLAGS = -W -Wall -std=c++14
TARGET = dp_maching

$(TARGET): dp_maching.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@