OBJS = fanalysis.o main.o
CPPFLAGS = -std=c++11
PROG = fanalysis
CC = g++
all : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(CPPFLAGS)
fanalysis.o : fanalysis.h fanalysis.cpp
	$(CC) -c fanalysis.cpp $(CPPFLAGS)
main.o : main.cpp
	$(CC) -c main.cpp $(CPPFLAGS)
