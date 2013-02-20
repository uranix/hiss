TARGET=libhiss.a

CXXFLAGS=-O0 -g -I/usr/include/mpi
CXX=g++
AR=ar rcs
RM=rm -f

SRC=coloring.cpp mpi_impl.cpp portrait.cpp sparsecomm.cpp
OBJS=$(SRC:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(AR) $@ $^

clean: 
	$(RM) $(OBJS) $(TARGET)
