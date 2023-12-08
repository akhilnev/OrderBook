CXX = g++
CXXFLAGS = -std=c++11
SRC = orderbook.cpp
TARGET = orderbook

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
