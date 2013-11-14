#include "myio.h"

int main() {

	printf("%s\n", get_file_name("//sa/path////"));
	printf("%s\n", get_dest_record_path("abc", "127.0.0.1"));
	write_into_record_file("abc", "127.0.0.1", "hello world");
}
