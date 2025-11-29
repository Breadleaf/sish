#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
	char *string = "Hello, World!\n";
	ssize_t written = write(STDIN_FILENO, string, strlen(string));
	return written;
}
