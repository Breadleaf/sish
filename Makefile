SHELL := $(shell which bash)

PROJ_ROOT := $(shell git rev-parse --show-toplevel)
PROJ_NAME := sish

CC := $(shell which cc)

SEARCH_DIRS := src src/builtin_utils
C_FILES := $(foreach dir,$(SEARCH_DIRS),$(wildcard $(dir)/*.c))
INCLUDE_DIRS := $(foreach dir,$(SEARCH_DIRS),-I $(dir))

.PHONY: all help build debug preview_manpage

all: help

help:
	@echo "make [target]"
	@echo "targets:"
	@echo "  all             - print this menu"
	@echo "  help            - print this menu"
	@echo "  build           - compile the program"
	@echo "  debug           - compile the program with debug flags"
	@echo "  preview_manpage - preview the manpage for sish(1)"

build:
	$(CC) $(C_FILES) $(INCLUDE_DIRS) -o $(PROJ_NAME)

debug:
	$(CC) $(C_FILES) $(INCLUDE_DIRS) -o $(PROJ_NAME) -D DEBUG_MODE=.

preview_manpage:
	if command -v groff &> /dev/null; then echo "groff is not installed"; fi
	groff -man -T ascii $(PROJ_ROOT)/manpages/sish.1
