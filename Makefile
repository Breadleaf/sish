SHELL:=$(shell which bash)

PROJ_ROOT:=$(shell git rev-parse --show-toplevel)
PROJ_NAME:=sish

CC:=$(shell which cc)

C_FILES:=$(shell ls $(PROJ_ROOT)/src/*.c)

.PHONY: all help build

all: help

help:
	@echo "make [target]"
	@echo "targets:"
	@echo "  all   - print this menu"
	@echo "  help  - print this menu"
	@echo "  build - compile the program"
	@echo "  debug - compile the program with debug flags"

build:
	$(CC) $(C_FILES) -o $(PROJ_NAME)

debug:
	$(CC) $(C_FILES) -o $(PROJ_NAME) -D DEBUG_MODE=.
