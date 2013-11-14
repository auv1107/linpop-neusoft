

DEFAULT=default
all: $(DEFAULT)

test: test.c
	gcc -o test test.c -Llibrary -lmyio -Iinclude

default:
	make -C data_structure
	make -C ui_module
	make -C io_module
	make -C network_module
	make clean -C ui_module
	make Login -C ui_module

clean:
	make clean -C data_structure
	make clean -C ui_module
	make clean -C io_module
	make clean -C network_module
