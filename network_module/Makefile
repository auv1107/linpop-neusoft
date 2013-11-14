LIBRARY=$(shell pwd)/../library/
INCLUDE=$(shell pwd)/../include/
CC=gcc
FLAGS=-fpic -shared -lpthread -g -L$(LIBRARY) -ldatastructure -lmyio -lgtkapi -I$(INCLUDE) `pkg-config --libs --cflags gtk+-2.0`

source=networkmoduleinit.c \
		packet.c \
		networkapi.c \

header=networkapi.h \
	packet.h \
	networkmoduleinit.h \

LIB=libnetworkapi.so
DEFAULT=header
CP=cp

all: $(LIB) $(DEFAULT)

libnetworkapi.so: $(source) 
	$(CC) $(FLAGS) $(source) -o $(LIBRARY)/libnetworkapi.so

header: $(header)
	cp $(header) $(INCLUDE)

clean:
	rm -rf *.o 
