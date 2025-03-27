CXX = g++
CXXFLAGS = -I$(PWD)/include  # Absolute include path

OBJS = src/main.o src/deck.o src/handconverter.o src/handevaluator.o src/pcg.o
SRCS = src/main.cpp src/deck.cpp src/handconverter.cpp src/handevaluator.cpp src/pcg.cpp

all: main

main: $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)  # Apply CXXFLAGS to object file compilation

clean:
	rm -f $(OBJS) main
