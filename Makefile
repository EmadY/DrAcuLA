OBJS = obj/DrAcuLA.o obj/terminal.o
CC = g++
BFLAGS = -std=c++11 -I .

all: DrAcuLA

DrAcuLA: $(OBJS)
	$(CC) $(BFLAGS) $(OBJS) -o DrAcuLA

obj/DrAcuLA.o: main.cc
	$(CC) $(BFLAGS) -c main.cc -o obj/DrAcuLA.o

obj/terminal.o: helpers/src/terminal.cc helpers/include/terminal.h
	$(CC) $(BFLAGS) -c helpers/src/terminal.cc -o obj/terminal.o

clean:
	rm DrAcuLA obj/*
