CC ?= cc
CFLAGS ?= -std=c11 -O2 -g -Wall -Wextra -Werror -Wpedantic
.PHONY: all smoke puzzle clean
all: build/fixture_reader
build/fixture_reader: src/fixture_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
smoke: all
	@./build/fixture_reader cases/observations.csv
puzzle: all
	@./build/fixture_reader --puzzle cases/observations.csv
clean:
	rm -rf build
