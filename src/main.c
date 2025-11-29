#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WRITE_ENVVAR 1
#define KEEP_ENVVAR  0

#define MAX_PATH_SIZE 4096

int main() {
	char cwd[MAX_PATH_SIZE];
	if (getcwd(cwd, MAX_PATH_SIZE) == NULL) {
		(void)printf("error: getcwd() failed!\n");
		exit(1);
	}

	(void)printf("CWD: '%s'\n", cwd);

	size_t cwd_length = strlen(cwd);

	char *go_back = "/../";
	size_t go_back_len = strlen(go_back);

	size_t total_len = cwd_length + go_back_len + 1;

	char *aggregate_string = malloc(total_len * sizeof(char));
	if (aggregate_string == NULL) {
		(void)printf("error: malloc() failed!\n");
		exit(1);
	}

	for (size_t idx = 0; idx < cwd_length; idx++) {
		aggregate_string[idx] = cwd[idx];
	}

	for (size_t idx = 0; idx < go_back_len; idx++) {
		aggregate_string[cwd_length + idx] = go_back[idx];
	}

	aggregate_string[total_len - 1] = 0;

	(void)printf("'%s'\n", aggregate_string);

	if (chdir(aggregate_string) != 0) {
		(void)printf("error: chdir() failed!\n");
		exit(1);
	}

	free(aggregate_string);

	char new_cwd[MAX_PATH_SIZE];
	if (getcwd(new_cwd, MAX_PATH_SIZE) == NULL) {
		(void)printf("error: getcwd() failed!\n");
		exit(1);
	}

	(void)printf("CWD: '%s'\n", new_cwd);
}
