CC=gcc
LIBRARY=$(shell pwd)/../library/
INCLUDE=$(shell pwd)/../include/

FLAGS=-fpic -shared `pkg-config --libs --cflags gtk+-2.0`
LIB=libdatastructure.so

CP=cp
DEFAULT=header

all: $(LIB) $(DEFAULT)

source=basetype.c

header=basetype.h

libdatastructure.so: $(source)
	gcc $(FLAGS) $(source) -o $(LIBRARY)/libdatastructure.so 

header: $(header)
	$(CP) $(header) $(INCLUDE)

clean:
	rm -rf *.o
