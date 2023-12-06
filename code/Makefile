CC = g++
CXXFLAGS = -Wextra -std=c++11 -O2
LDFLAGS =
LIBS = -larmadillo
TARGET = ../bin/out
BINDIR = ../bin/
OBJDIR = obj/
SRCDIR = src/
HDIR = headers/
HEADERS = $(HDIR)poly.h $(HDIR)basis.h
OBJS = $(OBJDIR)poly.o $(OBJDIR)basis.o $(OBJDIR)main.o

.Phony: clean all style 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)%.o: $(SRCDIR)%.cxx $(HEADERS)
	$(CC) $(CXXFLAGS) $< -c -o $@

clean:
	rm -f $(BINDIR)*
	rm -f $(OBJS)
	rm resultat.png

style : 
	astyle -A1 --recursive *.cxx *.h
	find . -type f -name '*.orig' -delete
