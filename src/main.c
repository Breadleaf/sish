#include <stdio.h>

#include "builtin_utils/cd.h"
#include "global.h"

int main() {
	print_working_directory();
	// for testing failure with errno
	// change_working_directory("srs");
	// print_working_directory();
	change_working_directory("src");
	print_working_directory();
	change_working_directory("..");
	print_working_directory();
	change_working_directory("\0");
	print_working_directory();
}
