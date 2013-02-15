CXX=g++
CFLAGS=-O3 -g -I../src

all: test_coloring

test_coloring : driver.cpp ../src/coloring.cpp
	$(CXX) $(CFLAGS) -o $@ $^

graphs : 
	for i in *.gv; do j=`echo $$i | sed 's/\.gv/.png/'`; twopi $$i -Tpng -o $$j; done
