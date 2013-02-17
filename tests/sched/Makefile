CXXFLAGS=-I../../src
CXX=mpicxx

all: main.cpp ../../src/mpi_impl.cpp ../../src/coloring.cpp
	$(CXX) $(CXXFLAGS) -o test_sched $^
