CC=gcc
LIBRARY=$(shell pwd)/../library/
INCLUDE=$(shell pwd)/../include/

FLAGS=-fpic -shared -g `pkg-config --libs --cflags gtk+-2.0` -L$(LIBRARY) -ldatastructure -I$(INCLUDE) 
LIB=libgtkapi.so

CP=cp
DEFAULT=header

all: $(LIB) $(DEFAULT)

Login: Login.c mainwin.c
	gcc -o Login Login.c `pkg-config --libs --cflags gtk+-2.0` -L$(LIBRARY) -ldatastructure -lnetworkapi -lmyio -lgtkapi  -I$(INCLUDE) -g

source=gtkapi.c

header=gtkapi.h \
	chat.h

libgtkapi.so: $(source)
	gcc $(FLAGS) $(source) -o $(LIBRARY)/libgtkapi.so 

header: $(header)
	$(CP) $(header) $(INCLUDE)

clean:
	rm -rf Login
