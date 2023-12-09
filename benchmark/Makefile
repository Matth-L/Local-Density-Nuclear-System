CC = g++
CXXFLAGS = -Wextra -std=c++11 -O2
LDFLAGS =
LIBS = -larmadillo
TARGET = ../bin/benchmark
BINDIR = ../bin/
OBJDIR = ../code/obj/
SRCDIR = ../code/src/

.Phony: clean all style 

all: $(TARGET)

$(TARGET): $(OBJDIR)benchmark.o $(OBJDIR)poly.o $(OBJDIR)basis.o 
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)benchmark.o : benchmark.cxx
	$(CC) $(CXXFLAGS) $< -c -o $@

clean : 
	rm -f $(BINDIR)*
	rm -f $(OBJDIR)*
	rm -f *.o
	rm -f benchmark
	rm -f *.orig
	rm -f ../benchmark.csv
	