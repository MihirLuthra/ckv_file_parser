CXX = g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
LIB = libckv.so

.PHONY: all clean test debug release

all: debug

debug: CXXFLAGS += -g
debug: $(LIB)

release: CXXFLAGS += -O3 -DNDEBUG
release: $(LIB)

SRCS = ckv.cpp
OBJS = $(SRCS:%.cpp=%.o)

ckv.o : ckv.cpp ckv.hpp

$(OBJS):
	$(CXX) $(CXXFLAGS) -fPIC -c $<

$(LIB): $(OBJS)
	$(CXX) $(CXXFLAGS) -fPIC -shared -o $@ $(OBJS)

clean:
	rm *.o $(LIB)
