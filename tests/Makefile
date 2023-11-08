CC = g++ -std=c++11
CXX = cxxtestgen --error-printer
HEADERSDIR = ../code/headers/
OBJDIR = ../code/obj/
BINDIR = ../bin/
HEADERS = $(HEADERSDIR)poly.h 
SRCDIR = ../code/src/
HEADERSTEST = mandatoryUnitTest.h

# le fichier intermédiaire généré par cxxtestgen
CXXTEST = test.cpp 
OBJS= $(OBJDIR)poly.o 
OBJSTEST= $(OBJDIR)test.o 
TARGET = $(BINDIR)test 

$(TARGET): $(OBJSTEST) $(OBJS)
	$(CC) -o $(BINDIR)test $^ -larmadillo

#création du .o à partir des .h pour les HEADERS
$(OBJDIR)%.o: $(SRCDIR)%.cxx $(HEADERSDIR)%.h
	$(CC) -c $< -o $@

# création du fichier cpp à partir du .h
$(CXXTEST): $(HEADERSTEST)
	$(CXX) -o $@ $^

#création du .o pour les cpp générés par cxxtestgen
$(OBJDIR)%.o: %.cpp
	pwd 
	$(CC) -c $< -o $@ -I $(HEADERSDIR)


.PHONY: all clean style

style : 
	astyle -A1 *.cpp *.h
	find . -type f -name '*.orig' -delete

clean : 
	rm -rf $(CXXTEST)
	rm -rf $(OBJDIR)*.o
	rm -rf $(TARGET)
	
