OBJS = obj/DrAcuLA.o obj/terminal.o obj/slave.o obj/master.o
CC = g++
BFLAGS = -std=c++11 -I .

rebuild:
	make clean
	make all

all: DrAcuLA

DrAcuLA: $(OBJS)
	$(CC) $(BFLAGS) $(OBJS) -o DrAcuLA

obj/DrAcuLA.o: main.cc
	$(CC) $(BFLAGS) -c main.cc -o obj/DrAcuLA.o

obj/terminal.o: helpers/src/terminal.cc helpers/include/terminal.h
	$(CC) $(BFLAGS) -c helpers/src/terminal.cc -o obj/terminal.o

obj/slave.o: wpa_control/src/slave.cc wpa_control/include/slave.h
	$(CC) $(BFLAGS) -c wpa_control/src/slave.cc -o obj/slave.o

obj/master.o: wpa_control/src/master.cc wpa_control/include/master.h
	$(CC) $(BFLAGS) -c wpa_control/src/master.cc -o obj/master.o

clean:
	rm DrAcuLA obj/*
