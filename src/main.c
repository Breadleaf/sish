#include "builtin_utils/cd.h"

int main() {
	change_working_directory("srs");
	print_working_directory();
	change_working_directory("..");
	print_working_directory();
	change_working_directory("\0");
	print_working_directory();
}
