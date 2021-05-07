CC=gcc
CCLINK=$(CC)
CFLAGS=-c -fpic -g -Wall -std=c99
OBJ=grades.o
RM=rm -rf *.o libgrades.so

# Link rule
libgrades.so: $(OBJ) liblinked-list.so
	$(CCLINK) -shared $(OBJ) -o libgrades.so -llinked-list -L.

# Compile rule
$(OBJ): grades.c grades.h
	$(CC) $(CFLAGS) grades.c

# Clean rule
clean:
	$(RM)