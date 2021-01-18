CXX = g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O3 -DNDEBUG

LFLAGS = -L../src  -lckv
IFLAGS = -I../src

CXXFLAGS += $(IFLAGS)

SRC = test_ckv.cpp
BIN = test_ckv.out

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LFLAGS)

.PHONY: clean

clean:
	rm $(BIN)
