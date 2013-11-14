CC=gcc
LIBRARY=$(shell pwd)/../library/
INCLUDE=$(shell pwd)/../include/

FLAGS=-fpic -shared `pkg-config --libs --cflags gtk+-2.0`
LIB=libmyio.so

CP=cp
DEFAULT=header

all: $(LIB) $(DEFAULT)

source=myio.c \
	cls.c \
	getip.c\
	writelog.c

header=myio.h \
	cls.h\
	getip.h \
	writelog.h

libmyio.so: $(source)
	gcc $(FLAGS) $(source) -o $(LIBRARY)/libmyio.so 

header: $(header)
	$(CP) $(header) $(INCLUDE)

clean:
	rm -rf *.o
