CXXFLAGS=-I../../src -I/usr/include/mpi -O0 -g
LDFLAGS=-L../../src -lmpi_cxx -lmpi -lhiss
CXX=g++

all: test_parts

test_parts: parts.o ../../src/libhiss.a
	$(CXX) -o $@ $^ $(LDFLAGS)
