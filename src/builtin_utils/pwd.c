#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "../global.h"
#include "pwd.h"

void print_working_directory() {
	debug_log("CALL: print_working_directory()\n");

	char *cwd = getcwd(NULL, 0);
	if (cwd == NULL) {
		(void)printf("error: getcwd(NULL, 0) failed!\n");
		(void)printf("errno: %d\n", errno);
		exit(1);
	}

	(void)printf("CWD: '%s'\n", cwd);

	free(cwd);

	debug_log("EXIT: print_working_directory()\n");
}
