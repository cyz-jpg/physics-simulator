
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = simulator
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
