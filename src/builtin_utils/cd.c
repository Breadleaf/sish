#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "../global.h"
#include "cd.h"

void change_working_directory(char *relative_path) {
	debug_log("CALL: change_working_directory(%s)\n", relative_path);

	char *path_to_append = relative_path;
	
	// if empty string is passed, assume user is running `cd`
	if (strcmp(path_to_append, "\0") == 0) {
		path_to_append = getenv("HOME");
		if (path_to_append == NULL) {
			(void)printf("error: getenv(HOME) failed!\n");
			exit(1);
		}
		debug_log("getenv(HOME) = '%s'\n", path_to_append);

		if (chdir(path_to_append) != 0) {
			(void)printf(
				"error: chdir(%s) failed!\n",
				path_to_append
			);
			(void)printf("errno: %d\n", errno);
			exit(1);
		}

		if (setenv("PWD", path_to_append, WRITE_ENVVAR) != 0) {
			(void)printf(
				"error: setenv(PWD, %s) failed!\n",\
				path_to_append
			);
			(void)printf("errno: %d\n", errno);
			exit(1);
		}
	} else {
		/*
		 Hacky `cd ..` and `cd [RELATIVE PATH]` solution

		 cd /home/user/my/path/../ is the same as /home/user/my/

		 by treating ../ as a relative path, we dont need to do some
		 parse/lex code
		 */

		char *cwd = getcwd(NULL, 0);
		if (cwd == NULL) {
			(void)printf("error: getcwd(NULL, 0) failed!\n");
			(void)printf("errno: %d\n", errno);
			exit(1);
		}

		size_t cwd_length = strlen(cwd);
		size_t path_to_append_len = strlen(path_to_append);
		// +1 for '/' and +1 for '\0' = +2
		size_t total_len = cwd_length + path_to_append_len + 2;

		char *aggregate_string = malloc(total_len * sizeof(char));
		if (aggregate_string == NULL) {
			(void)printf("error: malloc() failed!\n");
			(void)printf("errno: %d\n", errno);
			free(cwd);
			exit(1);
		}

		// PATH(a//b) is the same as PATH(a/b)
		// reference above comment about +2
		snprintf(aggregate_string, total_len, "%s/%s", cwd, path_to_append);

		if (chdir(aggregate_string) != 0) {
			(void)printf(
				"error: chdir(%s) failed!\n",
				aggregate_string
			);
			(void)printf("errno: %d\n", errno);
			free(cwd);
			free(aggregate_string);
			exit(1);
		}

		if (setenv("PWD", aggregate_string, WRITE_ENVVAR) != 0) {
			(void)printf(
				"error: setenv(PWD, %s) failed!\n",
				aggregate_string
			);
			(void)printf("errno: %d\n", errno);
			free(cwd);
			free(aggregate_string);
			exit(1);
		}

		free(cwd);
		free(aggregate_string);
	}

	debug_log("EXIT: change_working_directory()\n");
}
