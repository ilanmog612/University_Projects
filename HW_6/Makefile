#!/bin/bash
CXX=g++
CXXLINK=$(CXX)
CXXFLAGS= -c -fpic -g -Wall -std=c++11
EXEC= firewall.exe
OBJ= main.o
LIBS= libfirewall.so libinput.so
LIBS_O = string.o field.o port.o ip.o
RM= rm -rf *.o *.exe libfirewall.so

# EXE rule
$(EXEC): $(OBJ) ${LIBS} 
	$(CXX) -g -Wall -std=c++11  $(OBJ) -o $(EXEC) -lfirewall -linput -L.

# Link rule
libfirewall.so: ${LIBS_O} 
	$(CXX) -g -Wall -std=c++11 -shared ${LIBS_O} -o libfirewall.so -L.

# Compile rule
string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) string.cpp

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) field.cpp

port.o: port.cpp port.h field.h
	$(CXX) $(CXXFLAGS) port.cpp

ip.o: ip.cpp ip.h field.h
	$(CXX) $(CXXFLAGS) ip.cpp

main.o: main.cpp port.h ip.h input.h string.h field.h
	$(CXX) $(CXXFLAGS) main.cpp		

# Clean rule
clean:
	$(RM)