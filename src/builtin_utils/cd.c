#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "../global.h"

void change_working_directory(char *relative_path) {
	if (DEBUG_MODE) {
		(void)printf(
			"CALL: change_working_directory(%s)\n",
			relative_path
		);
	}

	char *path_to_append = relative_path;
	
	if (strcmp(path_to_append, "\0") == 0) {
		path_to_append = getenv("HOME");
		if (path_to_append == NULL) {
			(void)printf("error: getenv() failed!\n");
			exit(1);
		}
		if (DEBUG_MODE) {
			(void)printf("getenv(HOME) = '%s'\n", path_to_append);
		}

		if (chdir(path_to_append) != 0) {
			(void)printf("error: chdir() failed!\n");
			(void)printf("errno: %d\n", errno);
			exit(1);
		}

		if (setenv("PWD", path_to_append, WRITE_ENVVAR) != 0) {
			(void)printf("error: setenv() failed!\n");
			(void)printf("errno: %d\n", errno);
			exit(1);
		}
	} else {
		char cwd[MAX_PATH_SIZE];
		if (getcwd(cwd, MAX_PATH_SIZE) == NULL) {
			(void)printf("error: getcwd() failed!\n");
			(void)printf("errno: %d\n", errno);
			exit(1);
		}

		size_t cwd_length = strlen(cwd);
		size_t path_to_append_len = strlen(path_to_append);
		size_t total_len = cwd_length + path_to_append_len + 2;

		if (cwd[cwd_length - 1] != '/') {
			cwd[cwd_length] = '/';
			cwd[cwd_length + 1] = 0;
			cwd_length++;
		}

		char *aggregate_string = malloc(total_len * sizeof(char));
		if (aggregate_string == NULL) {
			(void)printf("error: malloc() failed!\n");
			(void)printf("errno: %d\n", errno);
			exit(1);
		}

		strcpy(aggregate_string, cwd);
		strcat(aggregate_string, path_to_append);

		if (chdir(aggregate_string) != 0) {
			(void)printf("error: chdir() failed!\n");
			(void)printf("errno: %d\n", errno);
			free(aggregate_string);
			exit(1);
		}

		if (setenv("PWD", aggregate_string, WRITE_ENVVAR) != 0) {
			(void)printf("error: setenv() failed!\n");
			(void)printf("errno: %d\n", errno);
			free(aggregate_string);
			exit(1);
		}

		free(aggregate_string);
	}

	if (DEBUG_MODE) {
		(void)printf("EXIT: change_working_directory()");
	}
}

void print_working_directory() {
	if (DEBUG_MODE) {
		(void)printf("CALL: change_working_directory()");
	}

	char cwd[MAX_PATH_SIZE];
	if (getcwd(cwd, MAX_PATH_SIZE) == NULL) {
		(void)printf("error: getcwd() failed!\n");
		(void)printf("errno: %d\n", errno);
		exit(1);
	}

	(void)printf("CWD: '%s'\n", cwd);

	if (DEBUG_MODE) {
		(void)printf("EXIT: print_working_directory()");
	}
}
