CXX = g++
CXXFLAGS = -Wall -std=c++17 -I/home/mryvkin/SDL/include
LDFLAGS = /home/mryvkin/SDL/build-static/libSDL3.a -lm -ldl -lpthread
TARGET = Chess
SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
