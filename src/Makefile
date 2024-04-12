.PHONY: help

all: hash_map tests # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

main: main.cpp # Build the main executable
	g++ -std=c++20 -Iinclude main.cpp -o main

tests: ../tests/hashMap_tests.cpp # Build the tests executable
	g++ -std=c++20 -Iinclude ../tests/hashMap_tests.cpp -o hash_map_tests

clean: # Delete all builded files
	rm -f hash_map tests
