CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = main
SRCS = main.cpp Request.cpp RequestQueue.cpp WebServer.cpp LoadBalancer.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
